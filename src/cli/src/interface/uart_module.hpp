#pragma once

#include <chrono>
#include <concepts>
#include <cstdint>
#include <expected>
#include <functional>
#include <memory>
#include <span>
#include <stop_token>
#include <string>
#include <thread>
#include <variant>

#include "srl_transport.hpp"
#include "tcp_transport.hpp"
#include "../client/client.hpp"
#include "../headers/error.hpp"
#include "../headers/responses.hpp"

namespace interface_mod {

    // the common transport shape (replaces the deprecated transport.hpp), checked at compile time
    template <typename T>
    concept ByteTransport = requires(T& t, const T& ct, std::span<const uint8_t> out, std::span<uint8_t> in, std::chrono::milliseconds timeout) {
        { t.write(out) } -> std::same_as<std::expected<size_t, error::Error>>;
        { t.read(in, timeout) } -> std::same_as<std::expected<size_t, error::Error>>;
        { t.flush_tx() } -> std::same_as<void>;
        { ct.tx_pending() } -> std::convertible_to<size_t>;
        { t.wake() } -> std::same_as<void>;
        { t.close() } -> std::same_as<void>;
    };

    static_assert(ByteTransport<TcpTransport>);
    static_assert(ByteTransport<SerialTransport>);

    using Transport = std::variant<TcpTransport, SerialTransport>;
    using EventSink = std::function<void(responses::Events&&)>;

    // UART TX (writer thread) and RX (reader thread) around one open transport.
    // The writer is the only thread that writes to / flushes the transport, the reader the only one that reads it.
    // The transport is only swapped (open / close) while both threads are stopped.
    class Link {

        private:

            enum class PaceResult { Go, Abort, Stalled };

            client_mod::Session& session;
            EventSink sink;
            std::unique_ptr<Transport> transport;
            std::jthread writer;
            std::jthread reader;

            void start();
            void writer_loop(std::stop_token st);
            void reader_loop(std::stop_token st);
            void send_transaction(const client_mod::WriterJob& job, std::stop_token st);
            PaceResult pace(uint64_t gen, client_mod::TimePoint not_before, client_mod::Nanos stall_limit, std::stop_token st);

        public:

            Link(client_mod::Session& sess, EventSink event_sink);
            ~Link();
            Link(const Link&) = delete;
            Link& operator=(const Link&) = delete;

            std::expected<void, error::Error> open_tcp(const std::string& host, uint16_t port, std::chrono::milliseconds timeout);
            std::expected<void, error::Error> open_serial(const std::string& name, uint32_t baud);
            void close();
            bool is_open() const;

    };

}