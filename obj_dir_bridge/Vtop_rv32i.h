// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP_RV32I_H_
#define VERILATED_VTOP_RV32I_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop_rv32i final {
  public:

    // INTERNAL VARIABLES
    Vtop__Syms* vlSymsp;
    const char* vlNamep;

    // PARAMETERS
    static constexpr CData/*1:0*/ RESP_OKAY = 0U;
    static constexpr CData/*1:0*/ RESP_SLVERR = 2U;
    static constexpr CData/*1:0*/ RESP_DECERR = 3U;
    static constexpr IData/*31:0*/ CPU_CLOCK_FREQ = 0x00989680U;
    static constexpr IData/*31:0*/ DATA_WIDTH = 0x00000020U;
    static constexpr IData/*31:0*/ ADDR_WIDTH = 5U;
    static constexpr IData/*31:0*/ NOP_INSTR = 0x00000013U;
    static constexpr IData/*31:0*/ BITS_FIT = 3U;
    static constexpr IData/*31:0*/ ROM_SIZE_BYTES = 0x00002000U;
    static constexpr IData/*31:0*/ RAM_SIZE_BYTES = 0x00020000U;
    static constexpr IData/*31:0*/ MMIO_OFFSET = 0x80000000U;
    static constexpr IData/*31:0*/ MMIO_SIZE_BYTES = 0x80000000U;
    static constexpr IData/*31:0*/ ROM_BASE = 0U;
    static constexpr IData/*31:0*/ RAM_BASE = 0x00002000U;
    static constexpr IData/*31:0*/ RAM_END = 0x00022000U;
    static constexpr IData/*31:0*/ RESET_VECTOR = 0U;

    // CONSTRUCTORS
    Vtop_rv32i();
    ~Vtop_rv32i();
    void ctor(Vtop__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtop_rv32i);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
