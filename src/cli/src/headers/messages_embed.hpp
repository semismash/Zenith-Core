// AUTO-GENERATED from messages.toml by embed_messages.py. DO NOT EDIT.
#pragma once
#include <string_view>

namespace messages_embed {

inline constexpr std::string_view messages_toml = R"zmsg0(# Zenith Core BIOS CLI - every string the shell prints.
# Embedded into the binary at build time (scripts/embed_messages.py), parsed with toml++ at startup.
# {} placeholders follow std::format rules ({:02X} = 2 digit hex, {:.2f} = 2 decimals ...).
# Keep the number of {} the same when editing, a message whose arguments don't fit is printed raw.

[prompt]
input = ">> "

[marker]
bios_state = "[BIOS STATE] "
from_bios = "[FROM BIOS] "

[word]
on = "on"
off = "off"
unknown = "unknown"

[state]
idle = "Idle"
message = "Message Display"
self_test = "Self Test"
telemetry = "Telemetry"
memory = "Memory Dump / Program Verify"
connection = "Connection Attempt"
program_load = "Program Load"
program_exec = "Program Execution"
program_done = "Program Execution Finished"
device_data = "Device Data Display"
error = "Error"
post_fail_idle = "Limited POST-fail Idle"
unknown = "Unknown (0x{:02X})"

[bios_error]
format = "[BIOS ERROR] 0x{:02X} 0x{:02X}: {}"
format_single = "[BIOS ERROR] 0x{:02X}: {}"
msg_get_too_big = "message too big on receive (empty or above the 256 byte echo buffer)"
msg_put_too_big = "message too big on transmit"
msg_unverified = "message unverified (0x3D missing after 0x3A)"
self_test = "self test error"
tele_unverified = "telemetry unverified (closing 0x7A not received within 4 parameters)"
tele_param = "invalid telemetry parameter"
tele_arg = "invalid telemetry argument"
mem_bounds = "memory access out of bounds"
conn_invalid = "connection invalid (ACK not received)"
conn_timeout = "connection timeout (no ACK in time)"
prg_unverified = "no validly loaded program"
prg_param = "invalid program parameter (or offset outside program space, or size 0)"
prg_arg = "invalid program argument"
prg_too_big = "program too big"
prg_offset_unaligned = "program offset not a multiple of 4"
prg_size_unaligned = "program size not a multiple of 4"
device_data = "device data error"
critical = "critical BIOS error, the BIOS reset itself (telemetry off, program invalid)"
bios_timeout = "BIOS timeout (a byte expected mid-command did not arrive in time)"
bios_cmd_invalid = "invalid command (unknown byte while idle)"
unknown = "unknown error code"

[client]
cooldown_start = "BIOS cooling down..."
cooldown_end = "BIOS ready."
cooldown_fallback = "warning: no ready signal from the BIOS, cooldown ended by timer"
timeout = "error: no response from the BIOS (timed out)"
protocol_mismatch = "error: unexpected byte 0x{:02X} from the BIOS, command aborted"
unsolicited = "unexpected byte from the BIOS: 0x{:02X}"
reboot = "the BIOS rebooted, device state cleared. Run `connect` again."
link_lost = "connection lost: {}"
raw_dropped = "dropped {} queued byte(s) because of the error"
program_start = "program running (only sendbyte, sendbytes and client commands until it finishes)"
program_done = "program finished"
program_stuck = "the program is still running. If it is stuck, reset the CPU (board button on the FPGA, `reset` in sim)."
dump_progress = "[dump] {}/{} bytes"
load_complete = "program loaded: {} bytes at 0x{:08X}"
verify_pass = "verify: PASS ({} bytes match)"
verify_fail = "verify: MISMATCH, first difference at 0x{:08X}"
verify_size = "verify: MISMATCH, read back {} bytes, expected {}"
telemetry_settings = "telemetry: bios tracking {}, program tracking {}, program reset {}"
telemetry_applied = "telemetry settings applied"

[post]
passed = "self test PASSED"
failed = "self test FAILED"
test_line = "  {:<14} {}"
pass = "pass"
fail = "FAIL"
test_0 = "registers"
test_1 = "ALU"
test_2 = "control flow"
test_3 = "memory"
test_4 = "stack"
test_5 = "UART"

[dump]
row = "0x{:08X}  {} |{}|"

[device]
bios = "BIOS:           {}"
arch = "architecture:   {}"
reg = "registers:      {} GPRs, 32-bit"
rom = "ROM:            {} KiB  0x{:08X} - 0x{:08X}"
ram = "RAM:            {} KiB  0x{:08X} - 0x{:08X}"
mem = "memory:         {} KiB  0x{:08X} - 0x{:08X}  (unmapped above, MMIO from 0x80000000)"
program = "program space:  {} KiB  0x{:08X} - 0x{:08X}"
clk = "clock:          {:g} MHz"
baud = "baud:           {}"

[status]
cycles = "clock cycles:        {}"
instr = "instructions:        {}"
stall = "stalls:              {}"
stallpcnt = "stall percent:       {:.2f} %"
stallpcnt_na = "stall percent:       n/a (no instructions counted)"
cpi = "CPI:                 {:.3f}"
cpi_na = "CPI:                 n/a (no instructions counted)"
loaduse = "load-use stalls:     {}"
brflush = "branch flushes:      {}"

[registers]
header = "registers after the program:"
row = "  x{:<2} {:<4} 0x{:08X}  {}"

[config]
header = "{} profile settings:"
entry = "  {:<15} {}"
set = "{} = {}"

[scan]
header = "available serial ports:"
entry = "  {}  {}"
entry_usb = "  {}  {} (USB {:04X}:{:04X})"
none = "no serial ports found"
hint = "(the Arty A7 shows two FTDI ports, the UART is usually the second one, e.g. /dev/ttyUSB1)"

[shell]
banner = "Zenith Core BIOS CLI ({} profile). Type `help` for the command list."
bye = "bye"
connecting = "connecting..."
connected = "connected to the BIOS"
connected_limited = "connected, but the BIOS is in the limited POST-fail state: only `connect` and `selftest` work"
connect_failed = "connection failed"
connect_retry = "retrying in {:.1f} s (Ctrl+C to stop)"
connect_stopped = "retry stopped"
sync_ok = "device state synced"
sync_failed = "warning: device data could not be fetched, limits fall back to the built-in defaults"
net_ok = "connected to the Verilator bridge at {}:{}, run `connect` next"
serial_ok = "opened serial port {}"
switched = "switched to the {} profile (disconnected)"
reset_ok = "CPU reset through the bridge side channel. Run `connect`."
reset_fpga = "press the reset button on the board, then run `connect`"
monitor_status = "monitor is {}"
log_status = "log is {}"
raw_queued = "queued {} byte(s)"
raw_pending = "{} byte(s) waiting to be sent: {}"
raw_pending_none = "no bytes waiting to be sent"

[about]
text = '''
Zenith Core BIOS CLI
Host console for the Zenith Core: a 5-stage pipelined RV32I core with forwarding, telemetry
counters and a hand-written UART BIOS, running in Verilator (sim profile, TCP) or on a
Digilent Arty A7-100T (fpga profile, USB serial).'''

[github]
url = ""    # put the repository link here
text = "GitHub: {}"
none = "no GitHub link set yet (messages.toml, [github] url)"

[help]
general = '''
Zenith Core BIOS CLI commands (`help <command>` for details)

 profiles     switch <sim|fpga>, config [key] [value]
 link         net [host:port] (sim), scan (fpga), connect [port] --timeout=S --retry=S, reset (sim)
 program      load <file.bin|file.hex> -r -v --offset= --telemode= --telereset= --register=
              run, verify
 memory       hexdump --offset=ADDR --size=COUNT
 telemetry    telemetry --mode= --reset= -r, status [-t | --telemetry=[cycles, instr, stall, stallpcnt, cpi, loaduse, brflush]]
 device       deviceinfo [--info=[arch, reg, rom, ram, mem, clk, baud]], sync, selftest
 raw bytes    sendbyte <byte>, sendbytes --bytes=[b0, b1, ...] --interval=N
 display      monitor [on|off], log [on|off], echo "message" [-t], clear
 other        help, about, github, exit / quit

Numbers: decimal, 0x hex or 0b binary. Booleans: true/false/on/off/1/0.'''
unknown = "no help for '{}', try `help`"
config = '''
config                      print all settings of the active profile
config <key>                print one setting
config <key> <value>        change it (kept per profile)
keys: cooldown_ms (both), sim_time_scale, host, port, reset_port (sim), serial_port (fpga)
sim_time_scale = wall-clock seconds per simulated second (e.g. 20 for a 500 kHz simulation)'''
switch = '''
switch <sim | fpga>
Only while disconnected or idle. Closes the link, clears the cached device state and leaves
the console disconnected until `connect` (sim: `net` first).'''
reset = '''
reset
sim: resets the CPU through the bridge side channel (RESET on the reset port), then run `connect`.
Also the way out of a program that never returns.
fpga: press the reset button on the board instead.'''
net = '''
net [host:port]
sim only. Opens the TCP link to the Verilator bridge (default 127.0.0.1:5555), then run `connect`.'''
scan = '''
scan
fpga only. Lists the serial ports (the Arty A7 UART is usually the second FTDI port).'''
connect = '''
connect [PORT] --timeout=SECONDS --retry=SECONDS
Handshake with the BIOS (AA, AB, AC). fpga: PORT opens that serial port (default: serial_port setting).
--timeout  how long to wait for the SYN-ACK, --retry  retry every SECONDS after a failure (Ctrl+C stops it).
The first connection after a self test also prints the POST results.'''
load = '''
load <file.bin | file.hex> -r -v --offset=ADDR --telemode=BOOL --telereset=BOOL --register=BOOL
-r run after load, -v read the program back and compare it with the file
--offset program start (default 0x2000, multiple of 4, inside program space)
--telemode program telemetry (default true), --telereset reset telemetry before running (default true)
--register print the registers after the program finishes (default false)
.hex: $readmemh text, all 2 digit (bytes) or all 8 digit (32-bit words, stored little endian) tokens.'''
run = '''
run
Runs the loaded program again (same offset and settings as the last load).'''
verify = '''
verify
Reads the loaded program back, compared with the last loaded file when it is still the same program.'''
telemetry = '''
telemetry --mode=BOOL --reset=BOOL -r
no arguments: show the current settings
--mode   BIOS (continuous) telemetry tracking (0x70)
--reset  reset telemetry every time a program starts (0x72)
-r       reset the counters now (0x73)
Program telemetry tracking (0x71) is set by `load --telemode`, every load overwrites 0x71 and 0x72.'''
status = '''
status [-t | --telemetry=[cycles, instr, stall, stallpcnt, cpi, loaduse, brflush]]
Telemetry counters (all of them by default). stallpcnt = stalls per 100 instructions, cpi = cycles per instruction (both client side).'''
monitor = '''
monitor [on | off]
Prints every byte coming from the BIOS as [FROM BIOS] 0xNN. No argument shows the current status.'''
log = '''
log [on | off]
Prints BIOS state changes as [BIOS STATE]. Client side only, the BIOS always sends them.'''
echo = '''
echo "message" [-t]
Sends the message to the BIOS (1 to 256 bytes), it is echoed back. -t prints it locally without the BIOS.'''
deviceinfo = '''
deviceinfo [--info=[arch, reg, rom, ram, mem, clk, baud]]
Device data from the BIOS, everything by default.'''
sync = '''
sync
Refreshes the cached device data and telemetry settings from the BIOS.'''
sendbyte = '''
sendbyte <byte>
Queues one raw byte for the CPU's UART receiver. Works whenever the prompt does (also while a program runs).'''
sendbytes = '''
sendbytes --bytes=[b0, b1, ...] --interval=N
Queues raw bytes, one every N byte-times (N x 10 baud ticks, default 1).
Without --bytes: lists the bytes still waiting to be sent.'''
selftest = '''
selftest
Runs the POST again. Overwrites program space, so the loaded program becomes invalid.'''
hexdump = '''
hexdump --offset=ADDR --size=COUNT
Dumps memory, up to the end of BIOS data space (0x21FBF).'''
clear = "clear: clears the terminal"
about = "about: information about the project"
github = "github: the repository link"
exit = "exit / quit: leaves the console (Ctrl+D works too)"
help = "help [command]: this list, or details about one command"

[parse_error]
unterminated_quote = "error: unterminated quote"
unterminated_bracket = "error: unbalanced [ ] in: {}"
syntax = "error: {}"
invalid_number = "error: not a number: {}"
number_range = "error: number out of range: {}"
invalid_bool = "error: expected true/false/on/off/1/0, got: {}"
invalid_toggle = "error: expected on/off/true/false, got: {}"
invalid_profile = "error: unknown profile '{}' (sim or fpga)"
invalid_info = "error: unknown --info item '{}' (arch, reg, rom, ram, mem, clk, baud)"
invalid_telemetry = "error: unknown --telemetry item '{}' (cycles, instr, stall, stallpcnt, cpi, loaduse, brflush)"
invalid_bytes = "error: not a byte (0 to 255): {}"
invalid_hostport = "error: expected host, host:port or :port, got: {}"
invalid_seconds = "error: expected a positive number of seconds, got: {}"
conflicting_flags = "error: these flags can't be used together: {}"
too_many_args = "error: too many arguments, usage: {}"
unknown = "error: could not parse the command"

[sema_error]
not_connected = "error: not connected to the BIOS, run `connect` first"
no_transport = "error: no link open {}"
transport_open = "error: the link is already open (use `switch` to start over)"
sim_only = "error: `{}` is only available in the sim profile"
fpga_only = "error: `{}` is only available in the fpga profile"
not_idle = "error: the BIOS is busy"
program_running = "error: a program is running, only sendbyte, sendbytes and client commands work until it finishes"
limited_state = "error: the BIOS is in the limited POST-fail state, only `connect` and `selftest` work"
raw_pending = "error: {} raw byte(s) are still waiting to be sent (`sendbytes` lists them)"
switch_not_allowed = "error: `switch` only works while disconnected or idle"
file_not_found = "error: file not found: {}"
file_read = "error: could not read: {}"
file_extension = "error: only .bin and .hex files can be loaded: {}"
hex_token = "error: bad .hex token at {}"
hex_mixed = "error: .hex file mixes byte and word tokens at {}"
program_empty = "error: the program is empty: {}"
offset_unaligned = "error: offset {} is not a multiple of 4"
offset_range = "error: offset {}"
program_too_big = "error: program too big: {}"
no_program = "error: no validly loaded program (load one first)"
dump_zero = "error: --size must be at least 1"
dump_bounds = "error: dump out of bounds: {}"
echo_empty = "error: empty message"
echo_long = "error: message is {} bytes, the BIOS echo buffer holds 256"
interval_zero = "error: --interval must be at least 1"
bytes_empty = "error: --bytes is empty"
no_serial_port = "error: no serial port given (connect <port>, or config serial_port <port>)"
config_key = "error: unknown setting '{}'"
config_value = "error: bad value: {}"
config_profile = "error: '{}' is not a setting of the active profile"
unknown = "error: command rejected"

[transport_error]
resolve = "error: could not resolve {}"
connect = "error: could not connect to {}"
socket = "error: socket error: {}"
write = "error: write failed: {}"
read = "error: read failed: {}"
peer_closed = "the other side closed the connection {}"
tx_stalled = "error: transmit stalled: {}"
serial_open = "error: could not open serial port {}"
serial_config = "error: could not configure serial port {}"
serial_io = "error: serial port error: {}"
serial_scan = "error: could not list serial ports: {}"
reset_channel = "error: reset side channel: {}"
reset_rejected = "error: the bridge did not accept the reset: {}"
unknown = "error: transport error")zmsg0";

} // namespace messages_embed
