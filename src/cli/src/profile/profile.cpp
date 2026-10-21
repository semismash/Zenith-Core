#include "profile.hpp"

#include <algorithm>

namespace profile_mod {

    using std::chrono::duration_cast;

    Profile::Profile(ProfileKind k) :
        kind{k}
    { }

    std::string_view Profile::name() const {
        return kind == ProfileKind::Sim ? "sim" : "fpga";
    }

    double Profile::time_scale() const {
        return kind == ProfileKind::Sim ? sim_time_scale : 1.0;
    }

    Seconds Profile::byte_time() const {
        return Seconds{10.0 / static_cast<double>(BAUD_RATE)};  // start + 8 data + stop
    }

    Nanos Profile::scaled(Seconds wall) const {
        return duration_cast<Nanos>(wall * time_scale());
    }

    // timeouts scale with how much the BIOS still has to send, so a big dump doesn't time out halfway
    Nanos Profile::response_timeout(size_t rx_bytes) const {
        return scaled(Seconds{BASE_RESPONSE_S} + byte_time() * (2.0 * static_cast<double>(rx_bytes)));
    }

    // at least cooldown_ms (wall-clock), never shorter than 10 byte-times
    Nanos Profile::cooldown_floor() const {
        const auto floor = duration_cast<Nanos>(std::chrono::milliseconds{cooldown_ms});
        return std::max(floor, scaled(byte_time() * 10.0));
    }

    // max(2 s, 4x floor), scaled by sim_time_scale
    Nanos Profile::ready_cap() const {
        const Seconds floor_s = std::max(Seconds{static_cast<double>(cooldown_ms) / 1000.0}, byte_time() * 10.0);
        return scaled(std::max(Seconds{READY_CAP_MIN_S}, floor_s * 4.0));
    }

    Nanos Profile::fallback_time() const {
        return scaled(byte_time() * 10.0);
    }

    Nanos Profile::chunk_gap(size_t bytes) const {
        return scaled(byte_time() * static_cast<double>(bytes));
    }

    Nanos Profile::program_notice() const {
        return scaled(Seconds{PROGRAM_NOTICE_S});
    }

    Nanos Profile::connect_timeout() const {
        return scaled(Seconds{CONNECT_TIMEOUT_S});
    }

    // how long the OS tx buffer may refuse to drain before the link is considered dead
    Nanos Profile::tx_stall_limit() const {
        return response_timeout(64);
    }

    Profile& ProfileSet::active() {
        return active_kind == ProfileKind::Sim ? sim : fpga;
    }

    const Profile& ProfileSet::active() const {
        return active_kind == ProfileKind::Sim ? sim : fpga;
    }

}