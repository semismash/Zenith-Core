// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

// Parameter definitions for Vtop_uart
constexpr IData/*31:0*/ Vtop_uart::UART_BAUD_RATE;
constexpr IData/*31:0*/ Vtop_uart::UART_SAMPLING_RATE;



Vtop_uart::Vtop_uart() = default;
Vtop_uart::~Vtop_uart() = default;

void Vtop_uart::ctor(Vtop__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
}

void Vtop_uart::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtop_uart::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
