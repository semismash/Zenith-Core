# ==================================================================================================
# Zenith Core - Makefile
#
# Run from ROOT, inside the MSYS2 UCRT64 shell (verilator + riscv64-unknown-elf toolchain + g++).
#
# Layout
#   src/design      RTL                         programs/    your test programs (.s now, .c later)
#   src/rtl_sim     Verilator testbenches       build/       EVERYTHING generated (git-ignored, `make clean` wipes it)
#   src/firmware    BIOS source only             build/bin        zenith.exe
#   src/cli         CLI source                   build/bios       bios.hex, bios_sim.hex (+ .bin/.lst/.map)
#   src/fpga        constraints, board files     build/programs   <name>.hex (+ .bin/.lst)
#                                                build/tmp, obj_dir, obj_dir_bridge   intermediates
#
# Programs (loaded through the BIOS with the CLI's `load`)
#   make asm PROG=t_mem           programs/t_mem.s -> build/programs/t_mem.hex   (linked at 0x2000, no stop word)
#   make asm PROG=t_mem TEXT_BASE=0x3000    link for another load offset
#
# Core-only simulation (no BIOS: the program is the ROM image)
#   make run PROG=test_alu        build/programs/test_alu.rom.hex (linked at 0x0 + 0xFFFFFFFF stop word), build, run
#   make rom-asm PROG=test_alu    assemble the ROM image only
#   make compile                  build the Verilator sim only
#   make sim PROG=test_alu        run the already-built sim
#
# BIOS + CLI over TCP
#   make bios-sim                 BIOS for simulation (TIMEOUT_DIV=16) -> build/bios/bios_sim.hex
#   make bios                     BIOS for the FPGA   (TIMEOUT_DIV=1)  -> build/bios/bios.hex
#   make bridge-selftest          test the UART/TCP bridge on its own (no Verilator needed)
#   make bridge-run               bios-sim + build the networked sim + run it (ports 5555 data / 5556 reset)
#   make bridge-sim               run the already-built networked sim   (BRIDGE_ARGS="+BRIDGE_LOG" etc.)
#   make cli                      codegen + build build/bin/zenith.exe   (SKIP_CODEGEN=1 to skip the codegen)
#   make cli-run                  build and launch it
#
#   make clean                    delete build/        make clean-programs   delete only the assembled programs
#   make help
# ==================================================================================================

# --- directories ----------------------------------------------------------------------------------
SRC_DIR         = src
DESIGN_DIR      = $(SRC_DIR)/design
SIM_DIR         = $(SRC_DIR)/rtl_sim
FW_DIR          = $(SRC_DIR)/firmware
CLI_DIR         = $(SRC_DIR)/cli
PROG_DIR        = programs

BUILD_DIR       = build
BIN_DIR         = $(BUILD_DIR)/bin
BIOS_OUT_DIR    = $(BUILD_DIR)/bios
PROG_OUT        = $(BUILD_DIR)/programs
TMP_DIR         = $(BUILD_DIR)/tmp
SIM_OBJ_DIR     = $(BUILD_DIR)/obj_dir
BRIDGE_OBJ_DIR  = $(BUILD_DIR)/obj_dir_bridge

# path of a file inside build/, seen from inside build/ (the sims run there, so their waveforms land there too)
rel = $(patsubst $(BUILD_DIR)/%,%,$(1))

# --- memory map (must match rv32i.sv / bios.s) -----------------------------------------------------
# ROM size, only used for the size check of core-only ROM images
ROM_BYTES      ?= 8192
# program space the BIOS loads into: PRG_BASE .. PRG_TOP, minus the 8-byte jump-back tail the BIOS appends
PRG_BASE       ?= 0x2000
PRG_TOP        ?= 0x21000
PRG_MAX_BYTES  := $(shell echo $$(( $(PRG_TOP) - $(PRG_BASE) - 8 )))

# --- toolchain ------------------------------------------------------------------------------------
RISCV_PREFIX   ?= riscv64-unknown-elf-
AS      = $(RISCV_PREFIX)as
LD      = $(RISCV_PREFIX)ld
OBJCOPY = $(RISCV_PREFIX)objcopy
OBJDUMP = $(RISCV_PREFIX)objdump

VERILATOR = verilator
EXE_EXT  := $(if $(filter Windows_NT,$(OS)),.exe,)
WINSOCK_LIBS := $(if $(filter Windows_NT,$(OS)),-lws2_32,)

# --- RTL sources ----------------------------------------------------------------------------------
# Packages have to be compiled first, in dependency order (a package that imports another goes
# after it). Every other .sv under src/design is picked up automatically after them.
# Any new package file has to be added here.
# (If a stale/duplicate .sv in there causes "duplicate module" errors, move it out of src/design.)
PKG_SRCS     = $(DESIGN_DIR)/rv32i.sv $(DESIGN_DIR)/uart.sv
VERILOG_SRCS = $(PKG_SRCS) $(filter-out $(PKG_SRCS),$(sort $(shell find $(DESIGN_DIR) -name '*.sv')))

.PHONY: all help asm rom-asm prog-build compile run sim bios bios-sim bios-build \
        bridge-compile bridge-run bridge-sim bridge-selftest \
        cli cli-codegen cli-run cli-clean clean clean-programs

all: compile

help:
	@grep -E '^#   make ' $(firstword $(MAKEFILE_LIST)) | sed 's/^#   //'

# ==================================================================================================
# Programs
#   PROG names a file in programs/ (without extension). Two flavours of the same source:
#     asm      BIOS-loadable: linked at PRG_BASE, nothing appended      -> build/programs/<PROG>.hex
#     rom-asm  core-only ROM image: linked at 0, 0xFFFFFFFF appended    -> build/programs/<PROG>.rom.hex
#   The hex is one little-endian 32-bit word per line (what rom.sv's $readmemh and the CLI's `load` take); the
#   raw bytes (.bin) and a disassembly (.lst) are written next to it.
# ==================================================================================================
PROG       ?= program
ASM_SRC     = $(PROG_DIR)/$(PROG).s

asm:
	@$(MAKE) --no-print-directory prog-build PB_TAG=$(PROG) PB_BASE=$(if $(TEXT_BASE),$(TEXT_BASE),$(PRG_BASE)) PB_STOP=$(if $(AUTO_STOP),$(AUTO_STOP),0) PB_LIMIT=$(PRG_MAX_BYTES)
	@echo "[MAKE] Load it from the CLI with:  load $(PROG_OUT)/$(PROG).hex"

rom-asm:
	@$(MAKE) --no-print-directory prog-build PB_TAG=$(PROG).rom PB_BASE=$(if $(TEXT_BASE),$(TEXT_BASE),0x0) PB_STOP=$(if $(AUTO_STOP),$(AUTO_STOP),1) PB_LIMIT=$(shell echo $$(( $(ROM_BYTES) - 4 )))

# internal: needs PB_TAG, PB_BASE, PB_STOP, PB_LIMIT
prog-build:
	@if [ -z "$(PB_TAG)" ] || [ -z "$(PB_BASE)" ] || [ -z "$(PB_LIMIT)" ]; then \
		echo "[MAKE ERROR] prog-build is internal, use 'make asm' or 'make rom-asm'"; \
		exit 1; \
	fi
	@if [ ! -f $(ASM_SRC) ]; then \
		echo "[MAKE ERROR] $(ASM_SRC) not found! (programs live in $(PROG_DIR)/)"; \
		exit 1; \
	fi
	@mkdir -p $(TMP_DIR) $(PROG_OUT)
	@echo "[MAKE] Assembling $(ASM_SRC), linking at $(PB_BASE)..."
	$(AS) -march=rv32i -mabi=ilp32 -o $(TMP_DIR)/$(PROG).o $(ASM_SRC)
	$(LD) -m elf32lriscv -Ttext $(PB_BASE) -o $(TMP_DIR)/$(PB_TAG).elf $(TMP_DIR)/$(PROG).o
	$(OBJCOPY) -O binary $(TMP_DIR)/$(PB_TAG).elf $(PROG_OUT)/$(PB_TAG).bin
	$(OBJDUMP) -d $(TMP_DIR)/$(PB_TAG).elf > $(PROG_OUT)/$(PB_TAG).lst
	@size=$$(wc -c < $(PROG_OUT)/$(PB_TAG).bin); \
	if [ $$size -gt $(PB_LIMIT) ]; then \
		echo "[MAKE ERROR] program is $$size bytes, the limit is $(PB_LIMIT)!"; \
		exit 1; \
	fi; \
	echo "[MAKE] $$size bytes (limit $(PB_LIMIT))"
	@od -An -v -tx4 -w4 $(PROG_OUT)/$(PB_TAG).bin | tr -d ' ' > $(PROG_OUT)/$(PB_TAG).hex
	@$(if $(filter 1,$(PB_STOP)),echo ffffffff >> $(PROG_OUT)/$(PB_TAG).hex,true)
	@echo "[MAKE] Done: $(PROG_OUT)/$(PB_TAG).hex  (disassembly: $(PROG_OUT)/$(PB_TAG).lst)"

# ==================================================================================================
# Core-only Verilator simulation (the program is the ROM image, no BIOS, no UART bridge)
#   --public-flat-rw makes every internal signal reachable from sim_main.cpp (rootp->top__DOT__...).
#   The exe runs inside build/, so its waveform.vcd ends up in build/ and not in ROOT.
# ==================================================================================================
SIM_EXE   = $(SIM_OBJ_DIR)/Vtop$(EXE_EXT)
CPP_SRCS  = $(SIM_DIR)/sim_main.cpp
ROM_HEX   = $(PROG_OUT)/$(PROG).rom.hex

compile: $(VERILOG_SRCS) $(CPP_SRCS)
	@echo "[MAKE] Compiling SystemVerilog core and C++ testbench..."
	@mkdir -p $(SIM_OBJ_DIR)
	$(VERILATOR) --cc --exe --build -j -Wall -Wno-fatal --trace --public-flat-rw \
		-I$(DESIGN_DIR) \
		--Mdir $(SIM_OBJ_DIR) \
		-CFLAGS "-O2" \
		-LDFLAGS "-O2" \
		$(VERILOG_SRCS) $(CPP_SRCS) --top-module top

run: rom-asm compile
	@echo "[MAKE] Executing simulation ($(ROM_HEX))..."
	cd $(BUILD_DIR) && ./$(call rel,$(SIM_EXE)) +ROM_HEX=$(call rel,$(ROM_HEX))

sim:
	@if [ ! -f $(SIM_EXE) ]; then \
		echo "[MAKE ERROR] $(SIM_EXE) not found! Run 'make compile' first."; \
		exit 1; \
	fi
	@if [ ! -f $(ROM_HEX) ]; then \
		echo "[MAKE ERROR] $(ROM_HEX) not found! Run 'make rom-asm PROG=$(PROG)' first."; \
		exit 1; \
	fi
	@echo "[MAKE] Executing simulation directly ($(ROM_HEX))..."
	cd $(BUILD_DIR) && ./$(call rel,$(SIM_EXE)) +ROM_HEX=$(call rel,$(ROM_HEX))

# ==================================================================================================
# BIOS
#   Source: src/firmware/{bios.s, linker.ld, protocol.inc} (override with BIOS_DIR=...)
#   The sim build shortens the BIOS timeouts by TIMEOUT_DIV (bios.s: .ifndef TIMEOUT_DIV), the FPGA build keeps
#   the real ones. Never put bios_sim.hex on the board.
# ==================================================================================================
BIOS_DIR        ?= $(FW_DIR)
BIOS_SRC         = $(BIOS_DIR)/bios.s
BIOS_LD          = $(BIOS_DIR)/linker.ld
BIOS_HEX         = $(BIOS_OUT_DIR)/bios.hex
BIOS_SIM_HEX     = $(BIOS_OUT_DIR)/bios_sim.hex
SIM_TIMEOUT_DIV ?= 16

bios-sim:
	@$(MAKE) --no-print-directory bios-build BIOS_TD=$(SIM_TIMEOUT_DIV) BIOS_OUT=$(BIOS_SIM_HEX) BIOS_TAG=bios_sim

bios:
	@$(MAKE) --no-print-directory bios-build BIOS_TD=1 BIOS_OUT=$(BIOS_HEX) BIOS_TAG=bios

# internal: needs BIOS_TD, BIOS_OUT, BIOS_TAG
bios-build:
	@if [ -z "$(BIOS_OUT)" ] || [ -z "$(BIOS_TAG)" ] || [ -z "$(BIOS_TD)" ]; then \
		echo "[MAKE ERROR] bios-build is internal, use 'make bios-sim' or 'make bios'"; \
		exit 1; \
	fi
	@for f in $(BIOS_SRC) $(BIOS_LD) $(BIOS_DIR)/protocol.inc; do \
		if [ ! -f $$f ]; then echo "[MAKE ERROR] $$f not found! (BIOS_DIR=$(BIOS_DIR))"; exit 1; fi; \
	done
	@mkdir -p $(TMP_DIR) $(BIOS_OUT_DIR)
	@echo "[MAKE] Assembling BIOS (TIMEOUT_DIV=$(BIOS_TD))..."
	$(AS) -march=rv32i -mabi=ilp32 -I $(BIOS_DIR) --defsym TIMEOUT_DIV=$(BIOS_TD) -o $(TMP_DIR)/$(BIOS_TAG).o $(BIOS_SRC)
	$(LD) -m elf32lriscv -T $(BIOS_LD) -Map=$(BIOS_OUT_DIR)/$(BIOS_TAG).map -o $(TMP_DIR)/$(BIOS_TAG).elf $(TMP_DIR)/$(BIOS_TAG).o
	$(OBJCOPY) -O binary $(TMP_DIR)/$(BIOS_TAG).elf $(BIOS_OUT_DIR)/$(BIOS_TAG).bin
	$(OBJDUMP) -d $(TMP_DIR)/$(BIOS_TAG).elf > $(BIOS_OUT_DIR)/$(BIOS_TAG).lst
	@size=$$(wc -c < $(BIOS_OUT_DIR)/$(BIOS_TAG).bin); \
	if [ $$size -gt $(ROM_BYTES) ]; then echo "[MAKE ERROR] BIOS is $$size bytes, ROM is $(ROM_BYTES)!"; exit 1; fi; \
	echo "[MAKE] BIOS image: $$size of $(ROM_BYTES) ROM bytes"
	@od -An -v -tx4 -w4 $(BIOS_OUT_DIR)/$(BIOS_TAG).bin | tr -d ' ' > $(BIOS_OUT)
	@echo "[MAKE] Done: $(BIOS_OUT)  (disassembly: $(BIOS_OUT_DIR)/$(BIOS_TAG).lst)"

# ==================================================================================================
# Networked simulation (BIOS + CLI over TCP)
#   A second Verilator build, separate from the core-only testbench: own output dir, own executable.
#   On Windows the bridge needs Winsock (-lws2_32). Runs inside build/ like the core-only sim.
# ==================================================================================================
BRIDGE_EXE      = $(BRIDGE_OBJ_DIR)/zenith_bridge$(EXE_EXT)
BRIDGE_SRCS     = $(SIM_DIR)/sim_bridge.cpp
BRIDGE_HDRS     = $(SIM_DIR)/uart_bridge.hpp

bridge-compile: $(VERILOG_SRCS) $(BRIDGE_SRCS) $(BRIDGE_HDRS)
	@echo "[MAKE] Compiling the networked simulation..."
	@mkdir -p $(BRIDGE_OBJ_DIR)
	$(VERILATOR) --cc --exe --build -j -Wall -Wno-fatal --trace --public-flat-rw \
		-I$(DESIGN_DIR) \
		--Mdir $(BRIDGE_OBJ_DIR) -o zenith_bridge$(EXE_EXT) \
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
	cd $(BUILD_DIR) && ./$(call rel,$(BRIDGE_EXE)) +ROM_HEX=$(call rel,$(BIOS_SIM_HEX)) $(BRIDGE_ARGS)

# the bridge without Verilator: a C++ port of the UART RTL talks to it over real sockets
bridge-selftest:
	@mkdir -p $(TMP_DIR)
	$(CXX) -std=c++17 -O2 -Wall -Wextra -o $(TMP_DIR)/test_uart_bridge$(EXE_EXT) $(SIM_DIR)/test_uart_bridge.cpp $(WINSOCK_LIBS)
	$(TMP_DIR)/test_uart_bridge$(EXE_EXT)

# ==================================================================================================
# CLI (src/cli) - native Windows build in the SAME MSYS2 UCRT64 shell as everything else
#   libserialport : pacman -S mingw-w64-ucrt-x86_64-libserialport      (headers/libs live in /ucrt64)
#   replxx        : built once from source and installed into /ucrt64     (no MSYS2 package exists)
#   CLI11, toml++ : header only, taken from src/cli/lib, from vcpkg_installed (if it is still there) or from
#                   /ucrt64/include (pacman -S mingw-w64-ucrt-x86_64-cli11 mingw-w64-ucrt-x86_64-tomlplusplus)
# ==================================================================================================
CLI_LIB_DIR    = $(CLI_DIR)/lib
CLI_VCPKG_INC  = $(CLI_DIR)/vcpkg_installed/x64-mingw-dynamic/include
CLI_EXE        = $(BIN_DIR)/zenith$(EXE_EXT)
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
	@mkdir -p $(BIN_DIR)
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

# ==================================================================================================
# Cleaning
# ==================================================================================================
clean:
	@echo "[MAKE] Deleting $(BUILD_DIR)/ ..."
	rm -rf $(BUILD_DIR)

clean-programs:
	@echo "[MAKE] Deleting assembled programs..."
	rm -rf $(PROG_OUT) $(TMP_DIR)