#include "shell.hpp"

#include <algorithm>
#include <cctype>
#include <cerrno>
#include <chrono>
#include <csignal>
#include <cstdio>
#include <format>
#include <iostream>
#include <string>
#include <thread>

#include "../headers/codes.hpp"
#include "../headers/overload.hpp"

namespace shell_mod {

    using client_mod::TxOutcome;
    using profile_mod::ProfileKind;

    namespace {

        // Ctrl+C while the prompt is open is a key press (replxx clears the line). While a command
        // blocks the shell it arrives as SIGINT: it only stops a `connect --retry` loop, a running
        // command can't be aborted (the CPU has no interrupts)
        volatile std::sig_atomic_t interrupt_flag{0};

        void on_sigint(int) {
            interrupt_flag = 1;
        }

        std::string trim(std::string_view text) {
            while (!text.empty() && std::isspace(static_cast<unsigned char>(text.front()))) text.remove_prefix(1);
            while (!text.empty() && std::isspace(static_cast<unsigned char>(text.back()))) text.remove_suffix(1);
            return std::string(text);
        }

        std::string hex_list(const std::vector<uint8_t>& bytes) {
            std::string out{};
            for (size_t i{0}; i < bytes.size(); ++i) {
                if (i > 0) out += ", ";
                out += std::format("0x{:02X}", bytes[i]);
            }
            return out;
        }

    }

    Shell::Shell(const print_mod::Messages& messages, print_mod::Printer& print, client_mod::Session& sess,
                 interface_mod::Link& lnk, profile_mod::ProfileSet& profs) :
        rx{},
        msgs{messages},
        printer{print},
        session{sess},
        link{lnk},
        profiles{profs},
        parser{},
        analyzer{},
        running{true},
        last_image{},
        last_image_offset{0}
    { }

    // While a program is running, BIOS/program output keeps streaming in from a background thread at
    // the same time the user is typing (sendbyte to feed the program, say). replxx's print() is meant
    // to be safe to call from another thread while input() is reading keystrokes, but in practice the
    // two can still corrupt each other's line redraw (seen firsthand: output text truncated mid-word,
    // fused with whatever the user was typing). Neither side is at fault in an obviously fixable way
    // from here, so the two are kept from ever touching the terminal at the same time at all: while a
    // program is running, input switches to a plain blocking read with no line-redraw logic of its own
    // (so a concurrent background print can't corrupt it, just land before or after it), and the
    // printer is detached from replxx so it falls back to the same plain stdout writes. Normal replxx
    // editing (history, tab-complete, arrow keys) resumes as soon as the program finishes.
    std::optional<std::string> Shell::read_line(const std::string& prompt) {
        if (session.snapshot().state != client_mod::SessionState::ProgramRunning) {
            errno = 0;
            const char* input = rx.input(prompt);
            if (input == nullptr) {
                if (errno == EAGAIN) return std::string{};    // Ctrl+C: line cleared, keep going
                return std::nullopt;                          // Ctrl+D / EOF
            }
            return std::string{input};
        }

        printer.attach(nullptr);
        std::fputs(prompt.c_str(), stdout);
        std::fflush(stdout);
        std::string line{};
        const bool ok = static_cast<bool>(std::getline(std::cin, line));
        printer.attach(&rx);
        if (!ok) {
            if (std::cin.eof()) return std::nullopt;    // Ctrl+D / EOF
            std::cin.clear();                            // a signal or similar transient interruption
            return std::string{};
        }
        return line;
    }

    int Shell::run() {
        std::signal(SIGINT, on_sigint);
        printer.attach(&rx);
        rx.install_window_change_handler();
        rx.set_max_history_size(256);
        rx.set_completion_callback([](const std::string& input, int& context_len) {
            replxx::Replxx::completions_t out{};
            if (input.find(' ') != std::string::npos) return out;  // only the command name is completed
            context_len = static_cast<int>(input.size());
            for (const auto& name : cmdparse_mod::CommandParser::command_names()) {
                if (name.starts_with(input)) out.emplace_back(name);
            }
            return out;
        });

        printer.say("shell.banner", profiles.active().name());
        const auto prompt = msgs.get("prompt.input");

        while (running) {
            const auto raw_line = read_line(prompt);
            if (!raw_line) break;                  // Ctrl+D / EOF
            const auto line = trim(*raw_line);
            if (line.empty()) continue;
            rx.history_add(line);

            auto cmd = parser.parse(line);
            if (!cmd) {
                printer.error(cmd.error());
                continue;
            }
            execute(*cmd);
        }

        link.close();
        printer.say("shell.bye");
        printer.attach(nullptr);
        return 0;
    }

    // a reader that lost the link stops by itself, the transport is cleaned up here before the next command
    void Shell::housekeeping() {
        if (link.is_open() && !session.snapshot().transport_open) link.close();
    }

    void Shell::execute(commands::Command& cmd) {
        using namespace commands;
        housekeeping();

        const auto snap = session.snapshot();
        const analyze_mod::Context ctx{ snap, profiles.active(), link.is_open() };
        if (auto res = analyzer.analyze(cmd, ctx); !res) {
            printer.error(res.error());
            return;
        }

        std::visit(overload{
            [this](const CommandConfig& c) { do_config(c); },
            [this](const CommandSwitch& c) { do_switch(c); },
            [this](const CommandReset&) { do_reset(); },
            [this](const CommandNet& c) { do_net(c); },
            [this](const CommandScan&) { do_scan(); },
            [this](const CommandConnect& c) { do_connect(c); },
            [this, &cmd](const CommandLoad& c) { do_load(cmd, c); },
            [this, &cmd](const CommandVerify&) { do_verify(cmd); },
            [this](const CommandSync&) { do_sync(); },
            [this](const CommandMonitor& c) { do_monitor(c); },
            [this](const CommandLog& c) { do_log(c); },
            [this](const CommandSendMsg& c) { do_sendmsg(c); },
            [this](const CommandSendByte& c) { do_sendbyte(c); },
            [this](const CommandSendByteList& c) { do_sendbytes(c); },
            [this](const CommandHelp& c) { do_help(c); },
            [this](const CommandClear&) { printer.clear_screen(); },
            [this](const CommandAbout&) { printer.line(msgs.get("about.text")); },
            [this](const CommandGitHub&) {
                const auto url = msgs.get("github.url");
                if (url.empty()) printer.say("github.none");
                else printer.say("github.text", url);
            },
            [this](const CommandExit&) { running = false; },
            [this](const CommandEcho& c) {
                if (c.terminal_echo) printer.line(c.msg);    // -t: straight to the terminal, the BIOS never sees it
                else run_transactions(bytegen_mod::build(Command{c}, session.snapshot().cache));
            },
            // remaining BIOS commands: selftest, telemetry, status, hexdump, run, deviceinfo
            [this, &cmd](const auto&) { run_transactions(bytegen_mod::build(cmd, session.snapshot().cache)); },
        }, cmd);
    }

    // submit one transaction after the other, stop at the first one that doesn't complete normally
    TxOutcome Shell::run_transactions(std::vector<bytegen_mod::Transaction> txs) {
        auto result{TxOutcome::Ok};
        for (auto& tx : txs) {
            const auto seq = session.submit(std::move(tx));
            if (!seq) {
                printer.error(seq.error());
                return TxOutcome::Refused;
            }
            result = session.wait_done(*seq);   // the reader prints the response (and any error) meanwhile
            if (result != TxOutcome::Ok) return result;
        }
        return result;
    }

    bool Shell::sleep_interruptible(double seconds) {
        const auto until = std::chrono::steady_clock::now() + std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<double>{seconds});
        while (std::chrono::steady_clock::now() < until) {
            if (interrupt_flag != 0) return false;
            std::this_thread::sleep_for(std::chrono::milliseconds{50});
        }
        return interrupt_flag == 0;
    }

    void Shell::do_config(const commands::CommandConfig& cmd) {
        auto& prof = profiles.active();
        if (!cmd.key) {
            printer.say("config.header", prof.name());
            for (const auto& [key, value] : profile_mod::list_settings(prof)) printer.say("config.entry", key, value);
            return;
        }
        if (!cmd.value) {
            const auto value = profile_mod::get_setting(prof, *cmd.key);
            if (!value) printer.error(value.error());
            else printer.say("config.entry", *cmd.key, *value);
            return;
        }
        if (auto res = profile_mod::set_setting(prof, *cmd.key, *cmd.value); !res) {
            printer.error(res.error());
            return;
        }
        session.set_profile(prof);
        const auto value = profile_mod::get_setting(prof, *cmd.key);
        printer.say("config.set", *cmd.key, value ? *value : *cmd.value);
    }

    // closes the transport, clears the cache, loads the profile, leaves the session disconnected
    void Shell::do_switch(const commands::CommandSwitch& cmd) {
        link.close();
        profiles.active_kind = cmd.fpga_else_sim ? ProfileKind::Fpga : ProfileKind::Sim;
        session.reset_for_switch(profiles.active());
        last_image.reset();
        printer.say("shell.switched", profiles.active().name());
    }

    void Shell::do_net(const commands::CommandNet& cmd) {
        const auto& prof = profiles.active();
        const auto host = cmd.host.value_or(prof.host);
        const auto port = cmd.port.value_or(prof.port);
        if (auto res = link.open_tcp(host, port, std::chrono::milliseconds{3000}); !res) {
            printer.error(res.error());
            return;
        }
        printer.say("shell.net_ok", host, port);
    }

    void Shell::do_scan() {
        const auto ports = interface_mod::SerialTransport::scan();
        if (!ports) {
            printer.error(ports.error());
            return;
        }
        if (ports->empty()) {
            printer.say("scan.none");
            return;
        }
        printer.say("scan.header");
        for (const auto& port : *ports) {
            if (port.usb_id) printer.say("scan.entry_usb", port.name, port.description, port.usb_id->first, port.usb_id->second);
            else printer.say("scan.entry", port.name, port.description);
        }
        printer.say("scan.hint");
    }

    void Shell::do_reset() {
        const auto& prof = profiles.active();
        if (prof.kind == ProfileKind::Fpga) {
            printer.say("shell.reset_fpga");
            return;
        }
        const auto timeout = std::max(std::chrono::milliseconds{2000}, std::chrono::duration_cast<std::chrono::milliseconds>(prof.scaled(profile_mod::Seconds{2.0})));
        if (auto res = interface_mod::send_reset(prof.host, prof.reset_port, timeout); !res) {
            printer.error(res.error());
            return;
        }
        session.after_sim_reset();
        last_image.reset();
        printer.say("shell.reset_ok");
    }

    // AA -> AB, then AC -> [POST results] -> F0 00 / F0 50, then a quiet sync of the device data cache
    void Shell::do_connect(const commands::CommandConnect& cmd) {
        const auto& prof = profiles.active();
        if (prof.kind == ProfileKind::Fpga && !link.is_open()) {
            const auto port = cmd.port_name.value_or(prof.serial_port);
            if (auto res = link.open_serial(port, profile_mod::Profile::BAUD_RATE); !res) {
                printer.error(res.error());
                return;
            }
            printer.say("shell.serial_ok", port);
        }

        const auto timeout = cmd.timeout_s
            ? std::chrono::duration_cast<client_mod::Nanos>(profile_mod::Seconds{*cmd.timeout_s})
            : prof.connect_timeout();

        interrupt_flag = 0;
        while (true) {
            printer.say("shell.connecting");
            const auto result = run_transactions({ bytegen_mod::make_connect_syn(timeout), bytegen_mod::make_connect_ack() });
            if (result == TxOutcome::Ok) break;
            if (!cmd.retry_s || interrupt_flag != 0 || !session.snapshot().transport_open) {
                printer.say("shell.connect_failed");
                return;
            }
            printer.say("shell.connect_retry", *cmd.retry_s);
            if (!sleep_interruptible(*cmd.retry_s)) {
                printer.say("shell.connect_stopped");
                return;
            }
        }

        if (session.snapshot().limited) {
            printer.say("shell.connected_limited");     // only connect / selftest work, no device data either
            return;
        }
        printer.say("shell.connected");
        if (run_transactions(bytegen_mod::make_sync()) != TxOutcome::Ok) printer.say("shell.sync_failed");
    }

    void Shell::do_load(const commands::Command& cmd, const commands::CommandLoad& load) {
        const auto result = run_transactions(bytegen_mod::build(cmd, session.snapshot().cache));
        const auto snap = session.snapshot();
        const bool loaded = (result == TxOutcome::Ok || result == TxOutcome::ProgramRunning)
            && snap.cache.program_valid && load.image && snap.cache.program_size == load.image->size();
        if (loaded) {
            last_image = load.image;
            last_image_offset = snap.cache.program_offset;
        } else {
            last_image.reset();
        }
    }

    // compares against the last loaded image when it is still the program the BIOS has
    void Shell::do_verify(const commands::Command& cmd) {
        const auto snap = session.snapshot();
        auto txs = bytegen_mod::build(cmd, snap.cache);
        if (!txs.empty() && last_image && snap.cache.program_offset == last_image_offset
            && snap.cache.program_size == last_image->size()) {
            txs.front().compare_image = last_image;
        }
        run_transactions(std::move(txs));
    }

    void Shell::do_sync() {
        if (run_transactions(bytegen_mod::make_sync()) == TxOutcome::Ok) printer.say("shell.sync_ok");
    }

    void Shell::do_monitor(const commands::CommandMonitor& cmd) {
        if (cmd.is_monitor) session.set_monitor(*cmd.is_monitor);
        printer.say("shell.monitor_status", msgs.get(session.snapshot().monitor_on ? "word.on" : "word.off"));
    }

    // client side only, the BIOS always sends its state updates
    void Shell::do_log(const commands::CommandLog& cmd) {
        if (cmd.is_log) session.set_log(*cmd.is_log);
        printer.say("shell.log_status", msgs.get(session.snapshot().log_on ? "word.on" : "word.off"));
    }

    // same frame as echo's (0x3D, 4-byte LE length, ascii), minus the leading 0x3A: this isn't a BIOS
    // command, it goes straight into the running program's UART RX, so there's no BIOS reply to wait for
    void Shell::do_sendmsg(const commands::CommandSendMsg& cmd) {
        std::vector<uint8_t> bytes{bios_protocol::TB_MSG_STR};
        bytegen_mod::put_u32(bytes, static_cast<uint32_t>(cmd.msg.size()));
        bytes.insert(bytes.end(), cmd.msg.begin(), cmd.msg.end());
        if (auto res = session.enqueue_raw(bytes, profiles.active().chunk_gap(1), client_mod::Clock::now()); !res) {
            printer.error(res.error());
            return;
        }
        // always program-running-only (enforced by the analyzer), so a "queued" confirmation is
        // always noise here, and one less print() call racing with the program's own streaming output
    }

    void Shell::do_sendbyte(const commands::CommandSendByte& cmd) {
        const uint8_t byte[1]{cmd.tx_byte};
        if (auto res = session.enqueue_raw(byte, profiles.active().chunk_gap(1), client_mod::Clock::now()); !res) {
            printer.error(res.error());
            return;
        }
        // skip the confirmation while a program is running: it's mostly used there to feed a program's
        // input, often in quick succession, and the text just adds noise (and another background print)
        if (session.snapshot().state != client_mod::SessionState::ProgramRunning) printer.say("shell.raw_queued", 1);
    }

    // --interval is in 10 baud ticks, i.e. byte-times
    void Shell::do_sendbytes(const commands::CommandSendByteList& cmd) {
        if (!cmd.tx_byte_list) {
            const auto pending = session.snapshot().raw_pending;
            if (pending.empty()) printer.say("shell.raw_pending_none");
            else printer.say("shell.raw_pending", pending.size(), hex_list(pending));
            return;
        }
        if (auto res = session.enqueue_raw(*cmd.tx_byte_list, profiles.active().chunk_gap(cmd.interval), client_mod::Clock::now()); !res) {
            printer.error(res.error());
            return;
        }
        printer.say("shell.raw_queued", cmd.tx_byte_list->size());
    }

    void Shell::do_help(const commands::CommandHelp& cmd) {
        if (!cmd.topic) {
            printer.line(msgs.get("help.general"));
            return;
        }
        const auto key = std::format("help.{}", *cmd.topic == "quit" ? std::string{"exit"} : *cmd.topic);
        if (msgs.contains(key)) printer.line(msgs.get(key));
        else printer.say("help.unknown", *cmd.topic);
    }

}