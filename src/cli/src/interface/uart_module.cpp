#include "uart_module.hpp"

#include <algorithm>
#include <array>

namespace interface_mod {

    using client_mod::Clock;
    using client_mod::TimePoint;

    Link::Link(client_mod::Session& sess, EventSink event_sink) :
        session{sess},
        sink{std::move(event_sink)},
        transport{},
        writer{},
        reader{}
    { }

    Link::~Link() {
        close();
    }

    std::expected<void, error::Error> Link::open_tcp(const std::string& host, uint16_t port, std::chrono::milliseconds timeout) {
        close();
        auto tcp = TcpTransport::connect_to(host, port, timeout, true);
        if (!tcp) return std::unexpected(tcp.error());
        transport = std::make_unique<Transport>(std::in_place_type<TcpTransport>, std::move(*tcp));
        session.transport_opened();
        start();
        return {};
    }

    std::expected<void, error::Error> Link::open_serial(const std::string& name, uint32_t baud) {
        close();
        auto srl = SerialTransport::open_port(name, baud);
        if (!srl) return std::unexpected(srl.error());
        transport = std::make_unique<Transport>(std::in_place_type<SerialTransport>, std::move(*srl));
        session.transport_opened();
        start();
        return {};
    }

    void Link::start() {
        writer = std::jthread([this](std::stop_token st) { writer_loop(st); });
        reader = std::jthread([this](std::stop_token st) { reader_loop(st); });
    }

    // stop both threads first (stop token + wake a blocked read), only then touch the transport
    void Link::close() {
        if (!transport) return;
        writer.request_stop();
        reader.request_stop();
        std::visit([](auto& t) { t.wake(); }, *transport);
        if (writer.joinable()) writer.join();
        if (reader.joinable()) reader.join();
        std::visit([](auto& t) { t.close(); }, *transport);
        transport.reset();
        session.transport_closed();
    }

    bool Link::is_open() const {
        return transport != nullptr;
    }

    void Link::writer_loop(std::stop_token st) {
        while (!st.stop_requested()) {
            const auto job = session.writer_next(st);
            if (!job) continue;     // only on shutdown

            if (job->raw) {         // sendbyte / sendbytes, the gap is enforced by the session
                const auto res = std::visit([&job](auto& t) { return t.write(job->bytes); }, *transport);
                if (!res) {
                    sink(session.on_link_lost(res.error().detail));
                    return;
                }
                session.note_host_write(Clock::now());
                continue;
            }
            send_transaction(*job, st);
        }
    }

    // chunks of <= 4 bytes at the profile's pacing, the generation is checked between every chunk
    void Link::send_transaction(const client_mod::WriterJob& job, std::stop_token st) {
        auto next = Clock::now();
        size_t sent{0};
        int last_percent{-1};
        for (size_t pos{0}; pos < job.bytes.size(); pos += job.chunk) {
            const auto paced = pace(job.generation, next, job.stall_limit, st);
            if (paced == PaceResult::Abort) {
                // the reader saw an error: drop whatever is still queued and leave the state alone
                // (and so the progress counter, reported below, simply stops where it was)
                std::visit([](auto& t) { t.flush_tx(); }, *transport);
                return;
            }
            if (paced == PaceResult::Stalled) {
                sink(session.on_link_lost("transmit buffer is not draining"));
                return;
            }
            const auto len = std::min(job.chunk, job.bytes.size() - pos);
            const auto chunk = std::span<const uint8_t>{job.bytes}.subspan(pos, len);
            const auto res = std::visit([chunk](auto& t) { return t.write(chunk); }, *transport);
            if (!res) {
                sink(session.on_link_lost(res.error().detail));
                return;
            }
            const auto now = Clock::now();
            session.note_host_write(now);
            next = now + job.gap;

            if (job.report_progress) {
                sent += len;
                const auto percent = static_cast<int>(sent * 100 / job.bytes.size());
                if (percent != last_percent) {
                    last_percent = percent;
                    responses::Events ev{};
                    ev.push_back(responses::EvLoadProgress{static_cast<uint32_t>(percent)});
                    sink(std::move(ev));
                }
            }
        }
        session.writer_done(job.seq, Clock::now());
    }

    // waits for the pacing gap and (serial) for the OS buffer to drain, so an abort never has much queued
    Link::PaceResult Link::pace(uint64_t gen, TimePoint not_before, client_mod::Nanos stall_limit, std::stop_token st) {
        const auto drain_start = Clock::now();
        while (true) {
            if (!session.gen_current(gen) || st.stop_requested()) return PaceResult::Abort;
            const auto now = Clock::now();
            const size_t pending = std::visit([](const auto& t) -> size_t { return t.tx_pending(); }, *transport);
            if (pending == 0 && now >= not_before) return PaceResult::Go;
            if (pending > 0 && now - drain_start > stall_limit) return PaceResult::Stalled;
            const auto until = pending > 0 ? now + std::chrono::milliseconds{1} : not_before;
            if (!session.writer_wait(gen, until, st)) return PaceResult::Abort;
        }
    }

    void Link::reader_loop(std::stop_token st) {
        std::array<uint8_t, 512> buf{};
        while (!st.stop_requested()) {
            const auto timeout = session.read_timeout(Clock::now());
            const auto res = std::visit([&buf, timeout](auto& t) { return t.read(buf, timeout); }, *transport);
            if (st.stop_requested()) break;     // a deliberate close also makes the read fail, don't report that
            if (!res) {
                sink(session.on_link_lost(res.error().detail));
                return;
            }
            auto events = session.on_bytes(std::span<const uint8_t>{buf.data(), *res}, Clock::now());
            if (!events.empty()) sink(std::move(events));
        }
    }

}