#pragma once

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <expected>
#include <optional>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include <libserialport.h>

#include "../headers/error.hpp"

// serial transport, used by the fpga profile (Arty A7 FTDI bridge, 9600 8N1, no flow control)

namespace interface_mod {

    using SrlErr = error::TransportError;

    struct PortInfo {
        std::string name;
        std::string description;
        std::optional<std::pair<int, int>> usb_id;  // vid, pid
    };

    class SerialTransport {

        private:

            sp_port* port{nullptr};
            bool opened{false};

            explicit SerialTransport(sp_port* p) :
                port{p},
                opened{false}
            { }

            static std::string last_error() {
                char* msg = sp_last_error_message();
                std::string text{msg != nullptr ? msg : "unknown error"};
                sp_free_error_message(msg);
                return text;
            }

        public:

            SerialTransport() = default;
            SerialTransport(const SerialTransport&) = delete;
            SerialTransport& operator=(const SerialTransport&) = delete;
            SerialTransport(SerialTransport&& other) noexcept :
                port{std::exchange(other.port, nullptr)},
                opened{std::exchange(other.opened, false)}
            { }
            SerialTransport& operator=(SerialTransport&& other) noexcept {
                if (this != &other) {
                    close();
                    port = std::exchange(other.port, nullptr);
                    opened = std::exchange(other.opened, false);
                }
                return *this;
            }
            ~SerialTransport() { close(); }

            static std::expected<SerialTransport, error::Error> open_port(const std::string& name, uint32_t baud) {
                sp_port* found{nullptr};
                if (sp_get_port_by_name(name.c_str(), &found) != SP_OK) {
                    return std::unexpected(error::Error(SrlErr::SerialOpenFailed, name + ": " + last_error()));
                }
                SerialTransport srl{found};     // owns the port from here on, close() frees it
                if (sp_open(found, SP_MODE_READ_WRITE) != SP_OK) {
                    return std::unexpected(error::Error(SrlErr::SerialOpenFailed, name + ": " + last_error()));
                }
                srl.opened = true;

                const bool configured =
                    sp_set_baudrate(found, static_cast<int>(baud)) == SP_OK &&
                    sp_set_bits(found, 8) == SP_OK &&
                    sp_set_parity(found, SP_PARITY_NONE) == SP_OK &&
                    sp_set_stopbits(found, 1) == SP_OK &&
                    sp_set_flowcontrol(found, SP_FLOWCONTROL_NONE) == SP_OK;
                if (!configured) {
                    return std::unexpected(error::Error(SrlErr::SerialConfigFailed, name + ": " + last_error()));
                }
                sp_flush(found, SP_BUF_BOTH);  // drop anything stale from before we opened it
                return srl;
            }

            std::expected<size_t, error::Error> write(std::span<const uint8_t> data) {
                const int rc = sp_blocking_write(port, data.data(), data.size(), 1000);
                if (rc < 0) return std::unexpected(error::Error(SrlErr::SerialIoFailed, last_error()));
                if (static_cast<size_t>(rc) != data.size()) return std::unexpected(error::Error(SrlErr::TxStalled, "serial write timed out"));
                return static_cast<size_t>(rc);
            }

            // returns as soon as any bytes arrived, 0 on timeout (a timeout of 0 would block forever in libserialport)
            std::expected<size_t, error::Error> read(std::span<uint8_t> buf, std::chrono::milliseconds timeout) {
                const auto ms = static_cast<unsigned int>(std::max<int64_t>(timeout.count(), 1));
                const int rc = sp_blocking_read_next(port, buf.data(), buf.size(), ms);
                if (rc < 0) return std::unexpected(error::Error(SrlErr::SerialIoFailed, last_error()));
                return static_cast<size_t>(rc);
            }

            // drop everything not yet on the wire (abort after a BIOS error)
            void flush_tx() {
                if (port != nullptr) sp_flush(port, SP_BUF_OUTPUT);
            }

            size_t tx_pending() const {
                if (port == nullptr) return 0;
                const int rc = sp_output_waiting(port);
                return rc > 0 ? static_cast<size_t>(rc) : 0;
            }

            // reads already time out after ~50 ms, nothing to wake
            void wake() { }

            void close() {
                if (port != nullptr) {
                    if (opened) sp_close(port);
                    sp_free_port(port);
                    port = nullptr;
                    opened = false;
                }
            }

            static std::expected<std::vector<PortInfo>, error::Error> scan() {
                sp_port** list{nullptr};
                if (sp_list_ports(&list) != SP_OK) {
                    return std::unexpected(error::Error(SrlErr::SerialScanFailed, last_error()));
                }
                std::vector<PortInfo> ports{};
                for (size_t i{0}; list[i] != nullptr; ++i) {
                    PortInfo info{};
                    if (const char* name = sp_get_port_name(list[i])) info.name = name;
                    if (const char* desc = sp_get_port_description(list[i])) info.description = desc;
                    if (sp_get_port_transport(list[i]) == SP_TRANSPORT_USB) {
                        int vid{0};
                        int pid{0};
                        if (sp_get_port_usb_vid_pid(list[i], &vid, &pid) == SP_OK) info.usb_id = std::pair{vid, pid};
                    }
                    ports.push_back(std::move(info));
                }
                sp_free_port_list(list);
                return ports;
            }

    };

}