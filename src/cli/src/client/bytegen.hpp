#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <set>
#include <variant>
#include <vector>

#include "../headers/commands.hpp"
#include "../headers/responses.hpp"

namespace bytegen_mod {

    // which response frame the session waits for (see Response frames in the design doc)
    enum class Expect {
        SynAck,             // AA       -> F0 0A, AB
        ConnectAck,         // AC       -> [message, POST results], F0 00 | F0 50
        Echo,               // 3A 3D .. -> F0 03, 3A 3D len bytes 3F, F0 00
        SelfTest,           // 5A       -> F0 05, 50, message, POST results, F0 00 | F0 50
        TelemetrySet,       // 7A .. 7A -> F0 07, F0 00
        TelemetryQuery,     // 7A 7A    -> F0 07, 70 v 71 v 72 v, F0 00
        TelemetryStatus,    // 7D       -> F0 07, 7D 4x[param u32] 7D, F0 00
        MemDump,            // 8A s o   -> F0 08, 8C data, F0 00
        Verify,             // CB       -> F0 08, 8C data, F0 00
        Load,               // CA ..    -> F0 0C, CA, [CB 8C data], [run], F0 00
        Run,                // CC       -> F0 1C, output, F0 2C, [75 frame], F0 00
        DeviceData,         // DA       -> F0 0D, DA, 11 params, F0 00
    };

    // one BIOS round trip. A command is one or more of these, run one after the other by the shell
    struct Transaction {
        Expect expect{Expect::Echo};
        std::vector<uint8_t> bytes{};
        bool quiet{false};                              // update the cache only, print nothing (connect / sync)

        uint32_t data_offset{0};                        // dump / verify / load: address of the data
        uint32_t data_size{0};                          // dump / verify / load: byte count

        bool load_verify{false};
        bool load_run{false};
        responses::LoadArgs load_args{};

        std::optional<bool> tele_bios{};                // telemetry set: what was sent, applied to the cache on success
        std::optional<bool> tele_prog_reset{};

        std::optional<std::chrono::nanoseconds> timeout_override{};     // connect --timeout
        std::shared_ptr<const std::vector<uint8_t>> compare_image{};    // load -v / verify: compare the read-back
        std::set<commands::DeviceDataParam> dd_filter{};
        std::variant<bool, std::set<commands::TelemetryParam>> tele_filter{true};
    };

    void put_u32(std::vector<uint8_t>& out, uint32_t value);    // little endian, like send_word/get_word
    size_t expected_rx_bytes(const Transaction& tx);           // sizes the response timeout

    Transaction make_connect_syn(std::optional<std::chrono::nanoseconds> timeout);
    Transaction make_connect_ack();
    std::vector<Transaction> make_sync();                       // quiet device data + telemetry query

    // BIOS-interfacing commands -> transactions, empty for client side commands
    std::vector<Transaction> build(const commands::Command& cmd, const responses::DeviceCache& cache);

}