#pragma once

#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <deque>
#include <expected>
#include <mutex>
#include <optional>
#include <span>
#include <stop_token>
#include <string>
#include <vector>

#include "bytegen.hpp"
#include "../headers/error.hpp"
#include "../headers/responses.hpp"
#include "../profile/profile.hpp"

namespace client_mod {

    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;
    using Nanos = std::chrono::nanoseconds;

    enum class SessionState {
        Disconnected,       // no handshake yet (the transport may already be open)
        Idle,
        Sending,
        AwaitingResponse,
        ProgramRunning,
        Cooldown,
    };

    enum class TxOutcome {
        Pending,
        Ok,
        ProgramRunning,     // the program started, the shell gets its prompt back
        BiosError,
        Timeout,
        ProtocolError,
        Rebooted,
        LinkLost,
        Refused,            // never submitted (shell side)
    };

    struct WriterJob {
        uint64_t generation;
        uint64_t seq;               // transaction sequence number, 0 for raw bytes
        bool raw;
        std::vector<uint8_t> bytes;
        size_t chunk;
        Nanos gap;                  // pause after every chunk
        Nanos stall_limit;
    };

    struct RawByte {
        uint8_t byte;
        Nanos gap;                  // pause after this byte (sendbytes --interval)
    };

    // copied out under the lock for the shell / command analyzer
    struct Snapshot {
        SessionState state;
        bool transport_open;
        bool linked;
        bool limited;
        responses::DeviceCache cache;
        bool monitor_on;
        bool log_on;
        std::vector<uint8_t> raw_pending;
    };

    // response analyzer stages: boundary stages expect a frame to start, data stages eat fixed size data
    enum class Stage {
        None,               // nothing being waited on, unsolicited bytes
        AwaitOwnState,      // waiting for F0 <own state> (idle heartbeats before it are ignored)
        SynAck,             // AB
        PostBody,           // message frame, then 5C/5E, or straight to F0 00 / F0 50
        PostResultsHdr,     // 5D
        PostPairs,          // 6x [test, result]
        PostFinish,         // 5F
        EchoHeader,         // 3A
        EchoBody,           // 3D len bytes, 3F
        SelfTestByte,       // 50
        Completion,         // F0 00 / F0 50
        TeleQuery,          // 70 v 71 v 72 v
        TeleStatusOpen,     // 7D
        TeleStatusBody,     // 4x [param, u32]
        TeleStatusClose,    // 7D
        MemConfirm,         // 8C
        MemData,            // raw bytes
        LoadComplete,       // CA
        LoadVerifyHdr,      // CB
        Program,            // program output until F0 2C
        AfterProgram,       // 75 register frame, or F0 00
        RegFrame,           // 31x [reg, u32], 75
        DdHeader,           // DA
        DdBody,             // 00 str, 01 str, 02..0A [param, u32]
    };

    // pure logic: state + byte + time in, events out. No locks, no io, so recorded BIOS byte
    // sequences can be replayed straight into it in unit tests
    class SessionCore {

        private:

            enum class DdPhase { Param, StrStart, Word };

            struct StrFrame {
                bool active{false};
                uint8_t len_bytes{0};
                uint32_t len{0};
                uint32_t got{0};
            };

            // state machine
            SessionState state{SessionState::Disconnected};
            bool transport_open{false};
            bool linked{false};
            bool limited{false};            // BIOS in the POST-fail idle (F0 50)
            bool expect_boot{false};        // swallow the 0x50 boot byte after a sim reset
            uint64_t generation{0};
            uint64_t tx_seq{0};
            uint64_t done_seq{0};
            TxOutcome outcome{TxOutcome::Ok};
            std::optional<bytegen_mod::Transaction> active{};
            bool job_taken{false};

            profile_mod::Profile profile;
            responses::DeviceCache cache{};
            std::string message_buffer{};
            bool monitor_on{false};
            bool log_on{false};

            std::deque<RawByte> raw_queue{};
            TimePoint raw_next{};
            TimePoint last_host_write{};

            // timers
            std::optional<TimePoint> response_deadline{};
            std::optional<TimePoint> program_notice_at{};
            std::optional<TimePoint> hold_deadline{};
            TimePoint cooldown_start{};
            bool cooldown_ready{false};
            bool cooldown_f0{false};

            // response analyzer
            Stage stage{Stage::None};
            uint8_t own_state{0};
            Stage after_own{Stage::None};
            bool pending_f0{false};
            std::optional<uint8_t> pending_err{};
            std::vector<uint8_t> data_buf{};
            StrFrame str{};
            uint32_t mem_expected{0};
            uint32_t mem_offset{0};
            bool mem_readback{false};
            bool mem_then_run{false};
            responses::PostResults post{};
            responses::TelemetryCounters counters{};
            responses::DeviceData dd{};
            uint8_t dd_next{0};
            DdPhase dd_phase{DdPhase::Param};
            uint32_t dd_word{0};
            uint8_t dd_word_bytes{0};
            std::string prog_hold{};        // F0 / 50 / 50 F0 held back in program output until the next byte

            SessionState idle_state() const;
            bool raw_allowed() const;
            bool quiet() const;
            TimePoint floor_end() const;
            TimePoint cap_end() const;

            void reset_parser();
            void begin_parse(const bytegen_mod::Transaction& tx);
            void expect_state(uint8_t state_byte, Stage next);
            void enter(Stage next, responses::Events& ev, TimePoint now);
            void finish(TxOutcome result);
            void finish_ok(responses::Events& ev);
            void apply_completion(const bytegen_mod::Transaction& tx, responses::Events& ev);
            void start_cooldown(responses::Events& ev, TimePoint now, TxOutcome result);
            void check_cooldown(responses::Events& ev, TimePoint now);
            void end_cooldown(responses::Events& ev, bool by_fallback);
            void on_reboot(responses::Events& ev);
            void protocol_mismatch(uint8_t byte, responses::Events& ev, TimePoint now);
            void bios_error_frame(uint8_t family, uint8_t code, responses::Events& ev, TimePoint now);

            void boundary_byte(uint8_t byte, responses::Events& ev, TimePoint now);
            bool accept(uint8_t byte, responses::Events& ev, TimePoint now);
            bool data_byte(uint8_t byte, responses::Events& ev, TimePoint now);
            void dd_byte(uint8_t byte, responses::Events& ev, TimePoint now);
            void state_byte(uint8_t st, responses::Events& ev, TimePoint now);
            void cooldown_byte(uint8_t byte, responses::Events& ev, TimePoint now);
            void program_byte(uint8_t byte, responses::Events& ev, TimePoint now);
            void str_byte(uint8_t byte, responses::Events& ev, TimePoint now);
            void start_str();
            void str_complete();
            void test_byte(responses::Events& ev);
            void enter_program(responses::Events& ev, TimePoint now);
            void program_done(responses::Events& ev, TimePoint now);
            void load_complete(responses::Events& ev, TimePoint now);
            void mem_complete(responses::Events& ev, TimePoint now);
            void store_dd_word(uint8_t param, uint32_t value);
            void emit_output(responses::Events& ev, uint8_t byte);
            void flush_hold(responses::Events& ev);
            void flush_message(responses::Events& ev);

        public:

            explicit SessionCore(const profile_mod::Profile& prof);

            // shell side
            std::expected<uint64_t, error::Error> submit(bytegen_mod::Transaction tx);
            std::expected<void, error::Error> enqueue_raw(std::span<const uint8_t> bytes, Nanos gap);
            bool finished(uint64_t seq) const;
            TxOutcome outcome_for(uint64_t seq) const;
            Snapshot snapshot() const;
            void set_monitor(bool on);
            void set_log(bool on);
            void set_profile(const profile_mod::Profile& prof);
            void transport_opened();
            void transport_closed();
            void reset_for_switch(const profile_mod::Profile& prof);
            void after_sim_reset();

            // writer side
            std::optional<WriterJob> take_job();
            std::optional<WriterJob> take_raw(TimePoint now);
            bool tx_job_ready() const;
            bool raw_ready() const;
            TimePoint raw_next_time() const;
            void writer_done(uint64_t seq, TimePoint now);
            void note_host_write(TimePoint now);
            uint64_t current_generation() const;

            // reader side
            responses::Events on_byte(uint8_t byte, TimePoint now);
            responses::Events on_tick(TimePoint now);
            responses::Events on_link_lost(std::string detail);
            std::optional<TimePoint> next_deadline() const;

    };

    // the single shared object: one mutex + one condition variable around the core.
    // No transport io and no printing happens while the mutex is held
    class Session {

        private:

            mutable std::mutex mtx;
            std::condition_variable_any cv;
            SessionCore core;

        public:

            explicit Session(const profile_mod::Profile& prof);

            // shell
            std::expected<uint64_t, error::Error> submit(bytegen_mod::Transaction tx);
            TxOutcome wait_done(uint64_t seq);
            Snapshot snapshot() const;
            std::expected<void, error::Error> enqueue_raw(std::span<const uint8_t> bytes, Nanos gap);
            void set_monitor(bool on);
            void set_log(bool on);
            void set_profile(const profile_mod::Profile& prof);
            void transport_opened();
            void transport_closed();
            void reset_for_switch(const profile_mod::Profile& prof);
            void after_sim_reset();

            // writer
            std::optional<WriterJob> writer_next(std::stop_token st);
            bool writer_wait(uint64_t gen, TimePoint until, std::stop_token st);
            bool gen_current(uint64_t gen) const;
            void note_host_write(TimePoint now);
            void writer_done(uint64_t seq, TimePoint now);

            // reader
            responses::Events on_bytes(std::span<const uint8_t> bytes, TimePoint now);
            responses::Events on_link_lost(std::string detail);
            std::chrono::milliseconds read_timeout(TimePoint now) const;

    };

}