// Self-test for uart_bridge.hpp - no Verilator, no BIOS.
//
// The "device" is a line-by-line C++ port of baud_tick.sv + uart_tx.sv + uart_rx.sv (same state machines, same
// registered-output timing), with a tiny firmware around it that echoes every received byte + 1. The bridge talks to
// it over real loopback TCP sockets, exactly as the CLI will talk to the simulation.
//
//   build + run:  make bridge-selftest
//
// If this passes but the real sim misbehaves, the problem is in the glue or the BIOS, not in the bridge's UART timing.

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "uart_bridge.hpp"
#include "uart_rtl_model.hpp"

using namespace zb;

// ---------------------------------------------------------------------------------------------------
//  loopback client
// ---------------------------------------------------------------------------------------------------
struct Client {
    sock_t s = BAD_SOCK;
    std::string got;
    bool open(uint16_t port) {
        net_init();
        s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s == BAD_SOCK) return false;
        sockaddr_in a;
        std::memset(&a, 0, sizeof(a));
        a.sin_family = AF_INET;
        a.sin_port = htons(port);
        a.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        if (::connect(s, reinterpret_cast<sockaddr*>(&a), sizeof(a)) != 0) return false;
        int one = 1;
        setsockopt(s, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&one), sizeof(one));
        return sock_nonblock(s);
    }
    void close() { if (s != BAD_SOCK) { sock_close(s); s = BAD_SOCK; } }
    void send(const std::string& d) { sock_send(s, d.data(), d.size()); }
    void pump() {
        char b[512];
        for (;;) {
            int n = sock_recv(s, b, sizeof(b));
            if (n > 0) got.append(b, b + n); else break;
        }
    }
};

// ---------------------------------------------------------------------------------------------------
//  harness
// ---------------------------------------------------------------------------------------------------
static int g_fail = 0, g_checks = 0;
#define CHECK(cond, ...)                                                           \
    do {                                                                           \
        ++g_checks;                                                                \
        if (!(cond)) { ++g_fail; std::printf("   FAIL: "); std::printf(__VA_ARGS__); std::printf("\n"); } \
    } while (0)

struct Rig {
    UartRtl dev;
    EchoFw fw;
    Bridge br;
    Client data, rst;
    int rx_level = 1;
    uint64_t cycles = 0;
    int resets = 0;
    unsigned poll_every;

    Rig(int clk, int baud, int samp, uint16_t dp, uint16_t rp, unsigned poll)
        : dev(clk, baud, samp), fw(dev),
          br(dp, rp, static_cast<unsigned>((clk / (baud * samp)) * samp)), poll_every(poll) {
        dev.reset();
    }
    bool up() {
        if (!br.start()) return false;
        if (!data.open(br.data_port()) || !rst.open(br.reset_port())) return false;
        for (int i = 0; i < 20; ++i) { br.poll(); sleep_ms(2); }   // let the accepts happen
        return br.data_connected() && br.reset_connected();
    }
    void step() {
        fw.clock(rx_level);
        rx_level = br.clock(dev.tx);
        ++cycles;
        if (cycles % poll_every == 0) {
            br.poll();
            if (br.take_reset_request()) {
                fw.reset();
                rx_level = 1;
                br.reset_complete();
                ++resets;
            }
        }
    }
    // run until `pred` or the budget is spent; the client sockets are pumped from time to time
    template <class P> bool run_until(uint64_t budget, P pred) {
        for (uint64_t i = 0; i < budget; ++i) {
            step();
            if (i % 997 == 0) { data.pump(); rst.pump(); if (pred()) return true; }
        }
        data.pump(); rst.pump();
        return pred();
    }
    void run(uint64_t n) { run_until(n, [] { return false; }); }
};

static std::string bytes(const std::vector<uint8_t>& v) { return std::string(v.begin(), v.end()); }

static void suite(int clk, int baud, int samp, uint16_t base_port) {
    std::printf("\n=== clk %d Hz, baud %d, oversample %d (bit = %d cycles)\n", clk, baud, samp, (clk / (baud * samp)) * samp);
    const uint64_t byte_cycles = static_cast<uint64_t>((clk / (baud * samp)) * samp) * 10;
    Rig r(clk, baud, samp, base_port, static_cast<uint16_t>(base_port + 1), 256);
    CHECK(r.up(), "bridge could not start / clients could not connect");
    if (!r.br.data_connected()) return;

    // T1: back-to-back burst, every byte value class (start-bit-like 0x00, all ones, alternating, ...)
    {
        std::string tx = std::string("\xAA\x3A\x00\xFF\x55\x80\x01\x7F", 8);
        r.data.send(tx);
        std::string want;
        for (char c : tx) want.push_back(static_cast<char>(static_cast<uint8_t>(c) + 1));
        bool ok = r.run_until(byte_cycles * 40, [&] { return r.data.got.size() >= want.size(); });
        CHECK(ok, "T1 timed out, got %zu of %zu echo bytes", r.data.got.size(), want.size());
        CHECK(bytes(r.fw.seen) == tx, "T1 device did not receive the exact bytes sent (got %zu bytes)", r.fw.seen.size());
        CHECK(r.data.got == want, "T1 echo mismatch");
        std::printf("  T1 burst of %zu bytes: %s\n", tx.size(), (r.data.got == want && bytes(r.fw.seen) == tx) ? "ok" : "FAILED");
    }

    // T2: 100 bytes with every value, still back to back
    {
        r.data.got.clear(); r.fw.seen.clear();
        std::string tx;
        for (int i = 0; i < 100; ++i) tx.push_back(static_cast<char>((i * 37 + 5) & 0xFF));
        r.data.send(tx);
        std::string want;
        for (char c : tx) want.push_back(static_cast<char>(static_cast<uint8_t>(c) + 1));
        r.run_until(byte_cycles * 400, [&] { return r.data.got.size() >= want.size(); });
        CHECK(bytes(r.fw.seen) == tx, "T2 device-side bytes differ (got %zu)", r.fw.seen.size());
        CHECK(r.data.got == want, "T2 echo mismatch (got %zu of %zu)", r.data.got.size(), want.size());
        std::printf("  T2 burst of %zu bytes: %s\n", tx.size(), r.data.got == want ? "ok" : "FAILED");
    }

    // T3: "RESET" arriving in two TCP pieces must trigger exactly one reset, only after the newline
    {
        r.resets = 0; r.rst.got.clear();
        r.rst.send("RES");
        r.run(5000);
        CHECK(r.resets == 0, "T3 reset fired on a partial line");
        r.rst.send("ET\n");
        r.run_until(20000, [&] { return r.rst.got.size() >= 3; });
        CHECK(r.resets == 1, "T3 expected 1 reset, saw %d", r.resets);
        CHECK(r.rst.got == "OK\n", "T3 expected OK\\n, got '%s'", r.rst.got.c_str());
        std::printf("  T3 split RESET line: %s\n", (r.resets == 1 && r.rst.got == "OK\n") ? "ok" : "FAILED");
    }

    // T4: unknown line ignored, CRLF accepted
    {
        r.resets = 0; r.rst.got.clear();
        r.rst.send("FOO\nRESET\r\n");
        r.run_until(20000, [&] { return r.rst.got.size() >= 3; });
        CHECK(r.resets == 1, "T4 expected 1 reset, saw %d", r.resets);
        CHECK(r.rst.got == "OK\n", "T4 expected a single OK\\n, got '%s'", r.rst.got.c_str());
        std::printf("  T4 unknown line + CRLF: %s\n", (r.resets == 1 && r.rst.got == "OK\n") ? "ok" : "FAILED");
    }

    // T5: reset in the middle of a transfer drops what was still queued; the link works again afterwards
    {
        r.data.got.clear(); r.fw.seen.clear(); r.rst.got.clear(); r.resets = 0;
        std::string tx(12, '\x10');
        r.data.send(tx);
        r.run(byte_cycles * 2 + 700);                 // a couple of bytes are through, the rest still queued
        size_t before = r.data.got.size();
        CHECK(before < tx.size(), "T5 setup: everything was already echoed");
        r.rst.send("RESET\n");
        r.run_until(20000, [&] { return r.resets == 1; });
        r.run(byte_cycles * 30);                      // would be plenty for the rest of the burst
        r.data.pump();
        CHECK(r.data.got.size() == before, "T5 %zu byte(s) arrived after the reset", r.data.got.size() - before);
        r.data.got.clear(); r.fw.seen.clear();
        r.data.send("\x42");
        bool ok = r.run_until(byte_cycles * 6, [&] { return r.data.got.size() >= 1; });
        CHECK(ok && r.data.got == "\x43", "T5 link dead after the reset");
        std::printf("  T5 reset mid-transfer: %s\n", (ok && r.data.got == "\x43" && r.data.got.size() == 1) ? "ok" : "FAILED");
    }

    // T6: the CLI disconnects and a new one connects; nothing stale is delivered
    {
        r.data.close();
        r.run(byte_cycles);                           // bridge notices, drops the client
        r.data.got.clear(); r.fw.seen.clear();
        CHECK(r.data.open(r.br.data_port()), "T6 reconnect failed");
        r.run(3000);
        r.data.send("\x01\x02");
        bool ok = r.run_until(byte_cycles * 8, [&] { return r.data.got.size() >= 2; });
        CHECK(ok && r.data.got == "\x02\x03", "T6 echo after reconnect wrong (%zu bytes)", r.data.got.size());
        std::printf("  T6 reconnect: %s\n", (ok && r.data.got == "\x02\x03") ? "ok" : "FAILED");
    }

    // T7: client vanishes while the device is still transmitting - must not crash or wedge
    {
        r.data.send("\x20\x21\x22");
        r.run(byte_cycles / 2);
        r.data.close();
        r.run(byte_cycles * 10);
        CHECK(true, "unreachable");
        std::printf("  T7 client gone mid-transmit: ok\n");
    }

    CHECK(r.br.link().tx_framing_errors() == 0, "decoder saw %llu framing error(s)", static_cast<unsigned long long>(r.br.link().tx_framing_errors()));
    CHECK(r.br.link().tx_glitches() == 0, "decoder saw %llu glitch(es)", static_cast<unsigned long long>(r.br.link().tx_glitches()));
    r.data.close();
    r.rst.close();
}

int main() {
    suite(10000000, 9600, 16, 25555);     // the real configuration (bit = 1040 cycles)
    suite(10000000, 115200, 16, 25565);   // much tighter timing (bit = 80 cycles)
    std::printf("\n%d checks, %d failed\n", g_checks, g_fail);
    std::printf(g_fail ? "RESULT: FAIL\n" : "RESULT: PASS\n");
    return g_fail ? 1 : 0;
}