#pragma once

// Windows build: Winsock2 instead of POSIX sockets (no arpa/inet.h, netdb.h, poll.h, sys/socket.h).
// Link with -lws2_32. WSAStartup/WSACleanup are handled once per process by WsaGuard below.

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <expected>
#include <memory>
#include <span>
#include <string>
#include <string_view>
#include <utility>

#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <winsock2.h>
#include <ws2tcpip.h>

#include "../headers/error.hpp"

#pragma comment(lib, "ws2_32.lib")   // also pass -lws2_32 on the g++ command line (MinGW ignores the pragma)

namespace interface_mod {

    using TransErr = error::TransportError;

    namespace detail {

        // one WSAStartup for the whole process, torn down at exit
        class WsaGuard {
            public:
                WsaGuard() {
                    WSADATA data{};
                    WSAStartup(MAKEWORD(2, 2), &data);
                }
                ~WsaGuard() { WSACleanup(); }
        };

        inline void ensure_wsa() {
            static WsaGuard guard{};
        }

        inline std::string wsa_error(int code) {
            char* msg{nullptr};
            const auto len = ::FormatMessageA(
                FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                nullptr, static_cast<DWORD>(code), 0, reinterpret_cast<char*>(&msg), 0, nullptr);
            std::string text = len > 0 && msg != nullptr ? std::string(msg, len) : ("error " + std::to_string(code));
            if (msg != nullptr) ::LocalFree(msg);
            while (!text.empty() && (text.back() == '\n' || text.back() == '\r')) text.pop_back();
            return text;
        }

    }

    class TcpTransport {

        private:

            SOCKET sock{INVALID_SOCKET};

            explicit TcpTransport(SOCKET s) :
                sock{s}
            { }

            static std::expected<SOCKET, error::Error> open_socket(const std::string& host, uint16_t port, std::chrono::milliseconds timeout) {
                detail::ensure_wsa();

                addrinfo hints{};
                hints.ai_family = AF_UNSPEC;
                hints.ai_socktype = SOCK_STREAM;
                addrinfo* found{nullptr};
                const auto port_str = std::to_string(port);
                if (const int rc = ::getaddrinfo(host.c_str(), port_str.c_str(), &hints, &found); rc != 0) {
                    return std::unexpected(error::Error(TransErr::ResolveFailed, host + ": " + ::gai_strerrorA(rc)));
                }
                std::unique_ptr<addrinfo, decltype(&::freeaddrinfo)> guard{found, &::freeaddrinfo};

                std::string last_err{"no address"};
                for (auto* ai = found; ai != nullptr; ai = ai->ai_next) {
                    const SOCKET s = ::socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
                    if (s == INVALID_SOCKET) { last_err = detail::wsa_error(::WSAGetLastError()); continue; }

                    u_long mode{1};    // non-blocking connect so the timeout can be applied
                    ::ioctlsocket(s, FIONBIO, &mode);
                    int rc = ::connect(s, ai->ai_addr, static_cast<int>(ai->ai_addrlen));
                    if (rc == SOCKET_ERROR && ::WSAGetLastError() == WSAEWOULDBLOCK) {
                        WSAPOLLFD pfd{s, POLLWRNORM, 0};
                        const int ready = ::WSAPoll(&pfd, 1, static_cast<int>(timeout.count()));
                        if (ready == 1 && (pfd.revents & (POLLWRNORM | POLLERR)) != 0) {
                            int so_err{0};
                            int len = sizeof(so_err);
                            ::getsockopt(s, SOL_SOCKET, SO_ERROR, reinterpret_cast<char*>(&so_err), &len);
                            rc = so_err == 0 ? 0 : SOCKET_ERROR;
                            if (so_err != 0) ::WSASetLastError(so_err);
                        } else {
                            rc = SOCKET_ERROR;
                            if (ready == 0) ::WSASetLastError(WSAETIMEDOUT);
                        }
                    }
                    if (rc == 0) {
                        mode = 0;
                        ::ioctlsocket(s, FIONBIO, &mode);   // back to blocking for the data path
                        return s;
                    }
                    last_err = detail::wsa_error(::WSAGetLastError());
                    ::closesocket(s);
                }
                return std::unexpected(error::Error(TransErr::ConnectFailed, host + ":" + port_str + ": " + last_err));
            }

        public:

            TcpTransport() = default;
            TcpTransport(const TcpTransport&) = delete;
            TcpTransport& operator=(const TcpTransport&) = delete;
            TcpTransport(TcpTransport&& other) noexcept :
                sock{std::exchange(other.sock, INVALID_SOCKET)}
            { }
            TcpTransport& operator=(TcpTransport&& other) noexcept {
                if (this != &other) {
                    close();
                    sock = std::exchange(other.sock, INVALID_SOCKET);
                }
                return *this;
            }
            ~TcpTransport() { close(); }

            // data channel: no nagle, small send buffer (bytes already in the kernel can't be recalled on abort)
            static std::expected<TcpTransport, error::Error> connect_to(const std::string& host, uint16_t port, std::chrono::milliseconds timeout, bool data_channel) {
                const auto s = open_socket(host, port, timeout);
                if (!s) return std::unexpected(s.error());
                if (data_channel) {
                    BOOL one{TRUE};
                    ::setsockopt(*s, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&one), sizeof(one));
                    int sndbuf{4096};
                    ::setsockopt(*s, SOL_SOCKET, SO_SNDBUF, reinterpret_cast<const char*>(&sndbuf), sizeof(sndbuf));
                }
                return TcpTransport{*s};
            }

            std::expected<size_t, error::Error> write(std::span<const uint8_t> data) {
                size_t sent{0};
                while (sent < data.size()) {
                    const auto n = ::send(sock, reinterpret_cast<const char*>(data.data() + sent),
                        static_cast<int>(data.size() - sent), 0);
                    if (n == SOCKET_ERROR) return std::unexpected(error::Error(TransErr::WriteFailed, detail::wsa_error(::WSAGetLastError())));
                    sent += static_cast<size_t>(n);
                }
                return sent;
            }

            // returns 0 on timeout
            std::expected<size_t, error::Error> read(std::span<uint8_t> buf, std::chrono::milliseconds timeout) {
                WSAPOLLFD pfd{sock, POLLRDNORM, 0};
                const int ready = ::WSAPoll(&pfd, 1, static_cast<int>(timeout.count()));
                if (ready == SOCKET_ERROR) return std::unexpected(error::Error(TransErr::ReadFailed, detail::wsa_error(::WSAGetLastError())));
                if (ready == 0) return 0;
                const auto n = ::recv(sock, reinterpret_cast<char*>(buf.data()), static_cast<int>(buf.size()), 0);
                if (n == 0) return std::unexpected(error::Error(TransErr::PeerClosed));
                if (n == SOCKET_ERROR) {
                    const auto err = ::WSAGetLastError();
                    if (err == WSAEWOULDBLOCK) return 0;
                    return std::unexpected(error::Error(TransErr::ReadFailed, detail::wsa_error(err)));
                }
                return static_cast<size_t>(n);
            }

            // nothing to flush: bytes already handed to the kernel can't be recalled, which is why the send buffer is small
            void flush_tx() { }

            // the bridge paces RX in simulated cycles, the writer paces by profile timing instead of the socket queue
            size_t tx_pending() const { return 0; }

            // wakes a blocked recv/send from another thread
            void wake() {
                if (sock != INVALID_SOCKET) ::shutdown(sock, SD_BOTH);
            }

            void close() {
                if (sock != INVALID_SOCKET) {
                    ::closesocket(sock);
                    sock = INVALID_SOCKET;
                }
            }

    };

    // reset side channel: `RESET\n` on the bridge's reset port, the bridge pulses rst_n and answers `OK\n`
    inline std::expected<void, error::Error> send_reset(const std::string& host, uint16_t port, std::chrono::milliseconds timeout) {
        auto chan = TcpTransport::connect_to(host, port, timeout, false);
        if (!chan) return std::unexpected(error::Error(TransErr::ResetChannelFailed, chan.error().detail));

        constexpr std::string_view request{"RESET\n"};
        const auto sent = chan->write(std::span{reinterpret_cast<const uint8_t*>(request.data()), request.size()});
        if (!sent) return std::unexpected(error::Error(TransErr::ResetChannelFailed, sent.error().detail));

        std::string reply{};
        const auto deadline = std::chrono::steady_clock::now() + timeout;
        std::array<uint8_t, 64> buf{};
        while (reply.find('\n') == std::string::npos) {
            const auto now = std::chrono::steady_clock::now();
            if (now >= deadline) break;
            const auto left = std::chrono::duration_cast<std::chrono::milliseconds>(deadline - now);
            const auto got = chan->read(buf, std::max(left, std::chrono::milliseconds{1}));
            if (!got) break;    // bridge closed the channel, check what we have
            reply.append(reinterpret_cast<const char*>(buf.data()), *got);
        }
        if (const auto end = reply.find_first_of("\r\n"); end != std::string::npos) reply.resize(end);

        if (reply == "OK") return {};
        return std::unexpected(error::Error(TransErr::ResetRejected, reply.empty() ? std::string{"no reply"} : reply));
    }

}