#include "cmdparse.hpp"

#include <algorithm>
#include <cctype>
#include <charconv>
#include <format>

namespace cmdparse_mod {

    using error::Error;
    using ParseErr = error::ParseError;
    using namespace commands;

    namespace {

        std::string to_lower(std::string_view text) {
            std::string out{text};
            std::ranges::transform(out, out.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            return out;
        }

        std::string_view trim(std::string_view text) {
            while (!text.empty() && std::isspace(static_cast<unsigned char>(text.front()))) text.remove_prefix(1);
            while (!text.empty() && std::isspace(static_cast<unsigned char>(text.back()))) text.remove_suffix(1);
            return text;
        }

        // on/off/true/false for monitor and log
        std::expected<std::optional<bool>, Error> parse_toggle(const std::optional<std::string>& arg) {
            if (!arg) return std::optional<bool>{};
            const auto value = to_lower(*arg);
            if (value == "on" || value == "true") return std::optional<bool>{true};
            if (value == "off" || value == "false") return std::optional<bool>{false};
            return std::unexpected(Error(ParseErr::InvalidToggle, *arg));
        }

        std::expected<std::optional<bool>, Error> parse_opt_bool(const std::optional<std::string>& arg) {
            if (!arg) return std::optional<bool>{};
            const auto value = parse_bool(*arg);
            if (!value) return std::unexpected(value.error());
            return std::optional<bool>{*value};
        }

        std::expected<std::set<DeviceDataParam>, Error> parse_info(std::string_view text) {
            std::set<DeviceDataParam> out{};
            for (const auto& item : parse_list(text)) {
                const auto name = to_lower(item);
                if (name == "arch") out.insert(DeviceDataParam::Arch);
                else if (name == "reg") out.insert(DeviceDataParam::Reg);
                else if (name == "rom") out.insert(DeviceDataParam::ROM);
                else if (name == "ram") out.insert(DeviceDataParam::RAM);
                else if (name == "mem") out.insert(DeviceDataParam::Mem);
                else if (name == "clk") out.insert(DeviceDataParam::Clk);
                else if (name == "baud") out.insert(DeviceDataParam::Baud);
                else return std::unexpected(Error(ParseErr::InvalidInfoParam, item));
            }
            return out;
        }

        std::expected<std::set<TelemetryParam>, Error> parse_telemetry(std::string_view text) {
            std::set<TelemetryParam> out{};
            for (const auto& item : parse_list(text)) {
                const auto name = to_lower(item);
                if (name == "cycles") out.insert(TelemetryParam::Cycles);
                else if (name == "instr") out.insert(TelemetryParam::Instr);
                else if (name == "stall") out.insert(TelemetryParam::Stall);
                else if (name == "stallpcnt") out.insert(TelemetryParam::StallPcnt);
                else if (name == "cpi") out.insert(TelemetryParam::Cpi);
                else if (name == "loaduse") out.insert(TelemetryParam::LoadUseStall);
                else if (name == "brflush") out.insert(TelemetryParam::BranchFlush);
                else return std::unexpected(Error(ParseErr::InvalidTelemetryParam, item));
            }
            if (out.empty()) return std::unexpected(Error(ParseErr::InvalidTelemetryParam, std::string(text)));
            return out;
        }

        std::expected<std::vector<uint8_t>, Error> parse_bytes(std::string_view text) {
            std::vector<uint8_t> out{};
            for (const auto& item : parse_list(text)) {
                const auto value = parse_uint(item, 0xFF);
                if (!value) return std::unexpected(Error(ParseErr::InvalidByteList, item));
                out.push_back(static_cast<uint8_t>(*value));
            }
            return out;
        }

        // "host", "host:port" or ":port"
        std::expected<CommandNet, Error> parse_net(const std::optional<std::string>& arg) {
            CommandNet cmd{};
            if (!arg) return cmd;
            const std::string_view text{*arg};
            const auto colon = text.rfind(':');
            const auto host = colon == std::string_view::npos ? text : text.substr(0, colon);
            if (!host.empty()) cmd.host = std::string(host);
            if (colon != std::string_view::npos) {
                const auto port = parse_uint(text.substr(colon + 1), 65535);
                if (!port || *port == 0) return std::unexpected(Error(ParseErr::InvalidHostPort, *arg));
                cmd.port = static_cast<uint16_t>(*port);
            }
            if (!cmd.host && !cmd.port) return std::unexpected(Error(ParseErr::InvalidHostPort, *arg));
            return cmd;
        }

    }

    // 0x.. hex, 0b.. binary, decimal otherwise
    std::expected<uint64_t, Error> parse_uint(std::string_view text, uint64_t max) {
        auto digits = trim(text);
        int base{10};
        if (digits.size() > 2 && digits[0] == '0' && (digits[1] == 'x' || digits[1] == 'X')) {
            base = 16;
            digits.remove_prefix(2);
        } else if (digits.size() > 2 && digits[0] == '0' && (digits[1] == 'b' || digits[1] == 'B')) {
            base = 2;
            digits.remove_prefix(2);
        }
        if (digits.empty()) return std::unexpected(Error(ParseErr::InvalidNumber, std::string(text)));

        uint64_t value{0};
        const auto [ptr, ec] = std::from_chars(digits.data(), digits.data() + digits.size(), value, base);
        if (ec == std::errc::result_out_of_range) return std::unexpected(Error(ParseErr::NumberOutOfRange, std::string(text)));
        if (ec != std::errc{} || ptr != digits.data() + digits.size()) return std::unexpected(Error(ParseErr::InvalidNumber, std::string(text)));
        if (value > max) return std::unexpected(Error(ParseErr::NumberOutOfRange, std::format("{} (max {})", text, max)));
        return value;
    }

    std::expected<bool, Error> parse_bool(std::string_view text) {
        const auto value = to_lower(trim(text));
        if (value == "true" || value == "on" || value == "1") return true;
        if (value == "false" || value == "off" || value == "0") return false;
        return std::unexpected(Error(ParseErr::InvalidBool, std::string(text)));
    }

    std::expected<double, Error> parse_seconds(std::string_view text) {
        const auto digits = trim(text);
        double value{0.0};
        const auto [ptr, ec] = std::from_chars(digits.data(), digits.data() + digits.size(), value);
        if (ec != std::errc{} || ptr != digits.data() + digits.size() || !(value > 0.0) || value > 86400.0) {
            return std::unexpected(Error(ParseErr::InvalidSeconds, std::string(text)));
        }
        return value;
    }

    std::vector<std::string> parse_list(std::string_view text) {
        auto body = trim(text);
        if (!body.empty() && body.front() == '[') body.remove_prefix(1);
        if (!body.empty() && body.back() == ']') body.remove_suffix(1);
        std::vector<std::string> out{};
        size_t start{0};
        while (start <= body.size()) {
            const auto comma = body.find(',', start);
            const auto item = trim(body.substr(start, comma == std::string_view::npos ? std::string_view::npos : comma - start));
            if (!item.empty()) out.emplace_back(item);
            if (comma == std::string_view::npos) break;
            start = comma + 1;
        }
        return out;
    }

    // whitespace split, "double" / 'single' quotes group (\n \t \\ \" in double quotes),
    // [ ... ] groups too so --bytes=[0x1, 0x2] stays one token
    std::expected<std::vector<std::string>, Error> CommandParser::tokenize(std::string_view line) {
        std::vector<std::string> tokens{};
        std::string cur{};
        bool in_token{false};
        char quote{0};
        int bracket{0};

        for (size_t i{0}; i < line.size(); ++i) {
            const char c = line[i];
            if (quote != 0) {
                if (c == quote) {
                    quote = 0;
                } else if (c == '\\' && quote == '"' && i + 1 < line.size()) {
                    const char next = line[++i];
                    switch (next) {
                        case 'n':   cur.push_back('\n'); break;
                        case 't':   cur.push_back('\t'); break;
                        case '\\':  cur.push_back('\\'); break;
                        case '"':   cur.push_back('"'); break;
                        default:    cur.push_back('\\'); cur.push_back(next); break;
                    }
                } else {
                    cur.push_back(c);
                }
                continue;
            }
            if (c == '"' || c == '\'') {
                quote = c;
                in_token = true;
                continue;
            }
            if (c == '[') ++bracket;
            if (c == ']') {
                if (bracket == 0) return std::unexpected(Error(ParseErr::UnterminatedBracket, std::string(line)));
                --bracket;
            }
            if (std::isspace(static_cast<unsigned char>(c)) && bracket == 0) {
                if (in_token) {
                    tokens.push_back(std::move(cur));
                    cur.clear();
                    in_token = false;
                }
                continue;
            }
            cur.push_back(c);
            in_token = true;
        }
        if (quote != 0) return std::unexpected(Error(ParseErr::UnterminatedQuote));
        if (bracket != 0) return std::unexpected(Error(ParseErr::UnterminatedBracket, std::string(line)));
        if (in_token) tokens.push_back(std::move(cur));
        return tokens;
    }

    const std::vector<std::string>& CommandParser::command_names() {
        static const std::vector<std::string> names{
            "about", "clear", "config", "connect", "deviceinfo", "echo", "exit", "github", "help", "hexdump",
            "load", "log", "monitor", "net", "quit", "reset", "run", "scan", "selftest", "sendbyte", "sendbytes",
            "status", "switch", "sync", "telemetry", "verify"
        };
        return names;
    }

    CommandParser::CommandParser() :
        st{},
        app{"zenith"},
        subs{}
    {
        app.set_help_flag();    // `help` is our own command, messages come from messages.toml
        app.require_subcommand(1);

        subs.config = app.add_subcommand("config");
        subs.config->add_option("args", st.config_args);

        subs.switch_profile = app.add_subcommand("switch");
        subs.switch_profile->add_option("profile", st.switch_target)->required();

        subs.reset = app.add_subcommand("reset");

        subs.net = app.add_subcommand("net");
        subs.net->add_option("target", st.net_target);

        subs.scan = app.add_subcommand("scan");

        subs.connect = app.add_subcommand("connect");
        subs.connect->add_option("port", st.connect_port);
        subs.connect->add_option("--timeout", st.connect_timeout);
        subs.connect->add_option("--retry", st.connect_retry);

        subs.load = app.add_subcommand("load");
        subs.load->add_option("file", st.load_file)->required();
        subs.load->add_flag("-r,--run", st.load_run);
        subs.load->add_flag("-v,--verify", st.load_verify);
        subs.load->add_option("--offset", st.load_offset);
        subs.load->add_option("--telemode", st.load_telemode);
        subs.load->add_option("--telereset", st.load_telereset);
        subs.load->add_option("--register", st.load_register);

        subs.run = app.add_subcommand("run");
        subs.verify = app.add_subcommand("verify");

        subs.telemetry = app.add_subcommand("telemetry");
        subs.telemetry->add_option("--mode", st.tele_mode);
        subs.telemetry->add_option("--reset", st.tele_reset);
        subs.telemetry->add_flag("-r", st.tele_inst_reset);

        subs.monitor = app.add_subcommand("monitor");
        subs.monitor->add_option("state", st.monitor_arg);

        subs.log = app.add_subcommand("log");
        subs.log->add_option("state", st.log_arg);

        subs.echo = app.add_subcommand("echo");
        subs.echo->add_option("message", st.echo_words);
        subs.echo->add_flag("-t", st.echo_terminal);

        subs.deviceinfo = app.add_subcommand("deviceinfo");
        subs.deviceinfo->add_option("--info", st.info_list);

        subs.sync = app.add_subcommand("sync");

        subs.sendbyte = app.add_subcommand("sendbyte");
        subs.sendbyte->add_option("byte", st.sendbyte_value)->required();

        subs.sendbytes = app.add_subcommand("sendbytes");
        subs.sendbytes->add_option("--bytes", st.sendbytes_list);
        subs.sendbytes->add_option("--interval", st.sendbytes_interval);

        subs.status = app.add_subcommand("status");
        subs.status->add_flag("-t", st.status_all);
        subs.status->add_option("--telemetry", st.status_list);

        subs.selftest = app.add_subcommand("selftest");

        subs.hexdump = app.add_subcommand("hexdump");
        subs.hexdump->add_option("--offset", st.dump_offset)->required();
        subs.hexdump->add_option("--size", st.dump_size)->required();

        subs.clear = app.add_subcommand("clear");

        subs.help = app.add_subcommand("help");
        subs.help->add_option("command", st.help_topic);

        subs.about = app.add_subcommand("about");
        subs.github = app.add_subcommand("github");

        subs.exit = app.add_subcommand("exit");
        subs.exit->alias("quit");
    }

    std::expected<Command, Error> CommandParser::parse(std::string_view line) {
        auto tokens = tokenize(line);
        if (!tokens) return std::unexpected(tokens.error());

        st = Storage{};     // CLI11 doesn't reset bound variables on clear()
        app.clear();
        std::vector<std::string> args{tokens->rbegin(), tokens->rend()};   // CLI11 takes them in reverse order
        try {
            app.parse(args);
        } catch (const CLI::ParseError& err) {
            return std::unexpected(Error(ParseErr::CommandSyntax, err.what()));
        }
        return build();
    }

    std::expected<Command, Error> CommandParser::build() const {

        if (app.got_subcommand(subs.config)) {
            if (st.config_args.size() > 2) return std::unexpected(Error(ParseErr::TooManyArgs, "config [key] [value]"));
            CommandConfig cmd{};
            if (!st.config_args.empty()) cmd.key = st.config_args[0];
            if (st.config_args.size() == 2) cmd.value = st.config_args[1];
            return Command{cmd};
        }

        if (app.got_subcommand(subs.switch_profile)) {
            const auto target = to_lower(st.switch_target);
            if (target != "sim" && target != "fpga") return std::unexpected(Error(ParseErr::InvalidProfile, st.switch_target));
            return Command{CommandSwitch{ target == "fpga" }};
        }

        if (app.got_subcommand(subs.reset)) return Command{CommandReset{}};
        if (app.got_subcommand(subs.scan)) return Command{CommandScan{}};

        if (app.got_subcommand(subs.net)) {
            auto cmd = parse_net(st.net_target);
            if (!cmd) return std::unexpected(cmd.error());
            return Command{*cmd};
        }

        if (app.got_subcommand(subs.connect)) {
            CommandConnect cmd{};
            cmd.port_name = st.connect_port;
            if (st.connect_timeout) {
                const auto secs = parse_seconds(*st.connect_timeout);
                if (!secs) return std::unexpected(secs.error());
                cmd.timeout_s = *secs;
            }
            if (st.connect_retry) {
                const auto secs = parse_seconds(*st.connect_retry);
                if (!secs) return std::unexpected(secs.error());
                cmd.retry_s = *secs;
            }
            return Command{cmd};
        }

        if (app.got_subcommand(subs.load)) {
            CommandLoad cmd{ st.load_file, st.load_run, st.load_verify, std::nullopt, true, true, false, nullptr };
            if (st.load_offset) {
                const auto offset = parse_uint(*st.load_offset, 0xFFFFFFFF);
                if (!offset) return std::unexpected(offset.error());
                cmd.start_addr = static_cast<uint32_t>(*offset);
            }
            // telemode / telereset are on by default (the console's job, the BIOS defaults to off)
            const auto telemode = parse_opt_bool(st.load_telemode);
            if (!telemode) return std::unexpected(telemode.error());
            const auto telereset = parse_opt_bool(st.load_telereset);
            if (!telereset) return std::unexpected(telereset.error());
            const auto reg_disp = parse_opt_bool(st.load_register);
            if (!reg_disp) return std::unexpected(reg_disp.error());
            cmd.telemode = telemode->value_or(true);
            cmd.telereset = telereset->value_or(true);
            cmd.reg_disp = reg_disp->value_or(false);
            return Command{std::move(cmd)};
        }

        if (app.got_subcommand(subs.run)) return Command{CommandRun{}};
        if (app.got_subcommand(subs.verify)) return Command{CommandVerify{}};

        if (app.got_subcommand(subs.telemetry)) {
            const auto mode = parse_opt_bool(st.tele_mode);
            if (!mode) return std::unexpected(mode.error());
            const auto reset = parse_opt_bool(st.tele_reset);
            if (!reset) return std::unexpected(reset.error());
            return Command{CommandTelemetry{ *mode, *reset, st.tele_inst_reset }};
        }

        if (app.got_subcommand(subs.monitor)) {
            const auto toggle = parse_toggle(st.monitor_arg);
            if (!toggle) return std::unexpected(toggle.error());
            return Command{CommandMonitor{ *toggle }};
        }

        if (app.got_subcommand(subs.log)) {
            const auto toggle = parse_toggle(st.log_arg);
            if (!toggle) return std::unexpected(toggle.error());
            return Command{CommandLog{ *toggle }};
        }

        if (app.got_subcommand(subs.echo)) {
            std::string msg{};     // unquoted words are joined back with single spaces
            for (size_t i{0}; i < st.echo_words.size(); ++i) {
                if (i > 0) msg.push_back(' ');
                msg += st.echo_words[i];
            }
            return Command{CommandEcho{ std::move(msg), st.echo_terminal }};
        }

        if (app.got_subcommand(subs.deviceinfo)) {
            CommandDeviceInfo cmd{};
            if (st.info_list) {
                auto info = parse_info(*st.info_list);
                if (!info) return std::unexpected(info.error());
                cmd.device_data_args = std::move(*info);
            }
            return Command{cmd};
        }

        if (app.got_subcommand(subs.sync)) return Command{CommandSync{}};

        if (app.got_subcommand(subs.sendbyte)) {
            const auto value = parse_uint(st.sendbyte_value, 0xFF);
            if (!value) return std::unexpected(value.error());
            return Command{CommandSendByte{ static_cast<uint8_t>(*value) }};
        }

        if (app.got_subcommand(subs.sendbytes)) {
            CommandSendByteList cmd{ std::nullopt, 1 };
            if (st.sendbytes_list) {
                auto bytes = parse_bytes(*st.sendbytes_list);
                if (!bytes) return std::unexpected(bytes.error());
                cmd.tx_byte_list = std::move(*bytes);
            }
            if (st.sendbytes_interval) {
                const auto interval = parse_uint(*st.sendbytes_interval, 1000000);
                if (!interval) return std::unexpected(interval.error());
                cmd.interval = static_cast<uint32_t>(*interval);
            }
            return Command{std::move(cmd)};
        }

        if (app.got_subcommand(subs.status)) {
            if (st.status_all && st.status_list) return std::unexpected(Error(ParseErr::ConflictingFlags, "-t / --telemetry"));
            CommandTelemetryStatus cmd{ true };     // plain `status` shows everything, same as -t
            if (st.status_list) {
                auto params = parse_telemetry(*st.status_list);
                if (!params) return std::unexpected(params.error());
                cmd.telemetry_args = std::move(*params);
            }
            return Command{std::move(cmd)};
        }

        if (app.got_subcommand(subs.selftest)) return Command{CommandSelfTest{}};

        if (app.got_subcommand(subs.hexdump)) {
            const auto offset = parse_uint(st.dump_offset, 0xFFFFFFFF);
            if (!offset) return std::unexpected(offset.error());
            const auto size = parse_uint(st.dump_size, 0xFFFFFFFF);
            if (!size) return std::unexpected(size.error());
            return Command{CommandHexDump{ static_cast<uint32_t>(*size), static_cast<uint32_t>(*offset) }};
        }

        if (app.got_subcommand(subs.clear)) return Command{CommandClear{}};
        if (app.got_subcommand(subs.help)) return Command{CommandHelp{ st.help_topic }};
        if (app.got_subcommand(subs.about)) return Command{CommandAbout{}};
        if (app.got_subcommand(subs.github)) return Command{CommandGitHub{}};
        if (app.got_subcommand(subs.exit)) return Command{CommandExit{}};

        return std::unexpected(Error(ParseErr::CommandSyntax, "unknown command"));
    }

}