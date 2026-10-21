// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

// Parameter definitions for Vtop_rv32i
constexpr CData/*1:0*/ Vtop_rv32i::RESP_OKAY;
constexpr CData/*1:0*/ Vtop_rv32i::RESP_SLVERR;
constexpr CData/*1:0*/ Vtop_rv32i::RESP_DECERR;
constexpr IData/*31:0*/ Vtop_rv32i::CPU_CLOCK_FREQ;
constexpr IData/*31:0*/ Vtop_rv32i::DATA_WIDTH;
constexpr IData/*31:0*/ Vtop_rv32i::ADDR_WIDTH;
constexpr IData/*31:0*/ Vtop_rv32i::NOP_INSTR;
constexpr IData/*31:0*/ Vtop_rv32i::BITS_FIT;
constexpr IData/*31:0*/ Vtop_rv32i::ROM_SIZE_BYTES;
constexpr IData/*31:0*/ Vtop_rv32i::RAM_SIZE_BYTES;
constexpr IData/*31:0*/ Vtop_rv32i::MMIO_OFFSET;
constexpr IData/*31:0*/ Vtop_rv32i::MMIO_SIZE_BYTES;
constexpr IData/*31:0*/ Vtop_rv32i::ROM_BASE;
constexpr IData/*31:0*/ Vtop_rv32i::RAM_BASE;
constexpr IData/*31:0*/ Vtop_rv32i::RAM_END;
constexpr IData/*31:0*/ Vtop_rv32i::RESET_VECTOR;



Vtop_rv32i::Vtop_rv32i() = default;
Vtop_rv32i::~Vtop_rv32i() = default;

void Vtop_rv32i::ctor(Vtop__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
}

void Vtop_rv32i::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtop_rv32i::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
