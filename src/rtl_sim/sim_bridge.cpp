// Zenith Core - networked Verilator simulation (stage 2: BIOS + CLI over TCP)
//
//   obj_dir_bridge/zenith_bridge.exe +ROM_HEX=src/firmware/bios_sim.hex
//
//   127.0.0.1:5555   UART bytes, both directions        (CLI "sim" profile, transport = TCP)
//   127.0.0.1:5556   "RESET\n" -> full reset incl. RAM -> "OK\n"
//
// The core runs free (as fast as the host allows). The UART is real bit-level 8N1 at the baud rate of the RTL, so the BIOS
// sees exactly what it would see on the Arty. Because the sim is slower than 10 MHz wall-clock, UART bytes appear on the
// socket proportionally slower than on hardware (the BIOS timeouts count simulated cycles, so they are not affected).
//
// Plusargs (all optional, ROM_HEX is read by rom.sv):
//   +ROM_HEX=<file>     program for the ROM, one 32-bit hex word per line (default: bios.hex)
//   +DATA_PORT=<n>      default 5555
//   +RESET_PORT=<n>     default 5556
//   +BAUD=<n>           UART baud rate, must match UART_BAUD_RATE in uart.sv (default 9600)
//   +POLL=<n>           cycles between socket polls (default 256)
//   +NOWAIT             do not hold the core in reset until the first CLI connects
//   +BRIDGE_LOG         print every UART byte with the cycle it happened in
//   +TRACE              write waveform_bridge.vcd (huge, only for short runs)
//
// Every internal signal is reached through DUT->rootp->top__DOT__..., which needs --public-flat-rw (already in the makefile).

#include <chrono>
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vtop.h"
#include "Vtop___024root.h"
#include "uart_bridge.hpp"

// --- must match the RTL (rv32i.sv / uart.sv / baud_tick.sv) ---------------------------------------
constexpr unsigned CPU_CLOCK_HZ    = 10000000;   // rv32i::CPU_CLOCK_FREQ
constexpr unsigned UART_BAUD_DEF   = 9600;       // uart::UART_BAUD_RATE
constexpr unsigned UART_SAMPLING   = 16;         // uart::UART_SAMPLING_RATE
constexpr size_t   RAM_WORDS       = 131072 / 4; // rv32i::RAM_SIZE_BYTES / 4
constexpr unsigned RESET_CYCLES    = 4;          // rst_n held low for this many clocks

namespace std {
    namespace __cxx11 {
        template class basic_string<char>;
    }
}

double sc_time_stamp() { return 0; }

static volatile std::sig_atomic_t g_quit = 0;
static void on_sigint(int) { g_quit = 1; }

static uint64_t g_cycles = 0;
static bool     g_log    = false;
static void log_rx(uint8_t b) { if (g_log) std::printf("[cyc %llu] host -> core 0x%02X\n", static_cast<unsigned long long>(g_cycles), b); }
static void log_tx(uint8_t b) { if (g_log) std::printf("[cyc %llu] core -> host 0x%02X\n", static_cast<unsigned long long>(g_cycles), b); }

static bool has_plusarg(const char* name) {
    const char* m = Verilated::commandArgsPlusMatch(name);
    return m && m[0];
}
static std::string plusarg_str(const char* name, const std::string& def) {
    const char* m = Verilated::commandArgsPlusMatch(name);
    if (!m || !m[0]) return def;
    const char* eq = std::strchr(m, '=');
    return (eq && eq[1]) ? std::string(eq + 1) : def;
}
static unsigned plusarg_uint(const char* name, unsigned def) {
    const std::string s = plusarg_str(name, "");
    if (s.empty()) return def;
    char* end = nullptr;
    unsigned long v = std::strtoul(s.c_str(), &end, 0);
    return (end && *end == '\0' && v > 0) ? static_cast<unsigned>(v) : def;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    std::signal(SIGINT, on_sigint);

    const unsigned data_port  = plusarg_uint("DATA_PORT", 5555);
    const unsigned reset_port = plusarg_uint("RESET_PORT", 5556);
    const unsigned baud       = plusarg_uint("BAUD", UART_BAUD_DEF);
    const unsigned poll_every = plusarg_uint("POLL", 256);
    const bool     wait_cli   = !has_plusarg("NOWAIT");
    const bool     trace_on   = has_plusarg("TRACE");
    g_log                     = has_plusarg("BRIDGE_LOG");
    // same arithmetic as baud_rate_gen (integer divide) x oversampling: one bit lasts this many CPU clocks
    const unsigned bit_cycles = (CPU_CLOCK_HZ / (baud * UART_SAMPLING)) * UART_SAMPLING;

    zb::Bridge bridge(static_cast<uint16_t>(data_port), static_cast<uint16_t>(reset_port), bit_cycles);
    if (!bridge.start()) {
        std::fprintf(stderr, "[BRIDGE ERROR] cannot listen on 127.0.0.1:%u / %u (is another sim still running?)\n", data_port, reset_port);
        return 1;
    }
    bridge.link().on_rx_started(log_rx);
    bridge.link().on_tx_decoded(log_tx);

    if (trace_on) Verilated::traceEverOn(true);
    auto DUT = std::make_unique<Vtop>();
    std::unique_ptr<VerilatedVcdC> trace;
    if (trace_on) {
        trace = std::make_unique<VerilatedVcdC>();
        DUT->trace(trace.get(), 99);
        trace->open("waveform_bridge.vcd");
    }
    Vtop___024root& r = *DUT->rootp;

    // reset the design clears RAM from C++ (ROM is never touched, it holds the BIOS)
    static_assert(sizeof(decltype(r.top__DOT__u_mem__DOT__u_ram__DOT__container)) >= RAM_WORDS * 4,
                  "RAM_WORDS is bigger than the RAM array in the design, check RAM_SIZE_BYTES");

    uint64_t sim_time = 0;
    int rx_level = 1;
    auto cycle = [&](bool with_bridge) {
        DUT->i_rx = rx_level;
        DUT->clk = 0;
        DUT->eval();
        if (trace) trace->dump(sim_time++);
        DUT->clk = 1;
        DUT->eval();
        if (trace) trace->dump(sim_time++);
        ++g_cycles;
        if (with_bridge) rx_level = bridge.clock(DUT->o_tx);
    };

    // The first eval() runs the initial blocks (rom.sv's $readmemh from +ROM_HEX).
    DUT->i_rx  = 1;
    DUT->rst_n = 0;
    DUT->clk   = 0;
    DUT->eval();
    if (trace) trace->dump(sim_time++);

    auto do_reset = [&](bool wipe_ram) {
        DUT->rst_n = 0;
        rx_level   = 1;
        for (unsigned i = 0; i < RESET_CYCLES; ++i) cycle(false);
        if (wipe_ram) {
            for (size_t i = 0; i < RAM_WORDS; ++i) r.top__DOT__u_mem__DOT__u_ram__DOT__container[i] = 0;
        }
        DUT->rst_n = 1;
        // top.sv releases core_rst_n two cpu_clk edges after rst_n (2-flop synchronizer)
        for (unsigned guard = 0; !r.top__DOT__core_rst_n && guard < 16; ++guard) cycle(false);
    };

    std::printf("========================================================\n");
    std::printf("[BRIDGE] ROM image : %s\n", plusarg_str("ROM_HEX", "bios.hex (default)").c_str());
    std::printf("[BRIDGE] UART      : %u baud, %u cycles per bit\n", baud, bit_cycles);
    std::printf("[BRIDGE] data      : 127.0.0.1:%u\n", data_port);
    std::printf("[BRIDGE] reset     : 127.0.0.1:%u  (\"RESET\\n\" -> \"OK\\n\")\n", reset_port);
    std::printf("[BRIDGE] Ctrl+C quits\n");

    if (wait_cli) {
        std::printf("[BRIDGE] core held in reset until the first client connects on %u (+NOWAIT to disable)\n", data_port);
        while (!g_quit && !bridge.data_connected()) {
            bridge.poll();
            if (bridge.take_reset_request()) bridge.reset_complete();   // the core is still in reset anyway
            zb::sleep_ms(10);
        }
        if (g_quit) return 0;
        std::printf("[BRIDGE] client connected, releasing reset\n");
    }
    do_reset(false);
    std::printf("[BRIDGE] core running\n");
    std::printf("========================================================\n");

    // ------------------------------------------------------------------------------------------ main loop
    const auto t0 = std::chrono::high_resolution_clock::now();
    const uint64_t c0 = g_cycles;
    unsigned since_poll = 0;
    bool announced = false;
    unsigned resets = 0;

    while (!g_quit && !Verilated::gotFinish()) {
        cycle(true);
        if (++since_poll < poll_every) continue;
        since_poll = 0;

        bridge.poll();
        if (bridge.take_reset_request()) {
            do_reset(true);
            bridge.reset_complete();
            announced = false;
            ++resets;
            std::printf("[BRIDGE] RESET #%u carried out (RAM cleared) at cycle %llu\n", resets, static_cast<unsigned long long>(g_cycles));
        }

        const bool stopped = r.top__DOT__stop;
        const bool halted  = r.top__DOT__halt;
        if (stopped || halted) {
            if (!announced) {
                announced = true;
                const unsigned led = DUT->led;
                std::printf("[BRIDGE] core %s at cycle %llu  (stop=%u instr_fault=%u data_fault=%u illegal_instr=%u, last fetch 0x%08x)\n",
                            halted ? "HALTED" : "STOPPED (ebreak/ecall)", static_cast<unsigned long long>(g_cycles),
                            led & 1, (led >> 1) & 1, (led >> 2) & 1, (led >> 3) & 1,
                            static_cast<unsigned>(r.top__DOT__if_araddr));
                std::printf("[BRIDGE] the core stays frozen until \"RESET\\n\" arrives on port %u\n", reset_port);
            }
            zb::sleep_ms(1);   // nothing but the UART can change now, do not burn a core
        }
    }

    const auto t1 = std::chrono::high_resolution_clock::now();
    const double secs = std::chrono::duration<double>(t1 - t0).count();
    const uint64_t ran = g_cycles - c0;
    std::printf("\n[BRIDGE] %llu cycles in %.2f s (%.2f MHz), UART frames: %llu to core, %llu from core, %llu framing errors\n",
                static_cast<unsigned long long>(ran), secs, secs > 0 ? ran / secs / 1e6 : 0.0,
                static_cast<unsigned long long>(bridge.link().rx_frames()), static_cast<unsigned long long>(bridge.link().tx_frames()),
                static_cast<unsigned long long>(bridge.link().tx_framing_errors()));

    if (trace) trace->close();
    DUT->final();
    return 0;
}