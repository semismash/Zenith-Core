#pragma once

#include <cstdint>
#include <span>
#include <optional>
#include <chrono>

namespace transport {

    class Transport {
        
    };

    class ITransport {
        virtual bool send(std::span<const uint8_t>) = 0;
        virtual std::optional<uint8_t> recv(std::chrono::milliseconds timeout) = 0;
    };

    enum class TransportError {

    };

}