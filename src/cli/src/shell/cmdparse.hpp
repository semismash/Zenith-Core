#pragma once

#include <cstdint>
#include <expected>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <CLI11.hpp>

#include "../headers/commands.hpp"
#include "../headers/error.hpp"

namespace cmdparse_mod {

    // parse helpers (numbers as strings, hex/binary through charconv)
    std::expected<uint64_t, error::Error> parse_uint(std::string_view text, uint64_t max);
    std::expected<bool, error::Error> parse_bool(std::string_view text);
    std::expected<double, error::Error> parse_seconds(std::string_view text);
    std::vector<std::string> parse_list(std::string_view text);    // "[a, b, c]" or "a,b,c"

    // one CLI11 app reused for every line (app.clear() in between)
    class CommandParser {

        private:

            // everything CLI11 writes into, reset before every line
            struct Storage {
                std::vector<std::string> config_args{};
                std::string switch_target{};
                std::optional<std::string> net_target{};
                std::optional<std::string> connect_port{};
                std::optional<std::string> connect_timeout{};
                std::optional<std::string> connect_retry{};
                std::string load_file{};
                bool load_run{false};
                bool load_verify{false};
                std::optional<std::string> load_offset{};
                std::optional<std::string> load_telemode{};
                std::optional<std::string> load_telereset{};
                std::optional<std::string> load_register{};
                std::optional<std::string> tele_mode{};
                std::optional<std::string> tele_reset{};
                bool tele_inst_reset{false};
                std::optional<std::string> monitor_arg{};
                std::optional<std::string> log_arg{};
                std::vector<std::string> echo_words{};
                bool echo_terminal{false};
                std::optional<std::string> info_list{};
                std::string sendbyte_value{};
                std::optional<std::string> sendbytes_list{};
                std::optional<std::string> sendbytes_interval{};
                bool status_all{false};
                std::optional<std::string> status_list{};
                std::string dump_offset{};
                std::string dump_size{};
                std::optional<std::string> help_topic{};
            };

            struct Subcommands {
                CLI::App* config{nullptr};
                CLI::App* switch_profile{nullptr};
                CLI::App* reset{nullptr};
                CLI::App* net{nullptr};
                CLI::App* scan{nullptr};
                CLI::App* connect{nullptr};
                CLI::App* load{nullptr};
                CLI::App* run{nullptr};
                CLI::App* verify{nullptr};
                CLI::App* telemetry{nullptr};
                CLI::App* monitor{nullptr};
                CLI::App* log{nullptr};
                CLI::App* echo{nullptr};
                CLI::App* deviceinfo{nullptr};
                CLI::App* sync{nullptr};
                CLI::App* sendbyte{nullptr};
                CLI::App* sendbytes{nullptr};
                CLI::App* status{nullptr};
                CLI::App* selftest{nullptr};
                CLI::App* hexdump{nullptr};
                CLI::App* clear{nullptr};
                CLI::App* help{nullptr};
                CLI::App* about{nullptr};
                CLI::App* github{nullptr};
                CLI::App* exit{nullptr};
            };

            Storage st;         // declared before app, CLI11 keeps references into it
            CLI::App app;
            Subcommands subs;

            std::expected<commands::Command, error::Error> build() const;

        public:

            CommandParser();
            CommandParser(const CommandParser&) = delete;
            CommandParser& operator=(const CommandParser&) = delete;

            std::expected<commands::Command, error::Error> parse(std::string_view line);
            static std::expected<std::vector<std::string>, error::Error> tokenize(std::string_view line);
            static const std::vector<std::string>& command_names();     // tab completion

    };

}