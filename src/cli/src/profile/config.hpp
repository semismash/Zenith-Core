#include "profile.hpp"

#include <array>
#include <charconv>
#include <format>

// CLI configuration (the `config` command). Values live in the active profile, kept per profile.
// (saving between sessions with TOML can be added on top of list_settings/set_setting later)

namespace profile_mod {

    using error::Error;
    using SemErr = error::SemanticError;

    namespace {

        enum class Scope { Both, SimOnly, FpgaOnly };

        struct SettingInfo {
            std::string_view key;
            Scope scope;
        };

        inline constexpr std::array<SettingInfo, 6> settings{{
            { "cooldown_ms",    Scope::Both },
            { "sim_time_scale", Scope::SimOnly },
            { "host",           Scope::SimOnly },
            { "port",           Scope::SimOnly },
            { "reset_port",     Scope::SimOnly },
            { "serial_port",    Scope::FpgaOnly },
        }};

        const SettingInfo* find_setting(std::string_view key) {
            for (const auto& info : settings) {
                if (info.key == key) return &info;
            }
            return nullptr;
        }

        bool in_scope(const Profile& prof, Scope scope) {
            switch (scope) {
                case Scope::Both:       return true;
                case Scope::SimOnly:    return prof.kind == ProfileKind::Sim;
                case Scope::FpgaOnly:   return prof.kind == ProfileKind::Fpga;
            }
            return false;
        }

        std::expected<const SettingInfo*, Error> lookup(const Profile& prof, std::string_view key) {
            const auto* info = find_setting(key);
            if (info == nullptr) return std::unexpected(Error(SemErr::ConfigUnknownKey, std::string(key)));
            if (!in_scope(prof, info->scope)) return std::unexpected(Error(SemErr::ConfigWrongProfile, std::string(key)));
            return info;
        }

        std::expected<uint64_t, Error> parse_whole(std::string_view key, std::string_view text, uint64_t min, uint64_t max) {
            uint64_t value{0};
            const auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), value);
            if (ec != std::errc{} || ptr != text.data() + text.size() || value < min || value > max) {
                return std::unexpected(Error(SemErr::ConfigBadValue, std::format("{} = {} (allowed {} to {})", key, text, min, max)));
            }
            return value;
        }

    }

    std::vector<std::pair<std::string, std::string>> list_settings(const Profile& prof) {
        std::vector<std::pair<std::string, std::string>> out{};
        for (const auto& info : settings) {
            if (!in_scope(prof, info.scope)) continue;
            const auto value = get_setting(prof, info.key);
            out.emplace_back(std::string(info.key), value ? *value : std::string{});
        }
        return out;
    }

    std::expected<std::string, Error> get_setting(const Profile& prof, std::string_view key) {
        const auto info = lookup(prof, key);
        if (!info) return std::unexpected(info.error());

        if (key == "cooldown_ms")       return std::to_string(prof.cooldown_ms);
        if (key == "sim_time_scale")    return std::format("{}", prof.sim_time_scale);
        if (key == "host")              return prof.host;
        if (key == "port")              return std::to_string(prof.port);
        if (key == "reset_port")        return std::to_string(prof.reset_port);
        if (key == "serial_port")       return prof.serial_port;
        return std::unexpected(Error(SemErr::ConfigUnknownKey, std::string(key)));
    }

    std::expected<void, Error> set_setting(Profile& prof, std::string_view key, std::string_view value) {
        const auto info = lookup(prof, key);
        if (!info) return std::unexpected(info.error());

        if (key == "cooldown_ms") {
            const auto num = parse_whole(key, value, 1, 60000);
            if (!num) return std::unexpected(num.error());
            prof.cooldown_ms = static_cast<uint32_t>(*num);
            return {};
        }
        if (key == "sim_time_scale") {
            double scale{0.0};
            const auto [ptr, ec] = std::from_chars(value.data(), value.data() + value.size(), scale);
            if (ec != std::errc{} || ptr != value.data() + value.size() || !(scale > 0.0) || scale > 1.0e6) {
                return std::unexpected(Error(SemErr::ConfigBadValue, std::format("{} = {} (must be > 0)", key, value)));
            }
            prof.sim_time_scale = scale;
            return {};
        }
        if (key == "host") {
            if (value.empty()) return std::unexpected(Error(SemErr::ConfigBadValue, std::format("{} = (empty)", key)));
            prof.host = std::string(value);
            return {};
        }
        if (key == "port" || key == "reset_port") {
            const auto num = parse_whole(key, value, 1, 65535);
            if (!num) return std::unexpected(num.error());
            (key == "port" ? prof.port : prof.reset_port) = static_cast<uint16_t>(*num);
            return {};
        }
        if (key == "serial_port") {
            prof.serial_port = std::string(value);
            return {};
        }
        return std::unexpected(Error(SemErr::ConfigUnknownKey, std::string(key)));
    }

}