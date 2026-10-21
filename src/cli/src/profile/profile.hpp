#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "../headers/error.hpp"

namespace profile_mod {

    using Nanos = std::chrono::nanoseconds;
    using Seconds = std::chrono::duration<double>;

    enum class ProfileKind { Sim, Fpga };

    // everything that differs between the verilator sim (tcp) and the fpga (serial)
    // nothing else in the CLI branches on sim vs fpga, it all comes through here
    class Profile {

        public:

            ProfileKind kind;

            // settings, editable with `config` (see config.cpp)
            uint32_t cooldown_ms{500};
            double sim_time_scale{1.0};         // wall-clock seconds per simulated second
            std::string host{"127.0.0.1"};
            uint16_t port{5555};
            uint16_t reset_port{5556};
            std::string serial_port{};

            // fixed for now (9600 8N1, see Device Config in the protocol notes)
            static constexpr uint32_t BAUD_RATE = 9600;
            static constexpr size_t CHUNK_SIZE = 4;             // bytes per writer chunk, abort is checked between chunks
            static constexpr double BASE_RESPONSE_S = 2.0;      // response timeout on top of the transfer time
            static constexpr double CONNECT_TIMEOUT_S = 2.0;    // default SYN-ACK wait
            static constexpr double PROGRAM_NOTICE_S = 10.0;    // "program still running" hint
            static constexpr double READY_CAP_MIN_S = 2.0;      // ready signal cap, max(2 s, 4x floor)

            explicit Profile(ProfileKind k);

            std::string_view name() const;
            double time_scale() const;          // sim_time_scale in sim, 1.0 on the fpga
            Seconds byte_time() const;          // one byte on the wire, 10 bits (8N1)
            Nanos scaled(Seconds wall) const;

            Nanos response_timeout(size_t rx_bytes) const;
            Nanos cooldown_floor() const;
            Nanos ready_cap() const;
            Nanos fallback_time() const;
            Nanos chunk_gap(size_t bytes) const;
            Nanos program_notice() const;
            Nanos connect_timeout() const;
            Nanos tx_stall_limit() const;

    };

    class ProfileSet {

        public:

            Profile sim{ProfileKind::Sim};
            Profile fpga{ProfileKind::Fpga};
            ProfileKind active_kind{ProfileKind::Sim};

            Profile& active();
            const Profile& active() const;

    };

    // config.cpp
    std::vector<std::pair<std::string, std::string>> list_settings(const Profile& prof);
    std::expected<std::string, error::Error> get_setting(const Profile& prof, std::string_view key);
    std::expected<void, error::Error> set_setting(Profile& prof, std::string_view key, std::string_view value);

}