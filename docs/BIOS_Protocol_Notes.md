# BIOS Functionality

> **NOTE:** All multi-byte values (sizes, offsets, addresses, telemetry counters, register values) are sent **little endian, 4 bytes**, in both directions (`get_word` / `send_word`).

## BIOS Memory Map

| Range | Usage |
|---|---|
| `0x00000000` - `0x00000FFF` | BIOS ROM |
| `0x00001000` - `0x0001FFFF` | Program space (program stack default top: `0x00020000`) |
| `0x00020000` - `0x00020FBF` | BIOS data space |
| `0x00020FC0` - `0x00020FFF` | BIOS stack (64 bytes / 16 words) |

> BIOS data space holds: saved status registers (`0x20004` program size, `0x20008` BIOS status, `0x2000C` program offset), the echo message buffer (`0x20800`) and the GPR dump buffer (`0x20900`).

> **NOTE:** There is no memory segmentation, a program can directly overwrite BIOS data space if it wants to (or is big enough to).

## INPUT/INTERNAL

### 1. Connection
> Primary function is to establish a valid link between the host (console) and the BIOS before any other communication occurs.

**Algorithm:**
- Host sends `0xAA` (SYN) to initiate a connection.
- BIOS responds with `0xAB` (SYN-ACK) to acknowledge.
- Host sends `0xAC` (ACK) to confirm the connection is established. BIOS waits for this ACK for a fixed window of `0x8F00000` cycles (~15 seconds @ 10MHz).
- If the byte received is not `0xAC`, the connection bit is cleared and BIOS responds with `0xEA` + sub-code `0x01` (Connection Invalid).
- If no ACK arrives within the window, BIOS responds with `0xEA` + sub-code `0x02` (Connection Timeout).
- Once the handshake completes, the BIOS sends the POST results to the host (see POST below). This is only done on the **first** connection after a self test (boot or `0x5A`); reconnecting afterwards does not repeat it.
- The `connect` command fails with a timeout if no SYN-ACK is received within the configured timeout window (see `--timeout` flag).

> **NOTE:** The `--timeout` and `--retry` flags are purely client-side. The BIOS-side windows are fixed (ACK window above, `0x4000000` cycles (~6.7 seconds @ 10MHz) for every other byte read mid-command).

> **NOTE:** Connecting is not enforced by the BIOS, the connection bit is only set/cleared for bookkeeping and the idle loop accepts commands regardless of it (except in the limited POST-fail state, see POST).

### 2. POST
> Primary function is to set the CPU up, verify its working, and send a message to be printed for verification

**Algorithm:**
- Runs automatically on boot from `_start`, before any host is connected. The results are held in the BIOS status register until the first connection (see Connection).
- Runs 6 tests in order, a failure in one does not stop the others, each test sets its own bit in the pass bitmask:
  - `0x00` Registers: writes a unique pattern in each of x1-x31, reads them back, and checks that x0 is hardwired to zero
  - `0x01` ALU: add/sub (incl. overflow wraparound), and/or/xor, logical + arithmetic shifts, slt/sltu
  - `0x02` Control Flow: beq, blt/bge (taken and not taken), jal, jalr
  - `0x03` Memory: word writes/reads at `0x1000`, `0x8000`, `0x10000` and `0x1FFFC`, plus a byte and a halfword access
  - `0x04` Stack: pushes 3 words, pops them back in order, verifies SP returned to its start
  - `0x05` UART: transmits the test byte `0x50` (transmit only, no loopback verification)
- POST passes only if all 6 tests pass. Otherwise, the BIOS enters a limited idle state (state `0x50`) where the only command serviced is connection (`0xAA`), all other bytes are ignored.
- Print message to screen (from BIOS itself) on first connection, see format below

**POST result transmission (BIOS to host):**
- Startup message: `0x3D`, 4-byte length, `BIOS Loaded Successfully!` (length includes the null terminator), then `0x3F`
- `0x5C` if self test passed, or `0x5E` if failed
- `0x5D`, followed by 6 pairs of `[test number (0x00-0x05), result]`, where result is `0x01` (pass) or `0x00` (fail)
- `0x5F` to mark the results as finished

> Self test can be activated again with the `0x5A` byte. The results are then sent straight away (same format as above) and the next connection will send them again.

> **NOTE:** Registers are **not** wiped to 0 and telemetry is **not** reset by POST, the register test leaves patterns in x1-x30. Telemetry settings are cleared (off) on any BIOS reset though, see Telemetry.

> **NOTE:** The memory test writes to program space (`0x1000`, `0x1004`, `0x8000`, `0x10000`, `0x1FFFC`), so a manually requested self test will corrupt a loaded program. Program size/offset and BIOS settings are saved and restored around it.

### 3. Bootloader
> Primary function is the load program into main memory

**Algorithm:**
- Host sends `0xCA` to begin a program load
- Host then sends up to 6 parameters (in any order), each being a parameter byte, followed by its argument if it has one:
  - `0xC0` run after load (no argument)
  - `0xC1` verify (read back) after load (no argument)
  - `0xC2` program start offset, followed by a 4-byte offset; defaults to `0x1000` (start of RAM) if not sent
  - `0xC3` program telemetry tracking, followed by `0x01` (on) or `0x00` (off)
  - `0xC4` program telemetry reset before execution, followed by `0x01` (on) or `0x00` (off)
  - `0xC5` register display after program completion, followed by `0x01` (on) or `0x00` (off)
- Host sends `0xCA` again to close the parameter list (also marks that the program size follows)
- Host sends a 4-byte program size (little endian)
- Host sends the program bytes (`size` bytes total)
- BIOS checks that the program (plus 4 extra bytes) fits in memory from the start offset before receiving anything. If not, it responds with `0xEC` + sub-code `0x04` (Program Too Big).
- BIOS inserts a final `jal` instruction right after the last program byte so that, after execution, the program jumps back into the BIOS (to `jump_back`, or `jump_back_reg_disp` if register display was requested) instead of the BIOS start address
- If `0xC1` was given, BIOS sends `0xCB` followed by the program bytes read back (`size` bytes, without the inserted jump)
- If `0xC0` was given, BIOS sets SP to the top of program space (`0x20000`) and jumps to the program's start pointer, otherwise it goes back to idle

**Errors:**
- `0xEC` + `0x02` (Invalid Parameter): unrecognized parameter byte, or all 6 parameters were used without the closing `0xCA` arriving
- `0xEC` + `0x03` (Invalid Argument): argument for `0xC3`, `0xC4` or `0xC5` was not `0x00` or `0x01`
- `0xEC` + `0x04` (Program Too Big)

> **NOTE:** All program settings default to **off** on the BIOS side if the parameter is not sent. The `True by default` behavior of `--telemode`/`--telereset` is therefore the console's responsibility (it has to send `0x01` explicitly).

> **NOTE:** There is currently no checksum or end-of-transfer byte in the load sequence. A checksum (and the `0xEC` mismatch sub-codes that go with it) is not implemented yet.

### 4. Program Run
> Primary function is to start execution of an already loaded program, and bring control back to BIOS once it finishes

**Algorithm:**
- Host sends `0xCC` to run the loaded program (also reached internally by the `0xC0` load parameter). It takes no arguments, execution always starts at the last used program offset.
- BIOS saves its status registers (program size, BIOS status, program offset) into BIOS data space, applies the program telemetry settings to the hardware (enable bit, and a reset pulse if the reset setting is on), sets SP to `0x20000` and jumps to the program's start pointer.
- Once the program runs into the inserted `jal`, BIOS restores its status registers, re-initializes its UART pointer and stack, restores its own telemetry setting to the hardware, and goes back to idle.
- If register display was requested during load, the GPR values are sent first (see Register Display).

> **NOTE:** Control only returns to BIOS if the program actually reaches its last instruction. `ecall`/`ebreak` simply halt the CPU in place and a program stuck in a loop never returns either. A proper return path from those (e.g. reset line or trap) is planned but not yet implemented.

> **NOTE:** If `0xCC` is sent before any program has been loaded (offset register is 0), the CPU jumps to address `0x0` and the BIOS restarts from the top, including POST.

### 5. Telemetry
> Primary function is to configure what telemetry is tracked, reset it, and report the counters

**Settings algorithm:**
- Host sends `0x7A` to begin telemetry configuration
- Host sends up to 4 parameters, each being a parameter byte followed by `0x01` (on) or `0x00` (off):
  - `0x70` BIOS (continuous) telemetry tracking
  - `0x71` Program telemetry tracking
  - `0x72` Program telemetry reset on program start
- Host can also send `0x73` at any point to reset telemetry data instantly. It takes no argument and does not count towards the 4 parameters.
- Host sends `0x7A` again to close the list. The new settings are then applied to the hardware.
- If `0x7A` is sent twice in a row with no parameters, BIOS instead responds with the current settings as `0x70`, value, `0x71`, value, `0x72`, value (value being `0x01` or `0x00`).

**Errors:**
- `0xE7` + `0x01` (Unverified): closing `0x7A` was not received within 4 parameters
- `0xE7` + `0x02` (Invalid Parameter)
- `0xE7` + `0x03` (Invalid Argument)

**Status algorithm:**
- Host sends `0x7D` to request the telemetry counters
- BIOS responds with `0x7D` (guard), then for each of the following `[parameter byte, 4-byte value]` in this order, and finally `0x7D` again:
  - `0x01` Instruction Count
  - `0x02` Stall Count
  - `0x03` Load-use Stall Count
  - `0x04` Branch-flush Count

> **NOTE:** All telemetry settings are off after every BIOS reset. The clock cycle counter (`0x00`) is part of the defined parameters but is not currently transmitted by the BIOS.

### 6. Device Data
> Primary function is to provide information about the device (hardcoded in the ROM)

**Algorithm:**
- Gets `0xDA` magic verification byte
- Returns all values via UART transmission, starting with `0xDA`, followed by each of the below as `[parameter byte, value]`:
  - `0x00` BIOS name (string)
  - `0x01` Architecture (string)
  - `0x02` Register Count (word)
  - `0x03` Clock Speed (word)
  - `0x04` UART Baud Tick (word)
  - `0x05` RAM Offset (word)
  - `0x06` RAM Size (word)
  - `0x07` Program Offset (word)
  - `0x08` Program Size (word)
  - `0x09` ROM Offset (word)
  - `0x0A` ROM Size (word)
- Strings are sent in the same framing as a message: `0x3D`, 4-byte length (including the null terminator), then the bytes. No `0x3F` follows them.

> **NOTE:** The BIOS does not take a metric selection byte, it always returns everything. Filtering (`--info`) is up to the console.

### 7. BIOS State Logging
> Primary function is to let the host track what the BIOS is currently doing

**Algorithm:**
- Host sends `0xFA`, followed by `0x01` (on) or `0x00` (off)
- BIOS acknowledges with `0xFA` followed by the new state (`0x01` or `0x00`)
- Any other argument responds with `0xEF` + sub-code `0x02` (Invalid Argument)
- While on, every time the BIOS changes state it sends `0xF0` followed by the state byte (see state list below)

> **NOTE:** The BIOS re-enters idle (and so sends an idle state update) every time an idle read times out, so expect a repeating `0xF0 0x00` while logging is on and nothing is happening.

### 8. Device Config *(TO BE ADDED IN A LATER REVISION)*
> Configure certain settings for the devices.

Options to be able to be configured:
- Usable RAM
- Baud Tick Rate

> **NOTE (TBD):** UART frame format (data bits / parity / stop bits) is still to be finalized. Current operation assumes a fixed baud rate (9600, hardcoded for now, reconfigurable later), with timing-based pacing as the only flow control (see `sendbytes --interval`) and no hardware flow control (no RTS/CTS).

## OUTPUT

### 1. Message Display
> Sends display message to the device for printing. Uses length-prefixed framing exclusively (no per-character mode).

**Algorithm:**
- Sends `0x3D` (message start), followed by a 4-byte message length (`N`), followed by `N` ASCII bytes.
- The caller then sends `0x3F` (flush) to mark the message as complete. (The internal print function does not send it itself.)

> This is more of a user-side thing, as any program in the CPU which uses this byte sequence will be able to print messages to the console.
>
> The `echo` command from the console can be used to send a message to the CPU, and the BIOS will respond back with the same message.

**Echo algorithm:**
- Host sends `0x3A` (echo), then `0x3D`, then a 4-byte length `N`, then `N` ASCII bytes. No closing byte is sent.
- Stores them into the echo buffer (`0x20800`) in the CPU.
- Then responds with `0x3A`, followed by the message in the sequence above (`0x3D`, length, bytes), followed by `0x3F` (finish).

**Errors:**
- `0xE3` + `0x01` (Message Too Big, on receive)
- `0xE3` + `0x02` (Message Too Big, on transmit)
- `0xE3` + `0x03` (Unverified, `0x3D` was not received after `0x3A`)

### 2. Memory Dump
> Dumps memory starting from a certain address, with a specified number of bytes.

- Takes in `0x8A` byte to indicate a memory dump request
- Takes in a 4-byte dump size, followed by a 4-byte starting address (**size first**)
- Responds with the raw bytes (`size` bytes), with no header or footer
- If out of bounds, returns `0xE8` 'error' byte and then error code `0x01`. The valid range is from `0x00000000` up to the top of BIOS data space (`0x20FBF`), the BIOS stack and everything above it (including the MMIO region) cannot be dumped.

> Normally this is taken care of by the console tool, but is a hardware safety check nonetheless.

> **NOTE:** The same routine (and the same bounds check) is used to read back programs for verification.

### 3. Register Display
> Dumps the 31 GPRs after a program completes, if it was requested during load.

- Sends `0x75` (guard byte)
- For each of x1 to x31 in order, sends the register number (`0x01`-`0x1F`), followed by its 4-byte value
- Sends `0x75` (guard byte) again

> **NOTE:** x31 (t6) is used by the dump routine as its own buffer pointer, so its original value is lost and it is always reported as `0`.

---

# BIOS CODES

## Patterns

| Range | Meaning |
|---|---|
| `0x3X` | Message/String Transmission |
| `0x5X` | CPU Self-Test |
| `0x7X` | Telemetry Data |
| `0x8X` | Memory Interfacing |
| `0xAX` | Connection |
| `0xCX` | Program Runtime |
| `0xDX` | Device Data |
| `0xEX` | Error Codes |
| `0xFX` | BIOS Data Monitoring |

## Byte Code List

### Input (to BIOS)

- `0x3A` - Echo command
- `0x3D` - Message string start (follows `0x3A`)
- `0x5A` - Self-Test
- `0x7A` - Telemetry Settings (start and end guard)
  - `0x70` - BIOS (Continuous) Telemetry Tracking
  - `0x71` - Program Telemetry Tracking
  - `0x72` - Program Telemetry Reset on Start
  - `0x73` - Instantaneous Telemetry Reset (no argument)
  - Arguments: `0x00` off, `0x01` on
- `0x7D` - Telemetry Status Display Request
- `0x8A` - Memory Dump (followed by 4-byte size, then 4-byte offset)
- `0xAA` - Connection (SYN)
- `0xAC` - Connection (ACK)
- `0xCA` - Program Load (also closes the parameter list)
  - `0xC0` - Run After Load (no argument)
  - `0xC1` - Verify After Load (no argument)
  - `0xC2` - Offset Address (4 bytes)
  - `0xC3` - Program Telemetry Mode (`0x00`/`0x01`)
  - `0xC4` - Program Telemetry Reset (`0x00`/`0x01`)
  - `0xC5` - Register Display After Run (`0x00`/`0x01`)
- `0xCB` - Program Verify (read back the loaded program)
- `0xCC` - Program Run
- `0xDA` - Device Data
- `0xFA` - BIOS Data Monitoring (followed by `0x00` off / `0x01` on)

### Output (from BIOS)

- `0x3A` - Echo response start
- `0x3D` - Message Display (followed by 4-byte length, then bytes)
- `0x3F` - Flush message (transmission finish)
- `0x50` - Self-test UART test byte
- `0x5C` - Self-test passed
- `0x5D` - Self-test per-test results start (followed by 6 pairs of `[test number, 0x00/0x01]`)
    - `0x00` - Registers
    - `0x01` - ALU
    - `0x02` - Control Flow
    - `0x03` - Memory
    - `0x04` - Stack
    - `0x05` - UART
- `0x5E` - Self-test failed
- `0x5F` - Self-test finished
- `0x70`, `0x71`, `0x72` - Telemetry settings reply (each followed by `0x00`/`0x01`)
- `0x7D` - Telemetry Status Display (start and end guard)
    - `0x00` - Clock Cycles *(defined, not currently sent)*
    - `0x01` - Instruction Count
    - `0x02` - Stall Count
    - `0x03` - Load-use Stall Count
    - `0x04` - Branch-flush Count
- `0x75` - Register Display (start and end guard)
- `0xAB` - Connection Valid (SYN-ACK)
- `0xCB` - Program Verify read-back follows (sent for `0xC1` during load)
- `0xDA` - Device Data Display
    - `0x00` - BIOS Name
    - `0x01` - Architecture
    - `0x02` - Register Count
    - `0x03` - Configured Clock Speed
    - `0x04` - Configured UART Baud Tick
    - `0x05` - RAM Offset
    - `0x06` - RAM Size
    - `0x07` - Program Offset
    - `0x08` - Program Size
    - `0x09` - ROM Offset
    - `0x0A` - ROM Size
- `0xFA` - BIOS Data Monitoring acknowledgement (followed by `0x00`/`0x01`)
- `0xF0` - Current BIOS State Update (followed by state)
    - `0x00` - Idle
    - `0x03` - Message Display
    - `0x05` - Self Test
    - `0x07` - Telemetry
    - `0x08` - Memory Dump / Program Verify
    - `0x0A` - Connection Attempt
    - `0x0C` - Program Load
    - `0x1C` - Program Execution
    - `0x0D` - Device Data Display
    - `0x0E` - Error *(defined, not currently used)*
    - `0x0F` - BIOS Log Toggle
    - `0x50` - Limited POST-fail Idle (connection only)

> **NOTE:** Defined in `protocol.inc` but not currently transmitted: `0x7A`, `0x7F`, `0x70`/`0x71` as telemetry display prefixes, `0x8A` (memory dump header), `0xCA` (program load attempted), `0xCC` (program run begin), `0xD1` (device info parameter prefix). Memory dump, program verify and device data parameters are sent without them.

### Error Codes (from: BIOS)

> **NOTE:** All error responses follow the same two-byte format — an error family byte, followed by a one-byte sub-code indicating the specific cause. The only exception is `0xEE`, which is a single byte.

- `0xE3` - Message Error
    - `0x01` - Message Too Big (receive)
    - `0x02` - Message Too Big (transmit)
    - `0x03` - Message Unverified (missing `0x3D`)
- `0xE5` - Self-test Error *(defined, not currently used)*
- `0xE7` - Telemetry Error
    - `0x01` - Unverified (closing `0x7A` not received)
    - `0x02` - Invalid Parameter
    - `0x03` - Invalid Argument
- `0xE8` - Memory Access Error
    - `0x01` - Out of Bounds (starting address or size outside `0x00000000`-`0x00020FBF`)
- `0xEA` - Connection Error
    - `0x01` - Connection Invalid (ACK not received)
    - `0x02` - Connection Timeout
- `0xEC` - Program Load/Runtime Error
    - `0x01` - Unverified *(defined, not currently used)*
    - `0x02` - Invalid Parameter
    - `0x03` - Invalid Argument
    - `0x04` - Program Too Big
- `0xED` - Device Data Error *(defined, not currently used)*
- `0xEE` - Critical Error (single byte, BIOS-side fault, followed by a BIOS reset)
- `0xEF` - BIOS Error
    - `0x01` - BIOS Timeout (a byte expected mid-command did not arrive in time)
    - `0x02` - Invalid Argument (BIOS data monitoring)

> **NOTE:** Please note that errors are raised when something goes wrong with the functioning of the BIOS or an unexpected deviation from expected control flow, not necessarily when returning the result of the specific operation.

> **NOTE:** Timeouts while idle (waiting for a command byte) are silent. After any error or timeout the BIOS returns to idle (or the limited POST-fail idle if the last self test failed).

---

# Console Commands

> **NOTE:** BIOS-interfacing commands only function while the CPU is idle in BIOS mode, since command bytes sent over UART are not processed while a program is executing (the CPU does not implement interrupts). Control returns to BIOS once the program reaches its end (see Program Run). Purely client-side commands (e.g. `clear`, toggling `monitor`/`log` locally, `help`, listing a pending `sendbytes` queue) still work regardless of CPU state. `monitor`, if enabled, will only show activity during execution if the running program itself chooses to transmit over UART.

### `scan`
- Gives the available port names, including that the FPGA may be connected to.

### `connect <PORTNAME> --timeout=TIME --retry=TIME`
- Connects with the available port and returns the result if connected properly. If connection fails, the terminal will print the error as so.
- Upon the first successful connection after a self test, the BIOS will send a message giving the POST status and whether it succeeded or failed, along with the result of each individual test.
- The `--timeout` flag sets how long (in seconds) the tool waits for a SYN-ACK before considering the connection attempt failed.
- The `--retry` flag, if set, automatically re-attempts the connection every `TIME` seconds following a failed or timed-out attempt.
- If the BIOS is in the limited POST-fail state, connecting is the only thing that works.

### `load <filename.bin | filename.hex> -r -v --offset=START_ADDRESS --telemode=<true/false> --telereset=<true/false> --register=<true/false>`
- Load a compiled binary into the CPU's RAM via the bootloader.
- The input filename can be in either `.bin` or `.hex`, but must be assembled first before loading into the CPU. The file path can be given too, and may be provided in quotes.
- The `-r` flag (run) indicates that the program will be directly executed by the CPU after being loaded.
- The `-v` flag (verify) first verifies the program bytes (read back) to the console (little endian) before execution.
- The `--offset` flag gives the bootloader the start address of the program from where it will be loaded. By default, it's the beginning address of the RAM (`0x1000`), and the input value must be higher than it. It can either be in binary or hex (with a `0x` prefix). The BIOS itself only checks the upper bound (program must fit), the lower bound is the console's job.
- The `--telemode` flag enables or disables telemetry tracking during program execution. True by default.
- The `--telereset` flag enables or disables telemetry reset before the program executes. True by default (meaning it does reset). This is independent of `selftest` — running a self-test does not itself reset telemetry data unless `--telereset` separately causes it to.
- The `--register` flag enables or disables displaying GPR values after program execution.
- The program is limited to the program space (the BIOS data space starts at `0x20000`).

### `run`
- Run the loaded binary in the memory address
- The BIOS run command takes no address, it always starts at the offset given to the last `load`.
- Once execution begins, BIOS-interfacing commands will not receive a response until the program finishes and control returns to the BIOS (or the CPU is reset, if it never returns).

> **NOTE (TBD):** The previous `--offset` flag for `run` has no BIOS-side equivalent right now (the offset can only be set through `load`).

### `verify`
- Verifies the loaded binary by printing the program bytes back to the console.

### `telemetry --mode=<true/false> --reset=<true/false> -r`
- Modifies current telemetry tracking settings.
- No arguments displays the current settings.
- The `--mode` flag can be used to modifying if telemetry tracking starts now or not.
- The `--reset` flag can be used to modify if telemetry data is reset every time a program starts.
- The `-r` flag, if used, resets telemetry data instantly.

### `monitor <(on/off) | (true/false)>`
- Monitors all bytes that the UART transmitter of the CPU sends to the console's device if true. False (off) by default.
- Not specifying an argument gives the current status.

### `log <(on/off) | (true/false)>`
- Logs the BIOS state of a CPU and it's current action
- Not specifying an argument gives the current status.
- Activation Byte — `0xFA`

### `echo "message" -t`
- Sends a message to the CPU when its in BIOS mode
- The `-t` flag can be used to bypass the bootloader and echo the message directly to the terminal (can be used to check terminal responsiveness).

### `clear`
- Clear the terminal.

### `deviceinfo --info=[arch, reg, rom, ram, mem, clk, baud]`
- Gives device info
- Omitting the `--info` flag lists all info about the device, while specifying it allows which metrics to be printed. Multiple metrics may be specified
- The BIOS always sends the full device data, the selection is done by the console.
- `arch` gives the CPU architecture details and specifications (RISC-V, RV32I, 32-bit)
- `reg` gives the data about the registers (32-bit GPRs, 32 GPRs total)
- `rom` gives ROM size and addresses (4KiB, `0x00000000`-`0x00000FFF`)
- `ram` gives RAM size and addresses (128KiB, `0x00001000`-`0x00020FFF`)
- `mem` gives the total usable (ROM+RAM) memory size and addresses (132KiB, `0x00000000`-`0x00020FFF`). Addresses above this are either unmapped (Invalid region, `0x00021000`-`0x7FFFFFFF`) or reserved for MMIO (`0x80000000`-`0xFFFFFFFF`).
- `clk` gives configured CPU design clock speed (10Mhz)
- `baud` gives configured CPU UART baud tick (9600)

> The BIOS also reports the program space (offset `0x1000`, size `0x1F000`) and the BIOS name (`Zenith Core BIOS v.1.0`).

### `sync`
- Syncs the current device state and data to that of the terminal.
- Updating the device state to the terminal allows the application to verify details about the CPU from the get-go before running the command and transmitting it to the CPU.

### `sendbyte [byte]`
- Sends a byte to the UART receiver of the CPU
- `[byte]` should be replaced by the byte value in hex (eg. `0x1F`) or in decimal (eg. `31`)

### `sendbytes --bytes=[byte0, byte1, byte2, ...] --interval=INTERVAL`
- Sends an array of bytes over to the UART receiver of the CPU
- `[byte0, byte1, byte2, ...]` should be replaced with the array of actual bytes. It must be done with the `--bytes` flag.
- Omitting the bytes flag will list the bytes serially left to be transmitted from a previous usage of the command.
- The `--interval` flag specifies the intervals between the byte transmissions in terms of 10 baud ticks (for example, an interval of 3 would mean one byte transmission every 30 baud ticks).

### `status -r [-t | --telemetry=[instr, stall, stallpcnt, loaduse, brflush]]`
- Gets status about the CPU and its recorded data.
- *(NOTE: REMOVED FOR THE CURRENT VERSION SO IGNORE)* The `-r` flag gives the stored register data about the CPU. The BIOS has no request byte for this, the GPRs are only sent once after a program completes when it was loaded with `--register=true` (see Register Display).
- The `-t` flag gives the currently stored telemetry data of the CPU (request byte `0x7D`). Alternatively, the `--telemetry` flag can be used to fetch specified metrics about CPI.
- **NOTE:** `cpi` and `stallpcnt` are derived values computed client-side by the CLI from the raw telemetry metrics reported by the BIOS — they are not raw BIOS telemetry codes themselves. `cpi` is to be implemented in a later version when `cycles` is implemented.
- **NOTE (TBD):** The BIOS does not currently send the clock cycle count, so `cycles` (and anything derived from it) can't be filled from BIOS data yet.

### `selftest`
- Performs a voluntary self test of the CPU once again to verify functionality. Please note that this will clear registers and overwrite program space, which may corrupt loaded programs.
- The results are displayed in the same format as the one after the first connection.

### `hexdump --offset=START_ADDRESS --size=BYTE_COUNT -v`
- Dumps the entire hex of the program in bytes from a given address.
- The `--offset` parameter is the start address from where the hex dump will begin. It is a mandatory parameter.
- The `--size` parameter is the number of bytes from the offset that the hex dump will print. It is a mandatory parameter.
- If the offset is invalid, or `BYTE COUNT` goes out of bounds, the program will refuse to print the bytes.
- The BIOS can only dump up to the end of BIOS data space (`0x20FBF`), the BIOS stack and MMIO region are out of bounds.

### `help`
- Provides the list of terminal commands and helpful info.

### `about`
- Gives information about the project and its developer.

### `github`
- Gives the GitHub repository link for the project.
