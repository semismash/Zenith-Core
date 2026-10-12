# BIOS Functionality

## INPUT/INTERNAL

### 1. Connection
> Primary function is to establish a valid link between the host (console) and the BIOS before any other communication occurs.

**Algorithm:**
- Host sends `0xAA` (SYN) to initiate a connection.
- BIOS responds with `0xAB` (SYN-ACK) to acknowledge.
- Host sends `0xAC` (ACK) to confirm the connection is established.
- Once the handshake completes, the BIOS automatically runs POST and sends the resulting status message to the host.
- The `connect` command fails with a timeout if no SYN-ACK is received within the configured timeout window (see `--timeout` flag).

### 2. POST
> Primary function is to set the CPU up, verify its working, and send a message to be printed for verification

**Algorithm:**
- Wipe all 31 GPRs (x1-x31) to 0
- Reset telemetry data
- Run a pre-loaded test program and verify functionality
- Print message to screen (from BIOS itself)

> Self test can be activated again with the `0x5A` byte

### 3. Bootloader
> Primary function is the load program into main memory

**Algorithm:**
- Host sends `0xCA` to begin a program load
- Host sends `0xC1` followed by a 4-byte program size (little endian)
- Host sends `0xC0` followed by a 4-byte start offset (little endian); defaults to `0x1000` (start of RAM) if not explicitly set by the user
- Host sends the program bytes (`size` bytes total)
- Host sends a 1-byte checksum (sum of all program bytes, mod 256), computed while sending the program bytes
- Host sends a final `0xCA` byte to close the transfer
- BIOS compares its own computed checksum of the received bytes against the one sent by the host. If they don't match, it responds with `0xEC` + sub-code `0x02` (Checksum Mismatch) and discards the load.
- If the checksum matches, BIOS inserts a final jump instruction at the end of the program so it jumps back to its own start address after execution
- Resets SP and jumps to the program's start pointer

> **NOTE:** There is currently no mechanism for the CPU to return control to the BIOS once a program begins execution. `ecall`/`ebreak` simply halt the CPU in place rather than returning to BIOS — a proper return path (e.g. reset line or trap) is planned but not yet implemented.

### 4. Device Data
> Primary function is to provide information about the device (hardcoded in the ROM)

**Algorithm:**
- Gets `0xDA` magic verification byte
- Gets another byte asking which metrics are to be listed (`0xFF` for all)
- Returns the values via UART transmission

### 5. Device Config *(TO BE ADDED IN A LATER REVISION)*
> Configure certain settings for the devices.

Options to be able to be configured:
- Usable RAM
- Baud Tick Rate

> **NOTE (TBD):** UART frame format (data bits / parity / stop bits) is still to be finalized. Current operation assumes a fixed baud rate (9600, hardcoded for now, reconfigurable later), with timing-based pacing as the only flow control (see `sendbytes --interval`) and no hardware flow control (no RTS/CTS).

## OUTPUT

### 1. Message Display
> Sends display message to the device for printing. Uses length-prefixed framing exclusively (no per-character mode).

**Algorithm:**
- Sends `0x3A` (message start), followed by 1 byte indicating the message length (`N`), followed by `N` ASCII bytes, followed by `0x3F` (flush) to mark the message as complete.

> This is more of a user-side thing, as any program in the CPU which uses this byte sequence will be able to print messages to the console.
>
> The `echo` command from the console can be used to send a message to the CPU, and the BIOS will respond back with the same message.

- Receives a `0x3D` byte (message start), followed by a 1-byte length `N`, followed by `N` ASCII bytes, followed by a `0x3F` byte (finish).
- Stores them into a memory space in the CPU.
- Then uses the internal print function (string display) to send it to the console.

### 2. Memory Dump
> Dumps memory starting from a certain address, with a specified number of bytes.

- Takes in `0x8A` byte to indicate a memory dump request
- Takes in `0x80` followed by a 4-byte starting address
- Takes in `0x81` followed by a 4-byte dump size
- If out of bounds, returns `0xE8` 'error' byte and then error code `0x00` for invalid starting address, or `0x01` for out of bounds (size too high, overflowing into the Invalid address region or past the addressable space). Reads that fall within the MMIO region are considered valid (not out of bounds) and simply return the mapped byte values, or `0x00` for unmapped slots.

> Normally this is taken care of by the console tool, but is a hardware safety check nonetheless.

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

- `0x3A` - Echo command (message start)
- `0x3F` - Message Finish
- `0x5A` - Self-Test
- `0x7A` - Telemetry Data
- `0x70` - Toggle Continuous Telemetry Tracking
- `0x72` - Toggle Program Telemetry Tracking
- `0x71` - Instantaneous Telemetry Reset
- `0x73` - Toggle Telemetry Reset on Program Start
- `0x8A` - Memory Dump
- `0x80` - Offset Address
- `0x81` - Dump Size (4 bytes)
- `0xAA` - Connection (SYN)
- `0xAC` - Connection (ACK)
- `0xC0` - Offset Address
- `0xC1` - Program Size
- `0xCA` - Program Load
- `0xCC` - Program Run
- `0xDA` - Device Data
- `0xFA` - BIOS Data monitoring

### Output (from BIOS)

- `0x3D` - Message Display
- `0x3F` - Flush message (transmission finish)
- `0x5C` - Self-test passed
- `0x5E` - Self-test failed
- `0x5F` - Self-test finished
- `0x7A` - Telemetry Display Start
- `0x70` - Register Display
- `0x71` - CPU Telemetry Display Parameters
    - `0x00` - Clock Cycles
    - `0x01` - Instruction Count
    - `0x02` - Stall Count
    - `0x03` - Load-use Stall Count
    - `0x04` - Branch-flush Count
- `0x7F` - Telemetry Display Finished
- `0x8A` - Memory Dump Indicator & Verifier
- `0xAB` - Connection Valid (SYN-ACK)
- `0xCA` - Program Runtime Attempted
- `0xCC` - Program Runtime Begin
- `0xDA` - Device Data Display
- `0xD1` - Device Info Parameters
    - `0x00` - Architecture
    - `0x01` - Register Count
    - `0x02` - RAM Size
    - `0x03` - ROM Size
    - `0x04` - Configured Clock Speed
    - `0x05` - Configured UART Baud Tick
- `0xF0` - Current BIOS State Update
    - `0x00` - Idle
    - `0x03` - Message Display
    - `0x05` - Self Test
    - `0x07` - Telemetry Display
    - `0x08` - Memory Dump
    - `0x0A` - Connection Attempt
    - `0x0C` - Program Load
    - `0x1C` - Program Execution
    - `0x0D` - Device Data Display
    - `0xEE` - BIOS Timeout

### Error Codes (from: BIOS)

> **NOTE:** All error responses follow the same two-byte format — an error family byte, followed by a one-byte sub-code indicating the specific cause.

- `0xE3` - Message Error
- `0xE5` - Self-test Error
- `0xE7` - Telemetry Error
- `0xE8` - Memory Access Error
    - `0x00` - Invalid Starting Address
    - `0x01` - Out of Bounds (overflows into Invalid region or past addressable space)
- `0xEA` - Connection Error
- `0xEC` - Program Load/Runtime Error
    - `0x00` - Invalid Program Size
    - `0x01` - Verification Byte Mismatch
    - `0x02` - Checksum Mismatch
- `0xED` - Device Data Error

> **NOTE:** Please note that errors are raised when something goes wrong with the functioning of the BIOS or an unexpected deviation from expected control flow, not necessarily when returning the result of the specific operation.

---

# Console Commands

> **NOTE:** BIOS-interfacing commands only function while the CPU is idle in BIOS mode, since command bytes sent over UART are not processed once a program begins executing (the CPU does not implement interrupts, and currently has no path back to BIOS mid-program). Purely client-side commands (e.g. `clear`, toggling `monitor`/`log` locally, `help`, listing a pending `sendbytes` queue) still work regardless of CPU state. `monitor`, if enabled, will only show activity during execution if the running program itself chooses to transmit over UART.

### `scan`
- Gives the available port names, including that the FPGA may be connected to.

### `connect <PORTNAME> --timeout=TIME --retry=TIME`
- Connects with the available port and returns the result if connected properly. If connection fails, the terminal will print the error as so.
- Upon a successful connection, the BIOS will send a message giving the POST status and whether it succeeded or failed.
- The `--timeout` flag sets how long (in seconds) the tool waits for a SYN-ACK before considering the connection attempt failed.
- The `--retry` flag, if set, automatically re-attempts the connection every `TIME` seconds following a failed or timed-out attempt.

### `load <filename.bin | filename.hex> -r -v --offset=START_ADDRESS --telemode=<true/false> --telereset=<true/false> --register=<true/false>`
- Load a compiled binary into the CPU's RAM via the bootloader.
- The input filename can be in either `.bin` or `.hex`, but must be assembled first before loading into the CPU. The file path can be given too, and may be provided in quotes.
- The `-r` flag (run) indicates that the program will be directly executed by the CPU after being loaded.
- The `-v` flag (verify) first verifies the program bytes (read back) to the console (little endian) before execution.
- The `--offset` flag gives the bootloader the start address of the program from where it will be loaded. By default, it's the beginning address of the RAM (`0x1000`), and the input value must be higher than it. It can either be in binary or hex (with a `0x` prefix).
- The `--telemode` flag enables or disables telemetry tracking during program execution. True by default.
- The `--telereset` flag enables or disables telemetry reset before the program executes. True by default (meaning it does reset). This is independent of `selftest` — running a self-test does not itself reset telemetry data unless `--telereset` separately causes it to.
- The `--register` flag enables or disables displaying GPR values after program execution.

### `run --offset=START_ADDRESS`
- Run the loaded binary in the memory address
- To begin running the binary at a different address, the `--offset` flag can be used (must be between `0x1000` and RAM limit).
- Once execution begins, BIOS-interfacing commands will not receive a response until the CPU is reset, as there is currently no mechanism to return control to BIOS mid-program.

### `verify`
- Verifies the loaded binary by printing the program bytes back to the console.

### `telemetry --mode=<true/false> --reset=<true/false> -r`
- Modifies current telemetry tracking settings.
- No arguments displays the current settings.
- The `--mode` flag can be used to modifying if telemetry tracking starts now or not.
- The `--reset` flag can be used to modify if telemetry data is reset every time a program starts or stops.
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
- `arch` gives the CPU architecture details and specifications (RISC-V, RV32I, 32-bit)
- `reg` gives the data about the registers (32-bit GPRs, 32 GPRs total)
- `rom` gives ROM size and addresses (4KiB, `0x00000000`-`0x00000FFF`)
- `ram` gives RAM size and addresses (128KiB, `0x00001000`-`0x00020FFF`)
- `mem` gives the total usable (ROM+RAM) memory size and addresses (132KiB, `0x00000000`-`0x00020FFF`). Addresses above this are either unmapped (Invalid region, `0x00021000`-`0x7FFFFFFF`) or reserved for MMIO (`0x80000000`-`0xFFFFFFFF`).
- `clk` gives configured CPU design clock speed (10Mhz)
- `baud` gives configured CPU UART baud tick (9600)

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

### `status -r [-t | --telemetry=[cycles, instr, cpi, stall, stallpcnt, loaduse, brflush]]`
- Gets status about the CPU and its recorded data.
- The `-r` flag gives stored register data about the CPU that time. Do note that this may not work properly until interrupts are implemented.
- The `-t` flag gives the currently stored telemetry data of the CPU. Alternatively, the `--telemetry` flag can be used to fetch specified metrics about CPI.
- **NOTE:** `cpi` and `stallpcnt` are derived values computed client-side by the CLI from the raw telemetry metrics reported by the BIOS — they are not raw BIOS telemetry codes themselves.

### `selftest`
- Performs a voluntary self test of the CPU once again to verify functionality. Please note that this will clear registers and overwrite the program space, which may corrupt loaded programs.

### `hexdump --offset=START_ADDRESS --size=BYTE_COUNT -v`
- Dumps the entire hex of the program in bytes from a given address.
- The `--offset` parameter is the start address from where the hex dump will begin. It is a mandatory parameter.
- The `--size` parameter is the number of bytes from the offset that the hex dump will print. It is a mandatory parameter.
- If the offset is invalid, or `BYTE COUNT` goes out of bounds, the program will refuse to print the bytes.
### `help`
- Provides the list of terminal commands and helpful info.

### `about`
- Gives information about the project and its developer.

### `github`
- Gives the GitHub repository link for the project.