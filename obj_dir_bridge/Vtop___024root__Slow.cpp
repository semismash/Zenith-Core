// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

// Parameter definitions for Vtop___024root
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_reg_file__DOT__DATA_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_reg_file__DOT__ADDR_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_fetch__DOT__DATA_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_fetch__DOT__MAX_OUTSTANDING;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_fetch__DOT__PTR_W;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_fetch__DOT__CNT_W;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_decoder__DOT__DATA_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_decoder__DOT__ADDR_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_alu__DOT__DATA_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_alu__DOT__ADDR_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_alu__DOT__SHAMT_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_lsu__DOT__DATA_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_uart_module__DOT__CLK_FREQ;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_uart_module__DOT__BAUD_RATE;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_uart_module__DOT__SAMPLING_RATE;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__CLK_FREQ;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__BAUD_RATE;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__SAMPLING_RATE;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__MAX;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__WIDTH;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__SAMPLING_RATE;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__TICK_CNT_W;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__SAMPLING_RATE;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__TICK_W;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__MID_TICK;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_mem__DOT__ROM_SIZE_BYTES;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_mem__DOT__RAM_SIZE_BYTES;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_mem__DOT__u_boot_rom__DOT__ROM_SIZE_BYTES;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_mem__DOT__u_boot_rom__DOT__ROM_WORDS;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_mem__DOT__u_boot_rom__DOT__ROM_AW;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_mem__DOT__u_ram__DOT__RAM_SIZE_BYTES;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_mem__DOT__u_ram__DOT__RAM_WORDS;
constexpr IData/*31:0*/ Vtop___024root::top__DOT__u_mem__DOT__u_ram__DOT__RAM_AW;


void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf);

Vtop___024root::Vtop___024root(Vtop__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtop___024root___ctor_var_reset(this);
}

void Vtop___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtop___024root::~Vtop___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
