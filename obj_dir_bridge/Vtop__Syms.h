// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTOP__SYMS_H_
#define VERILATED_VTOP__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtop.h"

// INCLUDE MODULE CLASSES
#include "Vtop___024root.h"
#include "Vtop___024unit.h"
#include "Vtop_uart.h"
#include "Vtop_rv32i.h"

// DPI TYPES for DPI Export callbacks (Internal use)

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtop__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtop* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtop___024root                 TOP;
    Vtop_rv32i                     TOP__rv32i;
    Vtop_uart                      TOP__uart;

    // SCOPE NAMES
    VerilatedScope* __Vscopep_TOP;
    VerilatedScope* __Vscopep_rv32i;
    VerilatedScope* __Vscopep_top;
    VerilatedScope* __Vscopep_top__u_cpu;
    VerilatedScope* __Vscopep_top__u_cpu__u_alu;
    VerilatedScope* __Vscopep_top__u_cpu__u_branch_unit;
    VerilatedScope* __Vscopep_top__u_cpu__u_data_decoder;
    VerilatedScope* __Vscopep_top__u_cpu__u_decoder;
    VerilatedScope* __Vscopep_top__u_cpu__u_decoder__u_imm_gen;
    VerilatedScope* __Vscopep_top__u_cpu__u_ex_mem;
    VerilatedScope* __Vscopep_top__u_cpu__u_fetch;
    VerilatedScope* __Vscopep_top__u_cpu__u_fetch__unnamedblk1;
    VerilatedScope* __Vscopep_top__u_cpu__u_fetch__unnamedblk2;
    VerilatedScope* __Vscopep_top__u_cpu__u_hazard_unit;
    VerilatedScope* __Vscopep_top__u_cpu__u_hazard_unit__u_dep_analyzer;
    VerilatedScope* __Vscopep_top__u_cpu__u_hazard_unit__u_fwd_unit;
    VerilatedScope* __Vscopep_top__u_cpu__u_hazard_unit__u_stall_unit;
    VerilatedScope* __Vscopep_top__u_cpu__u_id_ex;
    VerilatedScope* __Vscopep_top__u_cpu__u_if_id;
    VerilatedScope* __Vscopep_top__u_cpu__u_lsu;
    VerilatedScope* __Vscopep_top__u_cpu__u_mem_wb;
    VerilatedScope* __Vscopep_top__u_cpu__u_meta;
    VerilatedScope* __Vscopep_top__u_cpu__u_mmio_interface;
    VerilatedScope* __Vscopep_top__u_cpu__u_pc;
    VerilatedScope* __Vscopep_top__u_cpu__u_pc__unnamedblk1;
    VerilatedScope* __Vscopep_top__u_cpu__u_reg_file;
    VerilatedScope* __Vscopep_top__u_cpu__u_uart_module;
    VerilatedScope* __Vscopep_top__u_cpu__u_uart_module__u_baud_rate_gen;
    VerilatedScope* __Vscopep_top__u_cpu__u_uart_module__u_uart_rx;
    VerilatedScope* __Vscopep_top__u_cpu__u_uart_module__u_uart_tx;
    VerilatedScope* __Vscopep_top__u_cpu__u_write_back;
    VerilatedScope* __Vscopep_top__u_mem;
    VerilatedScope* __Vscopep_top__u_mem__u_boot_rom;
    VerilatedScope* __Vscopep_top__u_mem__u_boot_rom__unnamedblk1;
    VerilatedScope* __Vscopep_top__u_mem__u_default_data;
    VerilatedScope* __Vscopep_top__u_mem__u_default_if;
    VerilatedScope* __Vscopep_top__u_mem__u_ram;
    VerilatedScope* __Vscopep_top__u_mem__u_ram__unnamedblk1;
    VerilatedScope* __Vscopep_uart;

    // CONSTRUCTORS
    Vtop__Syms(VerilatedContext* contextp, const char* namep, Vtop* modelp);
    ~Vtop__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
