#pragma once

#include <cstdint>
#include <expected>
#include <format>
#include <mutex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "../headers/error.hpp"
#include "../headers/responses.hpp"

namespace replxx { class Replxx; }

namespace print_mod {

    // every string the shell prints, loaded from messages.toml (embedded into the binary at build time)
    class Messages {

        private:

            std::unordered_map<std::string, std::string> table;

        public:

            Messages() = default;
            std::expected<void, std::string> load(std::string_view toml_text);
            bool contains(std::string_view key) const;
            std::string get(std::string_view key) const;

            // std::format with the text from messages.toml, falls back to the raw text if the arguments don't fit
            template <typename... Args>
            std::string fmt(std::string_view key, const Args&... args) const {
                const auto pattern = get(key);
                try {
                    return std::vformat(pattern, std::make_format_args(args...));
                } catch (const std::format_error&) {
                    return pattern;
                }
            }

    };

    // the only way anything reaches the terminal. Own mutex (the print mutex), never taken while the
    // session mutex is held. Goes through replxx so the reader can print while the prompt is open
    class Printer {

        private:

            const Messages& msgs;
            std::mutex mtx;
            replxx::Replxx* rx{nullptr};
            bool at_line_start{true};
            uint64_t last_progress_step{~0ull};    // see render_progress: which 10%-step was last printed

            void emit(std::string_view text);
            void emit_line(std::string_view text);
            void render(const responses::Event& ev);
            void render_progress(const std::string& text, uint64_t done, uint64_t total);
            void render_post(const responses::PostResults& post);
            void render_dump(uint32_t offset, const std::vector<uint8_t>& data);
            void render_device(const responses::EvDeviceData& info);
            void render_status(const responses::EvTelemetryStatus& status);
            void render_registers(const responses::EvRegisters& regs);
            std::string on_off(std::optional<bool> value) const;
            std::string state_name(uint8_t state) const;

        public:

            explicit Printer(const Messages& messages);
            void attach(replxx::Replxx* replxx);
            void print(const responses::Events& events);
            void line(std::string_view text);
            void error(const error::Error& err);
            void clear_screen();

            template <typename... Args>
            void say(std::string_view key, const Args&... args) {
                line(msgs.fmt(key, args...));
            }

    };

}