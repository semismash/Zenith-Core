# Zenith

Zenith is a project demonstrating a bare-metal implementation of a computing stack from software to silicon. From a handcrafted core, a BIOS that handles program execution, and even a custom FPGA implementation, this project aims to demonstrate a practical full stack across both hardware and software with minimal external dependencies.
The project contains the following components -

- Custom 5-stage Pipelined RV32I Core with forwarding, telemetry tracking, AXI4Lite implementation, and UART communication.
- Handwritten BIOS firmware in RV32I assembly, allowing the user to interact with the CPU, providing functionality such as program loading and execution, self test, telemetry, device data info, etc.
- Fully custom designed unified protocol that allows communication between the CPU core via its firmware, and the client using the device.
- Custom designed CLI tool, allowing user-friendly interacting with the core, both in simulation and in hardware.
- Core simulation using Verilator, and FPGA implementation, executed directly via Make.
- Extensive documentation for every part of the stack, allowing users to easily access, refer to, or even reproduce the same results as over here. (NOTE: Documentation is still being updated properly, so the current documentation is not final.)

## How to Use

### Toolchain (Windows)

Zenith is currently set up and tested on **Windows 11**, with everything run from the **MSYS2 UCRT64 shell**. Run all `make` commands from the root of this repository.

| Purpose | Tool |
| --- | --- |
| Shell and build environment | MSYS2 (UCRT64 shell) with GNU Make |
| RTL simulation | Verilator 5.048 |
| Host C++ compiler (CLI and simulation bridge) | GCC from MSYS2 UCRT64, C++23 |
| RISC-V toolchain (BIOS and program builds) | `riscv64-unknown-elf` GCC and binutils 15.1.0 with the `rv32i/ilp32` multilib (RV32I only) |
| CLI dependencies | libserialport, replxx (built from source), CLI11 and toml++ (header-only) |
| Scripting | Python 3 (CLI code generation and a BIOS debug helper) |
| FPGA synthesis and programming | AMD Xilinx Vivado 2025.1, driven in batch mode through Tcl (no Vivado project files are kept) |
| FPGA board | Digilent Arty A7-100T (Artix-7 `xc7a100tcsg324-1`), programmed and accessed over its micro-USB port (JTAG and USB-UART) |

On the FPGA, the 100 MHz board oscillator is divided down to a 10 MHz core clock, and the UART runs at 9600 baud (8N1). Vivado has to be on your `PATH` for the FPGA commands (for example `export PATH=$PATH:/c/Xilinx/2025.1/Vivado/bin`; if only the launcher script is found, use `make fpga VIVADO=vivado.bat`).

### Makefile Usage

The [makefile](makefile) has more targets than the ones listed here. Run `make help` to see all of them. Generated files go into `build/` and `make clean` removes it.

#### Simulation (Verilator)

```bash
make cli            # build the command line client (build/bin/zenith.exe)
make bridge-run     # build the simulation BIOS and the networked Verilator simulation, then run it
```

Once the simulation is running, start the client in a second terminal and run `net`, then `connect`. The simulation listens on `127.0.0.1:5555` (data) and `127.0.0.1:5556` (reset). The individual steps are also available on their own:

```bash
make bios-sim       # only build the BIOS image for the simulation
make bridge-compile # only build the simulation
make bridge-sim     # run an already built simulation
```

To run a program directly as the ROM image on the standalone Verilator testbench (with waveform output and a per-cycle trace), use `make run PROG=<name>`.

#### Assembling Programs

Put a RV32I assembly file in [programs](programs/) and build it with its file name (without the extension):

```bash
make asm PROG=<name>    # programs/<name>.s  ->  build/programs/<name>.hex
```

Then use the client's `load` command with the generated `.hex` file, and run it with `run` (or pass `-r` to `load`).

#### Compiling C Programs

C programs are built the same way. They are compiled and linked together with the small C runtime in [src/runtime](src/runtime/), which provides the startup code, UART access, and the message functions `z_puts` and `z_gets` (see [zenith.h](src/runtime/zenith.h)):

```bash
make cprog PROG=<name>  # programs/<name>.c  ->  build/programs/<name>.hex
```

The resulting `.hex` file is loaded exactly like an assembled program.

#### Test Programs

Some sample test programs are placed in [test_progs](test_progs/) and can be used for testing. To use one, first copy it into [programs](programs/), and then build it with `make asm` (for `.s` files) or `make cprog` (for `.c` files), using its file name without the extension as `PROG`.

#### FPGA

```bash
make fpga           # BIOS for the board + Vivado synthesis, implementation and bitstream (build/vivado/zenith_core.bit)
make fpga-program   # load the bitstream into the board over JTAG
```

`make fpga` does not need the board connected. `make fpga-program` configures the FPGA, and this is volatile, so repeat it after every power cycle (no rebuild needed). The constraints file and Vivado scripts are in [src/fpga](src/fpga/). To talk to the board, switch the client to the FPGA profile, set the board's COM port with `config serial_port COM5` (the number is shown in Device Manager), and run `connect`. The simulation and FPGA flows use separate BIOS builds, so you can use both without one affecting the other.

## CPU Core Specifications

The CPU is based on the RV32I architecture. It contains implementation the base 40 instructions. Specifications include 32 General Purpose Registers (x0 hardwired to 0), 32-bit word size, 32-bit instruction size, and a 32-bit program counter (PC). The CPU is pipelined with 5 stages (IF -> ID -> EX -> MEM -> WB), and deals with hazards using stalling. For more information related to the RV32I architecture, please check the [official RISC-V specification.](https://docs.riscv.org/reference/isa/v20260120/unpriv/rv32.html)

### Diagram

![RISC-V Processor Image](diagram/RISCVIA-CORE-V2.1.png)

### Modules and Working

The CPU uses the IF -> ID -> EX -> MEM -> WB cycle. The main parts and modules of the CPU are categorized in the following manner, with each category having different components that serve different purposes in the CPU. -  

#### Core Components

These components are an integral part of the CPU, being responsible for storing data, directing control flow, and complmenting the main units.

- [**Register File**](src/design/core/components/reg_file.sv) - Register File containing the 32 general purpose registers. Outputs of the module are `r_data1` and `r_data2`, used by the execution units as operands, and which can be selected via their respective address inputed. Includes a provision for writing to a register, via selcting `w_enable`, the `w_addr`, and `w_data` to be written. `x0` is permanently hardwired to zero. Updated on positive clock edge, and allows asynchronous reset on negative edge on active low input.
- [**Program Counter**](src/design/core/components/pc.sv) - Program counter of the CPU, which points to the byte of the currently executing instruction in the instruction memory. Always initialized at byte 0. Increments by 4 by default on every positive clock edge. However, depending on the instruction, the PC can either be incremented by `IMM`, or be set to `rs1 + IMM`, based on the `pcinc_in1_pcor` and `pcinc_in2_doi` inputs respectively. Allows asynchronous reset on negative edge on active low input.

#### Unit Stages

These components form the backbome of the Fetch-Decode-Execute-Memory Access-Writeback cycle. Each stage interconnects with each other via pipeline registers (as described later on), which are updated on clock edge.

- [**Fetch Unit**](src/design/core/units/fetch.sv) - Fetch unit of the CPU, responsible for fetching the instructions from the instructions memory with the help of the program counter, and feeding it to the decoder. Currently functions largely as a wrapper around the `pc`, `instr`, and `mem_fault` lines. Purely combinational, and feeds `mem_fault` signals to the `HALT` unit.
- [**Decoder**](src/design/core/units/decoder.sv) - Decoder of the CPU, part of the controller responsible for decoding instructions for the rest of the CPU to execute. Purely combinational, and primarily decodes instructions based on the 7 `opcode` bits of the CPU. In addition, for arithmetic and logic instructions, the ALU looks at the `funct3` and `funct7` bits of the instruction to generate an equivalent signal for the ALU operation, given by the `alu_op` output. In addition, the decoder signals the Immediate Generator the respective format required to unpack immediate values for the instruction. Also gives signals to the PC, Reg File, and LSU to perform an operation based on the instruction.
- [**Immediate Generator**](src/design/core/units/imm_gen.sv) - Part of the decoder which generates immediate values from the instructions, and unpacks them based on signals given by the decoder, based on I, S, B, U, and J instructions. After unpacking, the module sends the value as a Word with respective sign-extended or zero-padded bits to either the ALU's `input_2` or the Reg File directly, if the instruction can bypass the ALU (eg. `LUI`).
- [**ALU**](src/design/core/units/alu.sv) - Arithmetic and Logic Unit, responsible for performing calculations for the CPU, and giving the result as an output. Supports 10 basic operations - `ADD`, `SUB`, `XOR`, `OR`, `AND`, `SLL`, `SRL`, `SRA`, `SLT`, and `SLTU`. In addition, both ALU inputs can support either Reg + Reg, Reg + IMM, or even PC + IMM operations (from the AUIPC instruction), controlled by the input signals `alu_in1_ropc` and `alu_in2_roi` from the decoder.
- [**Branch Unit**](src/design/core/units/branch_unit.sv) - Part of the execution phase which evaluates a branch condition based on the opcode and the ALU result, and accordingly emits a signal `branch_taken` which determines whether the CPU should successfully branch or not. A successful branch directly updates the PC, but also signals the hazard unit the flush the registers (convert to NOPs) to prevent the CPU from executing the now incorrect unbranched instructions.
- [**LSU**](src/design/core/units/lsu.sv) - Load store unit of the CPU, responsible for communicating with the Reg File and Data Memory Unit, requesting and writing data, and initiating `LOAD` and `STORE` instructions. Uses signals from the decoder to determine if the instruction is a LOAD or a STORE, utilizes the `funct3` field to check the number of bytes to be requested, and uses the `alu_res` input from the ALU to forward the address to the memory unit. Uses the `is_mem_read` and `is_mem_write` fields to determine if the instruction is a `LOAD` or a `STORE`, and prevent the CPU from accidentally faulting if there is no mem access instruction. In addition, uses a `req_bytes` signal to request a certain number of bytes from the data memory (1, 2, or 4 bytes), depending on the instruction.

#### Pipeline Registers

Piepline Registers are registers that store data about the CPU and it's particular stage of execution pertaining to that instruction. There is one pipeline register between any two successive stages, totalling up to 4 pipeline registers for the 5 stage processor. Pipeline registers only update on clock edge, and can be cleared via a clear signal on said clock edge, unless they are asynchronously reset via a reset signal.

- [**IF/EX Register**](src/design/core/pipeline/if_id.sv) - The first pipeline register between the IF and ID stages. Contains 64 bits, specifically the current fetched instruction and the PC value corresponding to that instruction fetch.
- [**ID/EX Register**](src/design/core/pipeline/id_ex.sv) - The second pipeline register between the ID and EX stages. It is the largest register by far, containing a total of 164 bits, which includes the PC value from the previous register, register file addresses and values, alu specific operation values, and a large number of metadata gathered from the decoder.
- [**EX/MEM Register**](src/design/core/pipeline/ex_mem.sv) - The third pipeline register between the EX and MEM stages. Contains a total of 78 bits, including the ALU result, destination register data, RS2 data, and other data from the ID/EX register relating to the MEM and WB stages.
- [**MEM/WB Register**](src/design/core/pipeline/mem_wb.sv) - The fourth pipeline register between the MEM and WB stages. Contains 40 bits, the smallest pipeline register, containing information related to WB and data that aids with data dependency analysis by the hazard unit.

#### Hazard Handling

The following components are used to handle hazards caused by pipeline faults during CPU execution.

- [**Hazard Unit**](src/design/core/hazard_unit/hazard_unit.sv) - Hazard detection unit of the CPU, which handles all data and control hazards by emitting signals. This includes flushing the IF/ID and ID/EX registers (to resolve control hazards via the `if_id_clear` and `id_ex_clear` signals), detecting data dependencies and stalling the CPU accordingly by freezeing the PC to create bubbles and eliminate said dependencies (to resolve data hazards via the `pc_enable` and `if_id_enable` registers), or forwarding values directly from downstream pipeline registers to the ALU inputs to eliminate many data hazards. It is a parent module which integrates the dependency analyzer, forwarding unit, and stall unit together. In addition, the unit generates metadata whenever a stall or flush occurs, which is used for advanced telemetry tracking.
- [**Dependency Analyzer**](src/design/core/hazard_unit/dep_analyzer.sv) - Dependency analyzer of the hazard unit checks for dependencies between registers of different CPU stages via the corresponding pipeline registers' metadata (i.e. if two register addresses match). Generates a high signal depending on the dependency, and also a signal indicating if the specific register field's dependency (`rs1` or `rs2`) is valid based on the instruction's opcode.
- [**Forwarding Unit**](src/design/core/hazard_unit/fwd_unit.sv) - CPU's forwarding unit which uses signals from the dependency analyzer to generate a respective signal to forward data from a downstream pipeline register up to the ALU's input. The output ports from this unit are connected directly to the ALU, in which they are multiplexed with the downstream `rdst` write back data. This helps eliminate many data hazards without unnecessary stalling.
- [**Stall Unit**](src/design/core/hazard_unit/stall_unit.sv) - CPU's global stall unit which helps deal with hazards which cannot be resolved using forwarding. This includes control hazards, by taking in a signal from the branch unit to flush the CPU, and helps catching load-use data hazards early by creating bubbles which can be converted into forwardable hazards.

#### General Core Components

These are higher level components in the CPU core, pertaining to integrating all CPU submodules together and telemetry tracking.

- [**CPU Core and Buses**](src/design/core/rv32i_core.sv) - Responsible for connecting all the aforementioned modules together, and maintaining functioning of the CPU. The core itself has multiple ports, including two for `CLOCK` and `RESET` (`clk` and `rst_n`), multiple signals from the FU/LSU to connect to the memory units, and a port connecting to the `HALT` unit of the CPU, which is raised during a fault that causes the CPU to panic.
- [**Telemetry Tracker**](src/design/core/meta.sv) - Telemetry tracker and metadata unit which keeps track of multiple values recorded during the CPU's execution time such as CPU STOP (from a STOP instruction `0xFFFFFFFF`), instruction count (`instr_count`), number of stalls (`stall_count`), number of Load-Use stalls (`l_use_count`), and branch flush count (`br_flush_count`). The simulation directly tracks these values and displays them at the end of the program to measure CPU performance (such as CPI). A CPU's reset signal will reset these values to 0.

#### CPU Memory

While not a part of the core, the instruction and data memory are vital parts of the system which the CPU requires to execute instructions and store data.

- [**Instruction Memory**](src/design/mem/instr_mem.sv) - The instruction memory's main role is to store the instructions that are to be used and executed by the CPU. It is currently a read-only memory (ROM), meaning that the instructions can only be fetched from it, not loading into it proactively. The instruction can be fetched by providing its address through the `instr_addr` port (provided by the program counter) and outputs the respective instruction (or word) present at the memory address (upto 3 additional succeeding bytes) via the `instr_out` port, and is only updated on `clk` edge. In addition, it includes a provision for raising a fault (`IF Fault`) if an instruction address is not found or a fetch fails.  
- [**Data Memory**](src/design/mem/data_mem.sv) - The data memory plays an integral role by loading and storing the data required by the CPU during memory accesses. Upon requesting data from the CPU, depending on the number of bytes modeled by `req_bytes`, it will either read the memory from the given address from said byte to the nth offset byte from that, or will write the memory at the given address until the nth offset byte if the `write_enable` signal is high. In addition, the memory unit includes a provision for raising a `Data Fault` (in case of Data Access Faults), if the requested access address or its following bytes go out of bounds.  
NOTE: By default, there is 64 KB of instruction memory and 64KB of data memory, although this may be changed via parameterization.  

The following mentioned modules are integrated and connected together in the `top.sv` module ([accessible through here](src/design/top.sv)), and are tested via the C++ Verilator testbench in the `sim_main.cpp` module ([accessible through here](src/sim_main.cpp)).

## BIOS, CLI, Protocol, and other Documentation

To be elaborated upon soon. For more information, feel free to check out the [documentation folder](docs/).

## Miscellaneous

### AI Usage Report

Something I have noticed is that a lot of people tend to not disclose the their AI usage in their projects, so I've decided to briefly and honestly report the parts of the project that I used AI for, along with the parts of the project that I have completely done and figured out by myself.

- **Design** - Completely human designed, for every part of the stack. The CPU, BIOS, Protocol, and CLI tool and commands were designed completely by me. AI was only used to review and potentially polish up certain design decisions that I made.
- **Implementation** - CPU core is almost completely human written, except for debugging and parts related to AXI4Lite implementation which used AI assistance. BIOS is nearly completely human written, except for certain menial and repeitive parts, and debugging. CLI tool and configuration (such as makefile, simulation bridge, FPGA), being less critical, were implemented largely with the help of AI, due to time constraints.
- **Debugging** - Mix of human and AI. I initially went through and debugged most of the code I could find, followed by using AI to catch silent bugs, errors, or any glitches that I was not able to fix. Every AI suggested fix was thoroughly reviewed by me.
- **Documentation** - Initially completeley human written, and polished/updated with AI assistance.

### Message from the Developer

Thanks for checking out my project! This project has been based open work that I started a couple of months ago, and I have put a lot of my heart and soul into make this work. And, after weeks of painstaking designing, coding, implementation, and documentation, and dealing with academics, existing projects, and many personal problems irl, I'm proud to announce that, at least this stage of the project, is finally complete. Really appreciate the few people who supported me throughout the journey, means a lot to me.
Stay tuned for more updates :D
