#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <replxx.hxx>

#include "cmdparse.hpp"
#include "responseprint.hpp"
#include "../client/bytegen.hpp"
#include "../client/client.hpp"
#include "../client/cmd_analyze.hpp"
#include "../headers/commands.hpp"
#include "../interface/uart_module.hpp"
#include "../profile/profile.hpp"

namespace shell_mod {

    // shell thread (main): reads a line, parses it, checks it, submits it, waits until the session is idle again
    class Shell {

        private:

            replxx::Replxx rx;
            const print_mod::Messages& msgs;
            print_mod::Printer& printer;
            client_mod::Session& session;
            interface_mod::Link& link;
            profile_mod::ProfileSet& profiles;
            cmdparse_mod::CommandParser parser;
            analyze_mod::CommandAnalyzer analyzer;
            bool running;

            std::shared_ptr<const std::vector<uint8_t>> last_image;    // compared against by `verify`
            uint32_t last_image_offset;

            void execute(commands::Command& cmd);
            void housekeeping();
            client_mod::TxOutcome run_transactions(std::vector<bytegen_mod::Transaction> txs);
            bool sleep_interruptible(double seconds);

            void do_config(const commands::CommandConfig& cmd);
            void do_switch(const commands::CommandSwitch& cmd);
            void do_net(const commands::CommandNet& cmd);
            void do_scan();
            void do_reset();
            void do_connect(const commands::CommandConnect& cmd);
            void do_load(const commands::Command& cmd, const commands::CommandLoad& load);
            void do_verify(const commands::Command& cmd);
            void do_sync();
            void do_monitor(const commands::CommandMonitor& cmd);
            void do_log(const commands::CommandLog& cmd);
            void do_sendbyte(const commands::CommandSendByte& cmd);
            void do_sendbytes(const commands::CommandSendByteList& cmd);
            void do_help(const commands::CommandHelp& cmd);

        public:

            Shell(const print_mod::Messages& messages, print_mod::Printer& print, client_mod::Session& sess,
                  interface_mod::Link& lnk, profile_mod::ProfileSet& profs);
            int run();

    };

}