#pragma once

#include <cstdint>
#include <expected>
#include <filesystem>
#include <vector>

#include "client.hpp"
#include "../headers/commands.hpp"
#include "../headers/error.hpp"
#include "../profile/profile.hpp"

namespace analyze_mod {

    // constants the BIOS doesn't report in its 0xDA reply
    inline constexpr uint32_t BIOS_DATA_TOP = 0x21FC0;          // dump/verify limit (end of BIOS data space + 1)
    inline constexpr uint32_t ECHO_BUF_SIZE = 256;              // BIOS echo buffer
    inline constexpr uint32_t PRG_TAIL_BYTES = 8;               // lui + jalr jump-back tail after every program
    inline constexpr uint32_t DEFAULT_PROG_OFFSET = 0x2000;     // used until device data has been fetched
    inline constexpr uint32_t DEFAULT_PROG_SIZE = 0x1F000;

    struct Context {
        const client_mod::Snapshot& snap;
        const profile_mod::Profile& profile;
        bool link_open;
    };

    // semantic checks against a snapshot of the state cache, so bad commands never reach the BIOS
    class CommandAnalyzer {

        private:

            std::expected<void, error::Error> require_transport(const Context& ctx) const;
            std::expected<void, error::Error> require_bios(const Context& ctx, bool allowed_when_limited) const;
            std::expected<void, error::Error> check_load(commands::CommandLoad& cmd, const Context& ctx) const;
            std::expected<void, error::Error> check_connect(const commands::CommandConnect& cmd, const Context& ctx) const;

        public:

            CommandAnalyzer() = default;
            std::expected<void, error::Error> analyze(commands::Command& cmd, const Context& ctx) const;

    };

    // .bin (raw) or .hex ($readmemh style, all 2 digit or all 8 digit tokens), zero padded to a multiple of 4
    std::expected<std::vector<uint8_t>, error::Error> read_program_image(const std::filesystem::path& path);

}