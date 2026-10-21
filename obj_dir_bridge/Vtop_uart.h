// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP_UART_H_
#define VERILATED_VTOP_UART_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop_uart final {
  public:

    // INTERNAL VARIABLES
    Vtop__Syms* vlSymsp;
    const char* vlNamep;

    // PARAMETERS
    static constexpr IData/*31:0*/ UART_BAUD_RATE = 0x00002580U;
    static constexpr IData/*31:0*/ UART_SAMPLING_RATE = 0x00000010U;

    // CONSTRUCTORS
    Vtop_uart();
    ~Vtop_uart();
    void ctor(Vtop__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtop_uart);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
