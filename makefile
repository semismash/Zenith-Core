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

.PHONY: all compile run sim clean asm

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

clean:
	@echo "[MAKE] Sweeping away generated simulation files..."
	rm -rf obj_dir tmp/program.bin tmp/program.o tmp/program.elf
