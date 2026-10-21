#pragma once

namespace cli_mod {

    // top level: program arguments, loads messages.toml, wires session / link / shell together
    class Cli {

        public:

            Cli() = default;
            int run(int argc, char** argv);

    };

}