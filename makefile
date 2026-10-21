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
#   make run TELEMETRY=1          build the TB with the telemetry printout (see sim_main.cpp)
#   make run AUTO_STOP=0          do not append the 0xFFFFFFFF stop word to the hex
#   make clean
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
# 1 = define HAVE_TELEMETRY in the testbench (needs meta_* signals in top.sv)
TELEMETRY   ?= 0

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
TB_DEFS      = $(if $(filter 1,$(TELEMETRY)),-DHAVE_TELEMETRY,)

.PHONY: all asm compile run sim clean

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
		-CFLAGS "-O2 $(TB_DEFS)" \
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

clean:
	@echo "[MAKE] Sweeping away generated simulation files..."
	rm -rf obj_dir $(TMP_DIR) waveform.vcd


# ==================================================================================================
# CLI (ROOT/src/cli) - DISABLED for now, re-enable (uncomment) when we move to the bridge/CLI stage.
# Built natively on Windows (MSYS2 MinGW64 shell). Remember to add cli cli-codegen cli-run cli-clean
# back to the .PHONY line above.
# ==================================================================================================
# CLI_DIR        = $(SRC_DIR)/cli
# CLI_LIB_DIR    = $(CLI_DIR)/lib
# CLI_VCPKG_DIR  = $(CLI_DIR)/vcpkg_installed/x64-mingw-dynamic
# CLI_EXE        = $(CLI_DIR)/zenith.exe
#
# CLI_SRCS = \
# 	$(CLI_DIR)/src/main.cpp \
# 	$(CLI_DIR)/src/cli.cpp \
# 	$(CLI_DIR)/src/shell/shell.cpp \
# 	$(CLI_DIR)/src/shell/cmdparse.cpp \
# 	$(CLI_DIR)/src/shell/responseprint.cpp \
# 	$(CLI_DIR)/src/client/client.cpp \
# 	$(CLI_DIR)/src/client/bytegen.cpp \
# 	$(CLI_DIR)/src/client/cmd_analyze.cpp \
# 	$(CLI_DIR)/src/interface/uart_module.cpp \
# 	$(CLI_DIR)/src/profile/profile.cpp \
# 	$(CLI_DIR)/src/profile/config.cpp
#
# CXX       = g++
# CXXFLAGS  = -std=c++23 -O2 -Wall -Wextra
# CLI_INCS  = -I$(CLI_LIB_DIR) -I$(CLI_VCPKG_DIR)/include
# CLI_LIBD  = -L$(CLI_VCPKG_DIR)/lib
# CLI_LIBS  = -lreplxx -lserialport -lsetupapi -lws2_32 -pthread
#
# # regenerates src/headers/codes.hpp (from protocol.inc) and src/headers/messages_embed.hpp
# # (from shell/messages.toml); run this before `cli` whenever either source file changes
# cli-codegen:
# 	@echo "[MAKE] Regenerating codes.hpp and messages_embed.hpp..."
# 	python3 $(CLI_DIR)/scripts/gen_codes.py
# 	python3 $(CLI_DIR)/scripts/embed_messages.py
#
# cli: cli-codegen
# 	@echo "[MAKE] Compiling Zenith Core BIOS CLI (native Windows / MinGW64)..."
# 	$(CXX) $(CXXFLAGS) -I$(CLI_DIR) $(CLI_INCS) \
# 		$(CLI_SRCS) \
# 		$(CLI_LIBD) $(CLI_LIBS) \
# 		-o $(CLI_EXE)
# 	@echo "[MAKE] CLI build complete: $(CLI_EXE)"
#
# cli-run: cli
# 	@echo "[MAKE] Launching the CLI..."
# 	$(CLI_EXE)
#
# cli-clean:
# 	@echo "[MAKE] Sweeping away the CLI build..."
# 	rm -f $(CLI_EXE) $(CLI_DIR)/src/headers/messages_embed.hpp $(CLI_DIR)/src/headers/codes.hpp