// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"


Vtop___024unit::Vtop___024unit() = default;
Vtop___024unit::~Vtop___024unit() = default;

void Vtop___024unit::ctor(Vtop__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
}

void Vtop___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtop___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
