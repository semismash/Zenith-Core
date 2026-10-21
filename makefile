VERILATOR = verilator
SIM_EXE   = ./obj_dir/Vtop.exe
SRC_DIR = src

# RISC-V Toolchain Configurations
AS      = riscv64-unknown-elf-as
LD      = riscv64-unknown-elf-ld
OBJCOPY = riscv64-unknown-elf-objcopy


# design
VERILOG_SRCS = \
	$(SRC_DIR)/design/rv32i.sv \
	$(SRC_DIR)/design/top.sv \
	$(SRC_DIR)/design/uart.sv \
	$(SRC_DIR)/design/core/meta.sv \
	$(SRC_DIR)/design/core/rv32i_core.sv \
	$(SRC_DIR)/design/core/components/default_slave.sv \
	$(SRC_DIR)/design/core/components/mmio_interface.sv \
	$(SRC_DIR)/design/core/components/pc.sv \
	$(SRC_DIR)/design/core/components/reg_file.sv \
	$(SRC_DIR)/design/core/hazard_unit/dep_analyzer.sv \
	$(SRC_DIR)/design/core/hazard_unit/fwd_unit.sv \
	$(SRC_DIR)/design/core/hazard_unit/hazard_unit.sv \
	$(SRC_DIR)/design/core/hazard_unit/stall_unit.sv \
	$(SRC_DIR)/design/core/pipeline/ex_mem.sv \
	$(SRC_DIR)/design/core/pipeline/id_ex.sv \
	$(SRC_DIR)/design/core/pipeline/if_id.sv \
	$(SRC_DIR)/design/core/pipeline/mem_wb.sv \
	$(SRC_DIR)/design/core/uart_module/baud_tick.sv \
	$(SRC_DIR)/design/core/uart_module/uart_module.sv \
	$(SRC_DIR)/design/core/uart_module/uart_rx.sv \
	$(SRC_DIR)/design/core/uart_module/uart_tx.sv \
	$(SRC_DIR)/design/core/units/alu.sv \
	$(SRC_DIR)/design/core/units/branch_unit.sv \
	$(SRC_DIR)/design/core/units/data_decoder.sv \
	$(SRC_DIR)/design/core/units/decoder.sv \
	$(SRC_DIR)/design/core/units/fetch.sv \
	$(SRC_DIR)/design/core/units/imm_gen.sv \
	$(SRC_DIR)/design/core/units/lsu.sv \
	$(SRC_DIR)/design/core/units/write_back.sv \
	$(SRC_DIR)/design/mem/mem.sv \
	$(SRC_DIR)/design/mem/ram.sv \
	$(SRC_DIR)/design/mem/rom.sv

# testbench
CPP_SRCS = $(SRC_DIR)/sim_main.cpp

# ----------------------------------------------------------------------------------------------
# CLI (ROOT/src/cli) - built natively on Windows (MSYS2 MinGW64 shell: g++, make, pacman all run
# from there), since it needs real COM ports and a console. Verilator/riscv-gnu-toolchain above
# keep running in WSL2 - they're invoked from a *separate* WSL shell, this Makefile's asm/compile/
# run/sim targets are unaffected and still expect a Linux (WSL) environment.
#
# Library locations (see chat for how to obtain each):
#   CLI_LIB_DIR    lib/CLI11.hpp, lib/toml.hpp                 (header-only, drop in place)
#   CLI_VCPKG_DIR  vcpkg install tree (replxx, libserialport)  (vcpkg_installed/x64-mingw-dynamic)
# Override on the command line if yours differs, e.g.:
#   mingw32-make cli CLI_VCPKG_DIR=C:/vcpkg_installed/x64-mingw-dynamic
# ----------------------------------------------------------------------------------------------
CLI_DIR        = $(SRC_DIR)/cli
CLI_LIB_DIR    = $(CLI_DIR)/lib
CLI_VCPKG_DIR  = $(CLI_DIR)/vcpkg_installed/x64-mingw-dynamic
CLI_EXE        = $(CLI_DIR)/zenith.exe

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

CXX       = g++
CXXFLAGS  = -std=c++23 -O2 -Wall -Wextra
CLI_INCS  = -I$(CLI_LIB_DIR) -I$(CLI_VCPKG_DIR)/include
CLI_LIBD  = -L$(CLI_VCPKG_DIR)/lib
CLI_LIBS  = -lreplxx -lserialport -lsetupapi -lws2_32 -pthread

.PHONY: all compile run sim clean asm cli cli-codegen cli-run cli-clean

all: compile

asm:
	@if [ ! -f program.s ]; then \
		echo "[MAKE ERROR] program.s not found in root directory!"; \
		exit 1; \
	fi
	@echo "[MAKE] Assembling program.s..."
	$(AS) -march=rv32i -mabi=ilp32 -o tmp/program.o program.s
	@echo "[MAKE] Linking ELF image at base address 0x0..."
	$(LD) -m elf32lriscv -Ttext 0x0 -o tmp/program.elf tmp/program.o
	@echo "[MAKE] Extracting raw machine bytes to binary..."
	$(OBJCOPY) -O binary tmp/program.elf tmp/program.bin
	@rm -f tmp/program.o tmp/program.elf
	@echo "[MAKE] Assembly compilation complete!"

compile: $(VERILOG_SRCS) $(CPP_SRCS)
	@echo "[MAKE] Compiling SystemVerilog core and C++ testbench..."
	$(VERILATOR) --cc --exe --build -j -Wall -Wno-fatal --trace -I$(SRC_DIR) \
		-CFLAGS "-O2" \
		-LDFLAGS "-O2" \
		$(VERILOG_SRCS) $(CPP_SRCS) --top-module top

run: asm compile
	@echo "[MAKE] Executing simulation wrapper..."
	$(SIM_EXE)

sim:
	@if [ ! -f $(SIM_EXE) ]; then \
		echo "[MAKE ERROR] Simulation executable $(SIM_EXE) not found! Run 'make compile' first."; \
		exit 1; \
	fi
	@echo "[MAKE] Executing simulation wrapper directly..."
	$(SIM_EXE)

# regenerates src/headers/codes.hpp (from protocol.inc) and src/headers/messages_embed.hpp
# (from shell/messages.toml); run this before `cli` whenever either source file changes
cli-codegen:
	@echo "[MAKE] Regenerating codes.hpp and messages_embed.hpp..."
	python3 $(CLI_DIR)/scripts/gen_codes.py
	python3 $(CLI_DIR)/scripts/embed_messages.py

cli: cli-codegen
	@echo "[MAKE] Compiling Zenith Core BIOS CLI (native Windows / MinGW64)..."
	$(CXX) $(CXXFLAGS) -I$(CLI_DIR) $(CLI_INCS) \
		$(CLI_SRCS) \
		$(CLI_LIBD) $(CLI_LIBS) \
		-o $(CLI_EXE)
	@echo "[MAKE] CLI build complete: $(CLI_EXE)"

cli-run: cli
	@echo "[MAKE] Launching the CLI..."
	$(CLI_EXE)

cli-clean:
	@echo "[MAKE] Sweeping away the CLI build..."
	rm -f $(CLI_EXE) $(CLI_DIR)/src/headers/messages_embed.hpp $(CLI_DIR)/src/headers/codes.hpp

clean:
	@echo "[MAKE] Sweeping away generated simulation files..."
	rm -rf obj_dir tmp/program.bin tmp/program.o tmp/program.elf