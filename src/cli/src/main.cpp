#include "cli.hpp"

int main(int argc, char* argv[]) {
    cli_mod::Cli cli{};
    return cli.run(argc, argv);
}