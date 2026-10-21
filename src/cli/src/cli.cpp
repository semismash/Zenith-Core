#include "cli.hpp"

#include <csignal>
#include <cstdio>
#include <string>

#include <CLI11.hpp>

#include "client/client.hpp"
#include "headers/messages_embed.hpp"
#include "interface/uart_module.hpp"
#include "profile/profile.hpp"
#include "shell/responseprint.hpp"
#include "shell/shell.hpp"

namespace cli_mod {

    int Cli::run(int argc, char** argv) {
        CLI::App args{"Zenith Core BIOS CLI"};
        std::string profile_name{"sim"};
        args.add_option("-p,--profile", profile_name, "starting profile: sim (TCP to the Verilator bridge) or fpga (serial)");
        try {
            args.parse(argc, argv);
        } catch (const CLI::ParseError& err) {
            return args.exit(err);
        }
        if (profile_name != "sim" && profile_name != "fpga") {
            std::fprintf(stderr, "unknown profile '%s' (sim or fpga)\n", profile_name.c_str());
            return 1;
        }

#ifdef SIGPIPE
        std::signal(SIGPIPE, SIG_IGN);  // a bridge that goes away must not kill the CLI, the reader reports it instead (POSIX only, Windows sockets don't raise it)
#endif

        print_mod::Messages messages{};
        if (auto res = messages.load(messages_embed::messages_toml); !res) {
            std::fprintf(stderr, "messages.toml could not be loaded: %s\n", res.error().c_str());
            return 1;
        }

        profile_mod::ProfileSet profiles{};
        profiles.active_kind = profile_name == "fpga" ? profile_mod::ProfileKind::Fpga : profile_mod::ProfileKind::Sim;

        // declaration order = teardown order in reverse: the shell closes the link and detaches replxx before it goes
        print_mod::Printer printer{messages};
        client_mod::Session session{profiles.active()};
        interface_mod::Link link{session, [&printer](responses::Events&& events) { printer.print(events); }};
        shell_mod::Shell shell{messages, printer, session, link, profiles};

        return shell.run();
    }

}