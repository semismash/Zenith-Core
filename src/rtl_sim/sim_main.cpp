// Zenith Core - core-only Verilator testbench (stage 1: no UART bridge, no CLI)
//
// Usage:  obj_dir/Vtop.exe +ROM_HEX=src/firmware/program.hex
//   rom.sv loads the same file through $readmemh (see its `ifdef VERILATOR block); this TB reads it
//   as well, only to echo the program and check its size.
//
// Every internal signal is reached through DUT->rootp->top__DOT__<name>, which needs the Verilator
// flag --public-flat-rw (already in the makefile).

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>
#include <iomanip>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vtop.h"
#include "Vtop___024root.h"

constexpr size_t   ROM_SIZE_BYTES   = 8192;   // must match rv32i.sv / rom.sv
constexpr size_t   MAX_CYCLE_COUNT  = 10000;  // safety cutoff for a runaway program
constexpr size_t   PIPELINE_STAGES  = 5;
constexpr unsigned RESET_CYCLES     = 4;      // clock cycles rst_n is held low before release
constexpr bool     REGS_ONLY_ON_CHANGE = false; // true: print the register block only in cycles where a register changed

// --- GPR TRACKING CONFIGURATION (Compile-Time Validated) ---
constexpr int MIN_GPR = 1; // inclusive
constexpr int MAX_GPR = 31; // inclusive

static_assert(MIN_GPR >= 1 && MIN_GPR <= 31, "[COMPILE ERROR] MIN_GPR must be between 1 and 31!");
static_assert(MAX_GPR >= 1 && MAX_GPR <= 31, "[COMPILE ERROR] MAX_GPR must be between 1 and 31!");
static_assert(MIN_GPR <= MAX_GPR, "[COMPILE ERROR] MIN_GPR cannot be greater than MAX_GPR!");

double sc_time_stamp() {
    return 0;
}

namespace std {
    namespace __cxx11 {
        template class basic_string<char>;
    }
}

// "0x" + 8 hex digits
static std::string hex32(uint32_t v) {
    char buf[16];
    std::snprintf(buf, sizeof(buf), "0x%08x", static_cast<unsigned>(v));
    return buf;
}

// reads a $readmemh style file: one hex word per token, '//' comments and '@addr' lines are skipped
static bool load_hex_words(const std::string& path, std::vector<uint32_t>& words) {
    std::ifstream f(path);
    if (!f.is_open()) return false;
    std::string line;
    while (std::getline(f, line)) {
        const auto c = line.find("//");
        if (c != std::string::npos) line.erase(c);
        std::istringstream ss(line);
        std::string tok;
        while (ss >> tok) {
            if (tok[0] == '@') continue;
            words.push_back(static_cast<uint32_t>(std::stoul(tok, nullptr, 16)));
        }
    }
    return true;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    // ---------------------------------------------------------------- program (for echo / size check)
    std::string hex_path;
    if (const char* m = Verilated::commandArgsPlusMatch("ROM_HEX"); m && m[0]) {
        const std::string s(m);
        const auto eq = s.find('=');
        if (eq != std::string::npos) hex_path = s.substr(eq + 1);
    }
    if (hex_path.empty()) {
        std::cerr << "[TB ERROR] No program given. Run with +ROM_HEX=<path to program.hex>" << std::endl;
        return -1;
    }

    std::vector<uint32_t> words;
    if (!load_hex_words(hex_path, words)) {
        std::cerr << "[TB ERROR] Could not open " << hex_path << std::endl;
        return -1;
    }
    if (words.size() * 4 > ROM_SIZE_BYTES) {
        std::cerr << "[TB ERROR] Program (" << words.size() * 4 << " bytes) exceeds the "
                  << ROM_SIZE_BYTES << " byte ROM!" << std::endl;
        return -1;
    }

    std::cout << "========================================================" << std::endl;
    std::cout << "[TB] PROGRAM " << hex_path << " (" << words.size() << " words):" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    for (size_t i = 0; i < words.size(); ++i) {
        std::cout << "Addr " << hex32(static_cast<uint32_t>(i * 4)) << ": " << hex32(words[i]) << std::endl;
    }
    std::cout << "========================================================\n" << std::endl;

    // ---------------------------------------------------------------- DUT
    auto DUT = std::make_unique<Vtop>();
    auto trace = std::make_unique<VerilatedVcdC>();
    DUT->trace(trace.get(), 99);
    trace->open("waveform.vcd");
    Vtop___024root& r = *DUT->rootp;

    uint64_t sim_time = 0;
    // one full clock period; leaves clk high
    auto tick = [&]() {
        DUT->clk = 0;
        DUT->eval();
        trace->dump(sim_time++);
        DUT->clk = 1;
        DUT->eval();
        trace->dump(sim_time++);
    };

    // The first eval() runs the initial blocks (rom.sv's $readmemh), so nothing may be poked into
    // the memories before it - the program comes in through +ROM_HEX instead.
    DUT->i_rx  = 1;   // UART idles high; left at 0 it would look like a permanent start bit
    DUT->rst_n = 0;
    DUT->clk   = 0;
    DUT->eval();
    trace->dump(sim_time++);

    for (unsigned i = 0; i < RESET_CYCLES; ++i) tick();
    DUT->rst_n = 1;
    // top.sv releases core_rst_n two cpu_clk edges after rst_n (2-flop synchronizer)
    for (unsigned guard = 0; !r.top__DOT__core_rst_n && guard < 16; ++guard) tick();
    if (!r.top__DOT__core_rst_n) {
        std::cerr << "[TB ERROR] core_rst_n never released!" << std::endl;
        return -1;
    }
    std::cout << "[TB] Reset released. Commencing execution loop..." << std::endl;

    // ---------------------------------------------------------------- main loop
    uint64_t cycles = 0;
    bool timed_out = false;
    uint32_t prev_regs[32] = {0};

    auto start_wall_time = std::chrono::high_resolution_clock::now();

    while (!Verilated::gotFinish() && !r.top__DOT__halt && !r.top__DOT__stop) {
        tick();
        cycles++;

        // AXI4-Lite handshakes as seen right after the rising edge (they complete at the next edge)
        const bool if_ar_hs  = r.top__DOT__if_arvalid   && r.top__DOT__if_arready;
        const bool if_r_hs   = r.top__DOT__if_rvalid    && r.top__DOT__if_rready;
        const bool d_ar_hs   = r.top__DOT__data_arvalid && r.top__DOT__data_arready;
        const bool d_aw_hs   = r.top__DOT__data_awvalid && r.top__DOT__data_awready &&
                               r.top__DOT__data_wvalid  && r.top__DOT__data_wready;
        const bool d_r_hs    = r.top__DOT__data_rvalid  && r.top__DOT__data_rready;
        const bool d_b_hs    = r.top__DOT__data_bvalid  && r.top__DOT__data_bready;

        bool regs_changed = false;
        for (int i = MIN_GPR; i <= MAX_GPR; ++i) {
            const uint32_t v = r.top__DOT__u_cpu__DOT__u_reg_file__DOT__registers[i];
            if (v != prev_regs[i]) regs_changed = true;
            prev_regs[i] = v;
        }

        std::cout << "\n========================================================" << std::endl;
        std::cout << "[CYCLE " << std::dec << cycles << "]" << std::endl;
        std::cout << " -> Fetch : AR " << (if_ar_hs ? hex32(r.top__DOT__if_araddr) : std::string("idle      "))
                  << " | R " << (if_r_hs ? hex32(r.top__DOT__if_rdata) : std::string("idle")) << std::endl;

        std::cout << " -> Data  : ";
        if (d_aw_hs) {
            std::cout << "WRITE " << hex32(r.top__DOT__data_awaddr) << " <- " << hex32(r.top__DOT__data_wdata)
                      << " strb=0x" << std::hex << static_cast<unsigned>(r.top__DOT__data_wstrb) << std::dec;
        } else if (d_ar_hs) {
            std::cout << "READ  " << hex32(r.top__DOT__data_araddr);
        } else {
            std::cout << "idle";
        }
        if (d_r_hs) std::cout << " | R " << hex32(r.top__DOT__data_rdata);
        if (d_b_hs) std::cout << " | B resp=" << static_cast<unsigned>(r.top__DOT__data_bresp);
        std::cout << std::endl;

        if (!REGS_ONLY_ON_CHANGE || regs_changed) {
            std::cout << " -------------------- REGISTER FILE --------------------" << std::endl;
            int printed_in_row = 0;
            std::cout << " -> ";
            for (int i = MIN_GPR; i <= MAX_GPR; ++i) {
                // format register number to always use 2 digits with zero-padding (e.g., x01, x12)
                std::cout << "x" << std::dec << std::setw(2) << std::setfill('0') << i << ": "
                          << hex32(prev_regs[i]);
                printed_in_row++;
                if (printed_in_row == 4 && i != MAX_GPR) {
                    std::cout << "\n -> ";
                    printed_in_row = 0;
                } else if (i != MAX_GPR) {
                    std::cout << " | ";
                }
            }
            std::cout << std::endl;
        }

        if (cycles >= MAX_CYCLE_COUNT) {
            std::cout << "\n[TB WARNING] Safety simulation cutoff breached!" << std::endl;
            timed_out = true;
            break;
        }
    }

    auto end_wall_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_wall_time - start_wall_time;

    // ---------------------------------------------------------------- end-of-run report
    const bool halted     = r.top__DOT__halt;
    const bool stopped    = r.top__DOT__stop;
    const unsigned led    = DUT->led;                 // [0] stop, [1] instr fault, [2] data fault, [3] illegal instr
    const bool any_fault  = (led & 0xE) != 0;

    std::cout << "\n========================================================" << std::endl;
    if (halted) {
        std::cout << "[TB INFO] CPU core crashed safely and generated a HALT signal." << std::endl;
    } else if (stopped) {
        std::cout << "[TB INFO] CPU core reached a safe STOP signal." << std::endl;
    } else if (timed_out) {
        std::cout << "[TB INFO] Simulation hit the " << MAX_CYCLE_COUNT << " cycle cutoff (no stop/halt)." << std::endl;
    } else {
        std::cout << "[TB INFO] Simulation finished processing." << std::endl;
    }
    std::cout << "[FINAL STATUS]" << std::endl;
    std::cout << " -> halt: " << halted << " | stop: " << stopped << std::endl;
    std::cout << " -> LEDs: stop=" << (led & 1) << " instr_fault=" << ((led >> 1) & 1)
              << " data_fault=" << ((led >> 2) & 1) << " illegal_instr=" << ((led >> 3) & 1) << std::endl;
    std::cout << " -> Last fetch addr: " << hex32(r.top__DOT__if_araddr) << std::endl;

    std::cout << "\n------------------- FINAL REGISTER FILE -------------------" << std::endl;
    for (int i = 1; i < 32; ++i) {
        std::cout << "x" << std::dec << std::setw(2) << std::setfill('0') << i << ": "
                  << hex32(r.top__DOT__u_cpu__DOT__u_reg_file__DOT__registers[i])
                  << ((i % 4 == 0) ? "\n" : " | ");
    }
    std::cout << std::endl;

    std::cout << "\n------------------- PERFORMANCE METRICS -------------------" << std::endl;
    std::cout << "Total Clock Cycles:       " << std::dec << cycles << std::endl;

#ifdef HAVE_TELEMETRY
    // needs MetaCount signals declared (public_flat_rw) in top.sv and hooked to the core, see notes
    uint32_t total_retired_instr = r.top__DOT__meta_instr_count;
    uint32_t total_stalls        = r.top__DOT__meta_stall_count;
    uint32_t load_use_stalls     = r.top__DOT__meta_l_use_count;
    uint32_t branch_flushes      = r.top__DOT__meta_br_flush_count;

    std::cout << "Instructions Retired:     " << total_retired_instr << std::endl;
    if (total_retired_instr > 0) {
        uint64_t steady_state_cycles = (cycles > (PIPELINE_STAGES - 1)) ? (cycles - (PIPELINE_STAGES - 1)) : 0;
        double cpi_clean  = static_cast<double>(cycles) / total_retired_instr;
        double cpi_steady = static_cast<double>(steady_state_cycles) / total_retired_instr;
        std::cout << "Measured CPI (w/ Overhead): " << std::fixed << std::setprecision(2) << cpi_clean << std::endl;
        std::cout << "Steady-State CPI (True):    " << std::fixed << std::setprecision(2) << cpi_steady << std::endl;
    } else {
        std::cout << "Measured CPI (w/ Overhead): N/A" << std::endl;
        std::cout << "Steady-State CPI (True):    N/A" << std::endl;
    }

    std::cout << " ------------------ MICROARCHITECTURAL STATS --------------" << std::endl;
    std::cout << "Total Stall Cycles:       " << std::dec << total_stalls;
    if (cycles > 0) {
        double stall_ratio = (static_cast<double>(total_stalls) / cycles) * 100.0;
        std::cout << " (" << std::fixed << std::setprecision(1) << stall_ratio << "% of cycles)" << std::endl;
    } else {
        std::cout << " (0.0%)" << std::endl;
    }
    std::cout << " -> Load-Use Stalls:      " << load_use_stalls << std::endl;
    std::cout << " -> Structural/ALU Stalls:" << (total_stalls - load_use_stalls) << std::endl;
    std::cout << "Total Branch Flush Cycles:" << branch_flushes << std::endl;
#else
    (void)PIPELINE_STAGES;
    std::cout << "Telemetry:                not exposed (build with 'make compile TELEMETRY=1' once top.sv exports meta_*)" << std::endl;
#endif

    std::cout << " ------------------- SIMULATION SPEED ---------------------" << std::endl;
    std::cout << "Elapsed Compute Time:     " << std::fixed << std::setprecision(6) << elapsed_seconds.count() << " seconds" << std::endl;

    if (elapsed_seconds.count() > 0.0) {
        double sim_hz = static_cast<double>(cycles) / elapsed_seconds.count();
        if (sim_hz >= 1000000.0) {
            std::cout << "Simulation Frequency:     " << std::fixed << std::setprecision(2) << (sim_hz / 1000000.0) << " MHz" << std::endl;
        } else if (sim_hz >= 1000.0) {
            std::cout << "Simulation Frequency:     " << std::fixed << std::setprecision(2) << (sim_hz / 1000.0) << " kHz" << std::endl;
        } else {
            std::cout << "Simulation Frequency:     " << std::fixed << std::setprecision(2) << sim_hz << " Hz" << std::endl;
        }
    } else {
        std::cout << "Simulation Frequency:     N/A" << std::endl;
    }
    std::cout << "========================================================\n" << std::endl;

    trace->close();
    DUT->final();

    // exit code: 0 = clean stop, 1 = halt or fault, 2 = timeout
    if (halted || any_fault) return 1;
    if (timed_out) return 2;
    return 0;
}