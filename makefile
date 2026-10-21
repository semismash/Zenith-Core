# ==================================================================================================
# Zenith Core - Makefile, stage 1: Verilator core-only simulation (no CLI, no bridge yet)
#
# Run from ROOT. Everything below assumes ONE shell that has verilator + the riscv toolchain
# (MSYS2 UCRT64). If Verilator lives in a different shell (e.g. WSL2), run `make asm` in the shell
# with the toolchain and `make compile sim` in the Verilator one; the targets are independent.
#
#   make run                      assemble src/firmware/program.s, build the sim, run it
#   make run PROG=test_alu        same for src/firmware/test_alu.s  ->  src/firmware/test_alu.hex
#   make asm PROG=test_alu        assemble only
#   make compile                  build the Verilator sim only
#   make sim PROG=test_alu        run the already-built sim with that program
#   make run AUTO_STOP=0          do not append the 0xFFFFFFFF stop word to the hex
#   make clean
#
#   --- stage 2: BIOS + CLI over TCP ---
#   make bios-sim                 assemble the BIOS for simulation (TIMEOUT_DIV=16) -> src/firmware/bios_sim.hex
#   make bios                     assemble the BIOS for the FPGA   (TIMEOUT_DIV=1)  -> src/firmware/bios.hex
#   make bridge-selftest          test the UART/TCP bridge on its own (no Verilator needed)
#   make bridge-run               bios-sim + build the networked sim + run it (ports 5555 data / 5556 reset)
#   make bridge-sim               run the already-built networked sim
#
#   --- CLI (native UCRT64 build) ---
#   make cli / cli-run / cli-clean   see the CLI section at the bottom
# ==================================================================================================

SRC_DIR      = src
DESIGN_DIR   = $(SRC_DIR)/design
SIM_DIR      = $(SRC_DIR)/rtl_sim
FW_DIR       = $(SRC_DIR)/firmware
TMP_DIR      = tmp

# --- program under test ---------------------------------------------------------------------------
PROG        ?= program
ASM_SRC      = $(FW_DIR)/$(PROG).s
HEX_OUT      = $(FW_DIR)/$(PROG).hex

# link address of .text; must match the ROM base in rv32i.sv / the core's reset PC
TEXT_BASE   ?= 0x0
# ROM size, only used for the program-size check below
ROM_BYTES   ?= 8192
# 1 = append a 0xFFFFFFFF word after the program (the sim's "stop" sentinel)
AUTO_STOP   ?= 1

# --- toolchain ------------------------------------------------------------------------------------
RISCV_PREFIX ?= riscv64-unknown-elf-
AS      = $(RISCV_PREFIX)as
LD      = $(RISCV_PREFIX)ld
OBJCOPY = $(RISCV_PREFIX)objcopy
OBJDUMP = $(RISCV_PREFIX)objdump

VERILATOR = verilator
EXE_EXT  := $(if $(filter Windows_NT,$(OS)),.exe,)
SIM_EXE   = ./obj_dir/Vtop$(EXE_EXT)

# --- RTL sources ----------------------------------------------------------------------------------
# Packages have to be compiled first, in dependency order (a package that imports another goes
# after it). Every other .sv under src/design is picked up automatically after them.
# Any new package file has to be added here.
# (If a stale/duplicate .sv in there causes "duplicate module" errors, move it out of src/design.)
PKG_SRCS     = $(DESIGN_DIR)/rv32i.sv $(DESIGN_DIR)/uart.sv
VERILOG_SRCS = $(PKG_SRCS) $(filter-out $(PKG_SRCS),$(sort $(shell find $(DESIGN_DIR) -name '*.sv')))

CPP_SRCS     = $(SIM_DIR)/sim_main.cpp

.PHONY: all asm compile run sim clean bios bios-sim bios-build bridge-compile bridge-run bridge-sim bridge-selftest cli cli-codegen cli-run cli-clean

all: compile

# --- assemble: program.s -> tmp/*.o/.elf/.bin/.lst -> src/firmware/<PROG>.hex ----------------------
# The hex is one little-endian 32-bit word per line, which is what rom.sv's $readmemh expects.
asm:
	@if [ ! -f $(ASM_SRC) ]; then \
		echo "[MAKE ERROR] $(ASM_SRC) not found!"; \
		exit 1; \
	fi
	@mkdir -p $(TMP_DIR)
	@echo "[MAKE] Assembling $(ASM_SRC)..."
	$(AS) -march=rv32i -mabi=ilp32 -o $(TMP_DIR)/$(PROG).o $(ASM_SRC)
	@echo "[MAKE] Linking at $(TEXT_BASE)..."
	$(LD) -m elf32lriscv -Ttext $(TEXT_BASE) -o $(TMP_DIR)/$(PROG).elf $(TMP_DIR)/$(PROG).o
	$(OBJCOPY) -O binary $(TMP_DIR)/$(PROG).elf $(TMP_DIR)/$(PROG).bin
	$(OBJDUMP) -d $(TMP_DIR)/$(PROG).elf > $(TMP_DIR)/$(PROG).lst
	@size=$$(wc -c < $(TMP_DIR)/$(PROG).bin); \
	limit=$$(( $(ROM_BYTES) - $(if $(filter 1,$(AUTO_STOP)),4,0) )); \
	if [ $$size -gt $$limit ]; then \
		echo "[MAKE ERROR] program is $$size bytes, ROM allows $$limit!"; \
		exit 1; \
	fi
	@echo "[MAKE] Writing $(HEX_OUT)..."
	@od -An -v -tx4 -w4 $(TMP_DIR)/$(PROG).bin | tr -d ' ' > $(HEX_OUT)
	@$(if $(filter 1,$(AUTO_STOP)),echo ffffffff >> $(HEX_OUT),true)
	@echo "[MAKE] Done: $(HEX_OUT)  (disassembly: $(TMP_DIR)/$(PROG).lst)"

# --- Verilator build ------------------------------------------------------------------------------
# --public-flat-rw makes every internal signal reachable from sim_main.cpp (rootp->top__DOT__...).
compile: $(VERILOG_SRCS) $(CPP_SRCS)
	@echo "[MAKE] Compiling SystemVerilog core and C++ testbench..."
	$(VERILATOR) --cc --exe --build -j -Wall -Wno-fatal --trace --public-flat-rw \
		-I$(DESIGN_DIR) \
		-CFLAGS "-O2" \
		-LDFLAGS "-O2" \
		$(VERILOG_SRCS) $(CPP_SRCS) --top-module top

run: asm compile
	@echo "[MAKE] Executing simulation ($(HEX_OUT))..."
	$(SIM_EXE) +ROM_HEX=$(HEX_OUT)

sim:
	@if [ ! -f $(SIM_EXE) ]; then \
		echo "[MAKE ERROR] $(SIM_EXE) not found! Run 'make compile' first."; \
		exit 1; \
	fi
	@if [ ! -f $(HEX_OUT) ]; then \
		echo "[MAKE ERROR] $(HEX_OUT) not found! Run 'make asm PROG=$(PROG)' first."; \
		exit 1; \
	fi
	@echo "[MAKE] Executing simulation directly ($(HEX_OUT))..."
	$(SIM_EXE) +ROM_HEX=$(HEX_OUT)

# --- BIOS ------------------------------------------------------------------------------------------
# bios.s + linker.ld + protocol.inc live together (override with BIOS_DIR=...). The sim build shortens the BIOS
# timeouts by TIMEOUT_DIV (bios.s: .ifndef TIMEOUT_DIV), the FPGA build keeps the real ones.
BIOS_DIR        ?= $(FW_DIR)
BIOS_SRC         = $(BIOS_DIR)/bios.s
BIOS_LD          = $(BIOS_DIR)/linker.ld
BIOS_HEX         = $(BIOS_DIR)/bios.hex
BIOS_SIM_HEX     = $(BIOS_DIR)/bios_sim.hex
SIM_TIMEOUT_DIV ?= 16

bios-sim:
	@$(MAKE) --no-print-directory bios-build BIOS_TD=$(SIM_TIMEOUT_DIV) BIOS_OUT=$(BIOS_SIM_HEX) BIOS_TAG=bios_sim

bios:
	@$(MAKE) --no-print-directory bios-build BIOS_TD=1 BIOS_OUT=$(BIOS_HEX) BIOS_TAG=bios

# internal: needs BIOS_TD, BIOS_OUT, BIOS_TAG
bios-build:
	@for f in $(BIOS_SRC) $(BIOS_LD) $(BIOS_DIR)/protocol.inc; do \
		if [ ! -f $$f ]; then echo "[MAKE ERROR] $$f not found! (BIOS_DIR=$(BIOS_DIR))"; exit 1; fi; \
	done
	@mkdir -p $(TMP_DIR)
	@echo "[MAKE] Assembling BIOS (TIMEOUT_DIV=$(BIOS_TD))..."
	$(AS) -march=rv32i -mabi=ilp32 -I $(BIOS_DIR) --defsym TIMEOUT_DIV=$(BIOS_TD) -o $(TMP_DIR)/$(BIOS_TAG).o $(BIOS_SRC)
	$(LD) -m elf32lriscv -T $(BIOS_LD) -Map=$(TMP_DIR)/$(BIOS_TAG).map -o $(TMP_DIR)/$(BIOS_TAG).elf $(TMP_DIR)/$(BIOS_TAG).o
	$(OBJCOPY) -O binary $(TMP_DIR)/$(BIOS_TAG).elf $(TMP_DIR)/$(BIOS_TAG).bin
	$(OBJDUMP) -d $(TMP_DIR)/$(BIOS_TAG).elf > $(TMP_DIR)/$(BIOS_TAG).lst
	@size=$$(wc -c < $(TMP_DIR)/$(BIOS_TAG).bin); \
	if [ $$size -gt $(ROM_BYTES) ]; then echo "[MAKE ERROR] BIOS is $$size bytes, ROM is $(ROM_BYTES)!"; exit 1; fi; \
	echo "[MAKE] BIOS image: $$size of $(ROM_BYTES) ROM bytes"
	@od -An -v -tx4 -w4 $(TMP_DIR)/$(BIOS_TAG).bin | tr -d ' ' > $(BIOS_OUT)
	@echo "[MAKE] Done: $(BIOS_OUT)  (disassembly: $(TMP_DIR)/$(BIOS_TAG).lst)"

# --- networked simulation (BIOS + CLI over TCP) ------------------------------------------------------
# A second Verilator build, separate from the core-only testbench: own output dir, own executable. On Windows
# the bridge needs Winsock (-lws2_32).
BRIDGE_OUT_DIR  = obj_dir_bridge
BRIDGE_EXE      = ./$(BRIDGE_OUT_DIR)/zenith_bridge$(EXE_EXT)
BRIDGE_SRCS     = $(SIM_DIR)/sim_bridge.cpp
BRIDGE_HDRS     = $(SIM_DIR)/uart_bridge.hpp
WINSOCK_LIBS   := $(if $(filter Windows_NT,$(OS)),-lws2_32,)

bridge-compile: $(VERILOG_SRCS) $(BRIDGE_SRCS) $(BRIDGE_HDRS)
	@echo "[MAKE] Compiling the networked simulation..."
	$(VERILATOR) --cc --exe --build -j -Wall -Wno-fatal --trace --public-flat-rw \
		-I$(DESIGN_DIR) \
		--Mdir $(BRIDGE_OUT_DIR) -o zenith_bridge$(EXE_EXT) \
		-CFLAGS "-O2" \
		-LDFLAGS "-O2 $(WINSOCK_LIBS)" \
		$(VERILOG_SRCS) $(BRIDGE_SRCS) --top-module top

bridge-run: bios-sim bridge-compile bridge-sim

bridge-sim:
	@if [ ! -f $(BRIDGE_EXE) ]; then \
		echo "[MAKE ERROR] $(BRIDGE_EXE) not found! Run 'make bridge-compile' first."; \
		exit 1; \
	fi
	@if [ ! -f $(BIOS_SIM_HEX) ]; then \
		echo "[MAKE ERROR] $(BIOS_SIM_HEX) not found! Run 'make bios-sim' first."; \
		exit 1; \
	fi
	$(BRIDGE_EXE) +ROM_HEX=$(BIOS_SIM_HEX) $(BRIDGE_ARGS)

# the bridge without Verilator: a C++ port of the UART RTL talks to it over real sockets
bridge-selftest:
	@mkdir -p $(TMP_DIR)
	$(CXX) -std=c++17 -O2 -Wall -Wextra -o $(TMP_DIR)/test_uart_bridge$(EXE_EXT) $(SIM_DIR)/test_uart_bridge.cpp $(WINSOCK_LIBS)
	$(TMP_DIR)/test_uart_bridge$(EXE_EXT)

clean:
	@echo "[MAKE] Sweeping away generated simulation files..."
	rm -rf obj_dir $(BRIDGE_OUT_DIR) $(TMP_DIR) waveform.vcd waveform_bridge.vcd


# ==================================================================================================
# CLI (ROOT/src/cli) - native Windows build in the SAME MSYS2 UCRT64 shell as everything else
#   libserialport : pacman -S mingw-w64-ucrt-x86_64-libserialport      (headers/libs live in /ucrt64)
#   replxx        : built once from source and installed into /ucrt64     (no MSYS2 package exists)
#   CLI11, toml++ : header only, taken from src/cli/lib, from vcpkg_installed (if it is still there) or from
#                   /ucrt64/include (pacman -S mingw-w64-ucrt-x86_64-cli11 mingw-w64-ucrt-x86_64-tomlplusplus)
#
#   make cli          generate codes.hpp + messages_embed.hpp, then build src/cli/zenith.exe
#   make cli SKIP_CODEGEN=1    build without regenerating the headers
#   make cli-run      build and launch it
# ==================================================================================================
CLI_DIR        = $(SRC_DIR)/cli
CLI_LIB_DIR    = $(CLI_DIR)/lib
CLI_VCPKG_INC  = $(CLI_DIR)/vcpkg_installed/x64-mingw-dynamic/include
CLI_EXE        = $(CLI_DIR)/zenith.exe
PYTHON        ?= python3

CLI_SRCS = \
	$(CLI_DIR)/src/main.cpp \
	$(CLI_DIR)/src/cli.cpp \
	$(CLI_DIR)/src/shell/shell.cpp \
	$(CLI_DIR)/src/shell/cmdparse.cpp \
	$(CLI_DIR)/src/shell/responseprint.cpp \
	$(CLI_DIR)/src/client/client.cpp \
	$(CLI_DIR)/src/client/bytegen.cpp \
	$(CLI_DIR)/src/client/cmd_analyze.cpp \
	$(CLI_DIR)/src/interface/uart_module.cpp \
	$(CLI_DIR)/src/profile/profile.cpp \
	$(CLI_DIR)/src/profile/config.cpp

CXXFLAGS  = -std=c++23 -O2 -Wall -Wextra
# -idirafter: vcpkg's include dir is only a fallback, it must never shadow the replxx/libserialport headers in /ucrt64
CLI_INCS  = -I$(CLI_DIR) -I$(CLI_LIB_DIR) $(if $(wildcard $(CLI_VCPKG_INC)),-idirafter $(CLI_VCPKG_INC),)
# a static libreplxx.a needs REPLXX_STATIC, otherwise the header expects a DLL and the link fails with __imp_ errors
CLI_DEFS  = -DREPLXX_STATIC
CLI_LIBS  = -lreplxx -lserialport -lsetupapi -lws2_32 -pthread

# regenerates src/cli/src/headers/codes.hpp (from protocol.inc) and messages_embed.hpp (from shell/messages.toml);
# runs before every `make cli` unless SKIP_CODEGEN=1
cli-codegen:
	@echo "[MAKE] Regenerating codes.hpp and messages_embed.hpp..."
	$(PYTHON) $(CLI_DIR)/scripts/gen_codes.py
	$(PYTHON) $(CLI_DIR)/scripts/embed_messages.py

cli: $(if $(SKIP_CODEGEN),,cli-codegen)
	@echo "[MAKE] Compiling Zenith Core BIOS CLI (UCRT64)..."
	$(CXX) $(CXXFLAGS) $(CLI_DEFS) $(CLI_INCS) \
		$(CLI_SRCS) \
		$(CLI_LIBS) \
		-o $(CLI_EXE)
	@echo "[MAKE] CLI build complete: $(CLI_EXE)"

cli-run: cli
	@echo "[MAKE] Launching the CLI..."
	$(CLI_EXE)

cli-clean:
	@echo "[MAKE] Sweeping away the CLI build..."
	rm -f $(CLI_EXE) $(CLI_DIR)/src/headers/messages_embed.hpp $(CLI_DIR)/src/headers/codes.hpp