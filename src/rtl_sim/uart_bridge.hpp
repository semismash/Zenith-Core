// Zenith Core - UART <-> TCP bridge for the Verilator simulation (header only, no Verilator dependency)
//
//   TCP 127.0.0.1:<data port>   (default 5555)  raw UART bytes, both directions (what the CLI's "sim" profile talks to)
//   TCP 127.0.0.1:<reset port>  (default 5556)  line protocol: client sends "RESET\n", bridge answers "OK\n"
//                                                once the reset has been carried out
//
// The simulation calls Bridge::clock() once per CPU clock edge. It serialises received TCP bytes onto the i_rx pin
// as real 8N1 frames (bit-exact timing, back to back like a real UART) and decodes frames from the o_tx pin.
// Bridge::poll() does all the socket work and is meant to be called every few hundred cycles, never per cycle.
//
// Single threaded and non-blocking everywhere, so a run is deterministic. Works with Winsock (native Windows /
// MSYS2) and with POSIX sockets (WSL2, Linux).
#pragma once

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <deque>
#include <string>
#include <vector>

#ifdef _WIN32
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #ifndef NOMINMAX
    #define NOMINMAX
  #endif
  #include <winsock2.h>
  #include <ws2tcpip.h>
#else
  #include <arpa/inet.h>
  #include <cerrno>
  #include <fcntl.h>
  #include <netinet/in.h>
  #include <netinet/tcp.h>
  #include <sys/socket.h>
  #include <sys/types.h>
  #include <unistd.h>
#endif

namespace zb {

// ===================================================================================================
//  tiny portability layer
// ===================================================================================================
#ifdef _WIN32
using sock_t = SOCKET;
static const sock_t BAD_SOCK = INVALID_SOCKET;
inline bool net_init() {
    static bool done = false;
    if (!done) {
        WSADATA d;
        if (WSAStartup(MAKEWORD(2, 2), &d) != 0) return false;
        done = true;
    }
    return true;
}
inline bool err_would_block() { return WSAGetLastError() == WSAEWOULDBLOCK; }
inline void sock_close(sock_t s) { closesocket(s); }
inline bool sock_nonblock(sock_t s) { u_long m = 1; return ioctlsocket(s, FIONBIO, &m) == 0; }
inline void sleep_ms(unsigned ms) { Sleep(ms); }
inline int sock_send(sock_t s, const char* p, size_t n) { return ::send(s, p, static_cast<int>(n), 0); }
inline int sock_recv(sock_t s, char* p, size_t n) { return ::recv(s, p, static_cast<int>(n), 0); }
#else
using sock_t = int;
static const sock_t BAD_SOCK = -1;
inline bool net_init() { return true; }
inline bool err_would_block() { return errno == EAGAIN || errno == EWOULDBLOCK; }
inline void sock_close(sock_t s) { ::close(s); }
inline bool sock_nonblock(sock_t s) {
    int f = fcntl(s, F_GETFL, 0);
    return f >= 0 && fcntl(s, F_SETFL, f | O_NONBLOCK) == 0;
}
inline void sleep_ms(unsigned ms) { usleep(ms * 1000u); }
inline int sock_send(sock_t s, const char* p, size_t n) { return static_cast<int>(::send(s, p, n, MSG_NOSIGNAL)); }
inline int sock_recv(sock_t s, char* p, size_t n) { return static_cast<int>(::recv(s, p, n, 0)); }
#endif

// ===================================================================================================
//  Endpoint: one listening port, at most one connected client (a newer client replaces the older one,
//  which keeps a crashed CLI from locking the port)
// ===================================================================================================
class Endpoint {
public:
    Endpoint() = default;
    Endpoint(const Endpoint&) = delete;
    Endpoint& operator=(const Endpoint&) = delete;
    ~Endpoint() { close_all(); }

    bool open(uint16_t port, bool nodelay) {
        if (!net_init()) return false;
        port_ = port;
        nodelay_ = nodelay;
        lis_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (lis_ == BAD_SOCK) return false;
#ifndef _WIN32
        int one = 1;  // quick restart of the sim without waiting for TIME_WAIT (not wanted on Windows, it allows port hijacking)
        setsockopt(lis_, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&one), sizeof(one));
#endif
        sockaddr_in a;
        std::memset(&a, 0, sizeof(a));
        a.sin_family = AF_INET;
        a.sin_port = htons(port);
        a.sin_addr.s_addr = htonl(INADDR_LOOPBACK);   // loopback only
        if (::bind(lis_, reinterpret_cast<sockaddr*>(&a), sizeof(a)) != 0 || ::listen(lis_, 4) != 0 ||
            !sock_nonblock(lis_)) {
            sock_close(lis_);
            lis_ = BAD_SOCK;
            return false;
        }
        return true;
    }

    void close_all() {
        drop_client();
        if (lis_ != BAD_SOCK) { sock_close(lis_); lis_ = BAD_SOCK; }
    }

    void drop_client() {
        if (cli_ != BAD_SOCK) { sock_close(cli_); cli_ = BAD_SOCK; }
        out_.clear();
    }

    bool connected() const { return cli_ != BAD_SOCK; }
    uint16_t port() const { return port_; }

    // accepts every pending connection, the newest one wins. Returns true if a new client arrived.
    bool accept_poll() {
        bool got = false;
        if (lis_ == BAD_SOCK) return false;
        for (;;) {
            sock_t c = ::accept(lis_, nullptr, nullptr);
            if (c == BAD_SOCK) break;   // nothing pending (or a transient error, retried on the next poll)
            if (!sock_nonblock(c)) { sock_close(c); continue; }
            if (nodelay_) {
                int one = 1;            // single UART bytes must not sit in Nagle's buffer
                setsockopt(c, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&one), sizeof(one));
            }
            drop_client();
            cli_ = c;
            got = true;
        }
        return got;
    }

    // appends whatever the client sent to `out`. Returns false if the client went away during this call.
    bool recv_poll(std::vector<uint8_t>& out) {
        if (cli_ == BAD_SOCK) return true;
        char buf[4096];
        for (;;) {
            int n = sock_recv(cli_, buf, sizeof(buf));
            if (n > 0) {
                out.insert(out.end(), reinterpret_cast<uint8_t*>(buf), reinterpret_cast<uint8_t*>(buf) + n);
                if (static_cast<size_t>(n) < sizeof(buf)) return true;
                continue;
            }
            if (n < 0 && err_would_block()) return true;
            drop_client();   // orderly close (0) or a hard error
            return false;
        }
    }

    void send_queue(const uint8_t* p, size_t n) {
        if (cli_ != BAD_SOCK) out_.insert(out_.end(), p, p + n);
    }
    void clear_out() { out_.clear(); }

    // pushes as much of the queued output as the socket takes right now
    void flush() {
        while (cli_ != BAD_SOCK && !out_.empty()) {
            char buf[1024];
            size_t n = 0;
            while (n < sizeof(buf) && n < out_.size()) { buf[n] = static_cast<char>(out_[n]); ++n; }
            int s = sock_send(cli_, buf, n);
            if (s > 0) { out_.erase(out_.begin(), out_.begin() + s); continue; }
            if (s < 0 && err_would_block()) return;   // keep the rest for the next poll
            drop_client();
            return;
        }
    }

private:
    sock_t lis_ = BAD_SOCK;
    sock_t cli_ = BAD_SOCK;
    uint16_t port_ = 0;
    bool nodelay_ = false;
    std::deque<uint8_t> out_;
};

// ===================================================================================================
//  UartLink: bit-level 8N1 serialiser (host -> i_rx) and decoder (o_tx -> host), cycle accurate
// ===================================================================================================
class UartLink {
public:
    explicit UartLink(unsigned bit_cycles) : bit_(bit_cycles ? bit_cycles : 1) {}

    unsigned bit_cycles() const { return bit_; }

    void push_rx(uint8_t b) { rx_q_.push_back(b); }
    bool pop_tx(uint8_t& b) {
        if (tx_out_.empty()) return false;
        b = tx_out_.front();
        tx_out_.pop_front();
        return true;
    }
    size_t rx_pending() const { return rx_q_.size() + (rx_active_ ? 1 : 0); }

    // forgets everything in flight (core reset: a half-sent frame would only confuse the fresh BIOS)
    void reset() {
        rx_q_.clear();
        tx_out_.clear();
        rx_active_ = false;
        rx_level_ = 1;
        tx_active_ = false;
    }
    void clear_queues() { rx_q_.clear(); tx_out_.clear(); }

    // One call per CPU clock cycle. `tx_pin` is o_tx as seen after the rising edge; the return value is the level
    // i_rx must have during the NEXT cycle.
    int clock(int tx_pin) {
        // ---- host -> core (i_rx)
        if (rx_active_) {
            if (++rx_cnt_ >= bit_) {
                rx_cnt_ = 0;
                if (++rx_bit_ >= 10) rx_active_ = false;
            }
        }
        if (!rx_active_ && !rx_q_.empty()) {            // next frame starts right away (back to back, like a real host)
            rx_byte_ = rx_q_.front();
            rx_q_.pop_front();
            rx_active_ = true;
            rx_bit_ = 0;
            rx_cnt_ = 0;
            ++rx_frames_;
            if (rx_started_cb_) rx_started_cb_(rx_byte_);
        }
        if (!rx_active_)            rx_level_ = 1;
        else if (rx_bit_ == 0)      rx_level_ = 0;                          // start bit
        else if (rx_bit_ <= 8)      rx_level_ = (rx_byte_ >> (rx_bit_ - 1)) & 1;   // data, LSB first
        else                        rx_level_ = 1;                          // stop bit

        // ---- core -> host (o_tx), sampled in the middle of every bit
        if (!tx_active_) {
            if (tx_pin == 0) { tx_active_ = true; tx_cnt_ = 0; tx_bit_ = 0; tx_shift_ = 0; }
        } else {
            ++tx_cnt_;
            if (tx_cnt_ == bit_ * tx_bit_ + bit_ / 2) {
                if (tx_bit_ == 0) {
                    if (tx_pin != 0) { tx_active_ = false; ++tx_glitches_; }   // not a real start bit
                } else if (tx_bit_ <= 8) {
                    tx_shift_ |= static_cast<uint8_t>((tx_pin & 1) << (tx_bit_ - 1));
                } else {
                    if (tx_pin == 1) {
                        tx_out_.push_back(tx_shift_);
                        ++tx_frames_;
                        if (tx_decoded_cb_) tx_decoded_cb_(tx_shift_);
                    } else {
                        ++tx_framing_errors_;
                    }
                    tx_active_ = false;
                }
                ++tx_bit_;
            }
        }
        return rx_level_;
    }

    // statistics / hooks
    uint64_t rx_frames() const { return rx_frames_; }
    uint64_t tx_frames() const { return tx_frames_; }
    uint64_t tx_framing_errors() const { return tx_framing_errors_; }
    uint64_t tx_glitches() const { return tx_glitches_; }
    void on_rx_started(void (*cb)(uint8_t)) { rx_started_cb_ = cb; }
    void on_tx_decoded(void (*cb)(uint8_t)) { tx_decoded_cb_ = cb; }

private:
    unsigned bit_;
    // rx (to the core)
    std::deque<uint8_t> rx_q_;
    bool rx_active_ = false;
    uint8_t rx_byte_ = 0;
    unsigned rx_bit_ = 0, rx_cnt_ = 0;
    int rx_level_ = 1;
    // tx (from the core)
    std::deque<uint8_t> tx_out_;
    bool tx_active_ = false;
    uint8_t tx_shift_ = 0;
    unsigned tx_bit_ = 0, tx_cnt_ = 0;
    // stats
    uint64_t rx_frames_ = 0, tx_frames_ = 0, tx_framing_errors_ = 0, tx_glitches_ = 0;
    void (*rx_started_cb_)(uint8_t) = nullptr;
    void (*tx_decoded_cb_)(uint8_t) = nullptr;
};

// ===================================================================================================
//  Bridge: both sockets + the UART link
// ===================================================================================================
class Bridge {
public:
    Bridge(uint16_t data_port, uint16_t reset_port, unsigned bit_cycles)
        : data_port_(data_port), reset_port_(reset_port), link_(bit_cycles) {}

    bool start() { return data_.open(data_port_, true) && reset_.open(reset_port_, true); }

    // ---- per cycle
    int clock(int tx_pin) { return link_.clock(tx_pin); }

    // ---- every few hundred cycles
    void poll() {
        if (data_.accept_poll()) {
            link_.clear_queues();     // stale bytes from a previous session are not for this client
            ++data_clients_;
        }
        if (reset_.accept_poll()) rst_line_.clear();

        std::vector<uint8_t> in;
        data_.recv_poll(in);
        for (size_t i = 0; i < in.size(); ++i) link_.push_rx(in[i]);

        uint8_t b;
        std::vector<uint8_t> out;
        while (link_.pop_tx(b)) out.push_back(b);
        if (!out.empty()) data_.send_queue(out.data(), out.size());   // dropped when nobody is connected
        data_.flush();

        std::vector<uint8_t> rin;
        reset_.recv_poll(rin);
        for (size_t i = 0; i < rin.size(); ++i) {
            char c = static_cast<char>(rin[i]);
            if (c == '\n') {
                if (!rst_line_.empty() && rst_line_.back() == '\r') rst_line_.pop_back();
                if (rst_line_ == "RESET") reset_pending_ = true;
                else if (!rst_line_.empty()) std::fprintf(stderr, "[BRIDGE] ignoring unknown reset-channel line '%s'\n", rst_line_.c_str());
                rst_line_.clear();
            } else if (rst_line_.size() < 64) {
                rst_line_.push_back(c);
            }
        }
        reset_.flush();
    }

    // true once per received "RESET\n"; the caller then resets the design and calls reset_complete()
    bool take_reset_request() {
        bool r = reset_pending_;
        reset_pending_ = false;
        return r;
    }
    void reset_complete() {
        link_.reset();
        data_.clear_out();            // bytes the old BIOS produced before the reset must not reach the client
        static const uint8_t ok[3] = {'O', 'K', '\n'};
        reset_.send_queue(ok, 3);
        reset_.flush();
    }

    bool data_connected() const { return data_.connected(); }
    bool reset_connected() const { return reset_.connected(); }
    uint64_t data_clients() const { return data_clients_; }
    UartLink& link() { return link_; }
    uint16_t data_port() const { return data_port_; }
    uint16_t reset_port() const { return reset_port_; }

private:
    uint16_t data_port_, reset_port_;
    Endpoint data_, reset_;
    UartLink link_;
    std::string rst_line_;
    bool reset_pending_ = false;
    uint64_t data_clients_ = 0;
};

}  // namespace zb