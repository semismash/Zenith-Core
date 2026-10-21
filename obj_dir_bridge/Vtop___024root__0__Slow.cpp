// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

VL_ATTR_COLD void Vtop___024root___eval_static__TOP(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root___eval_static__TOP(vlSelf);
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__cpu_clk__0 
        = vlSelfRef.top__DOT__cpu_clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__rst_n__0 
        = vlSelfRef.top__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__clk__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_reg_file__DOT__clk__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_reg_file__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_fetch__DOT__clk__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_fetch__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_if_id__DOT__clk__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_if_id__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_id_ex__DOT__clk__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_id_ex__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_ex_mem__DOT__clk__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_ex_mem__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_lsu__DOT__clk__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_lsu__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_data_decoder__DOT__clk__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_data_decoder__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_mmio_interface__DOT__clk__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_mem_wb__DOT__clk__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_mem_wb__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_meta__DOT__clk__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_meta__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__clk__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__clk__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__clk__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__clk__0 
        = vlSelfRef.top__DOT__u_mem__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_mem__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_boot_rom__DOT__clk__0 
        = vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_boot_rom__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_ram__DOT__clk__0 
        = vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_ram__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_default_if__DOT__clk__0 
        = vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_default_if__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_default_data__DOT__clk__0 
        = vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_default_data__DOT__rst_n__0 
        = vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__rst_n;
}

VL_ATTR_COLD void Vtop___024root___eval_static__TOP(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static__TOP\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9124449291403006271ull);
    vlSelf->top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2324538194100007937ull);
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__unnamedblk1__DOT__hex_file = ""s;
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root___eval_initial__TOP(vlSelf);
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial__TOP\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ top__DOT__u_mem__DOT__u_boot_rom__DOT____VlemExpr_0;
    // Body
    vlSelfRef.top__DOT__u_mem__DOT__data_wready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__data_awready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__data_arready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__if_arready = 1U;
    vlSelfRef.top__DOT__data_bready = 1U;
    vlSelfRef.top__DOT__data_rready = 1U;
    vlSelfRef.top__DOT__mmcm_locked = 1U;
    vlSelfRef.top__DOT__if_rready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__if_rready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_rready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__clear = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__data_rready_out = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__data_bready_out = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_rready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_bready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_bready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_arready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_rready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_awready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_bready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__data_rready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__data_bready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_bready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_bready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_arready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_awready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_wready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_bready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_arready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_awready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wready = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__clear = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__if_rready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__rom_if_arready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_rready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__rom_if_rresp = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_arready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_rresp = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_awready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_wready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_bresp = 2U;
    top__DOT__u_mem__DOT__u_boot_rom__DOT____VlemExpr_0 
        = VL_VALUEPLUSARGS_INN(64, "ROM_HEX=%s"s, vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__unnamedblk1__DOT__hex_file);
    if ((! top__DOT__u_mem__DOT__u_boot_rom__DOT____VlemExpr_0)) {
        vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__unnamedblk1__DOT__hex_file = "bios.hex"s;
    }
    VL_READMEM_N(true, 32, 2048, 0, vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__unnamedblk1__DOT__hex_file
                 ,  &(vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__container)
                 , 0, ~0ULL);
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_arready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_arready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_awready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_wready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_rresp = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_rresp = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_bresp = 2U;
    vlSelfRef.top__DOT__u_mem__DOT__ram_if_arready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_rready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__ram_if_rresp = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_arready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_rresp = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_awready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_wready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_bresp = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_arready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_arready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_awready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_wready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_rresp = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_rresp = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_bresp = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__dif_arready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__dif_rdata = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__rready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__dif_rresp = 3U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__awaddr = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__awvalid = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__dif_awready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__wdata = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__wstrb = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__wvalid = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__dif_wready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__bready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__dif_bresp = 3U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__arready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__awready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__wready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__rdata = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__rresp = 3U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__bresp = 3U;
    vlSelfRef.top__DOT__u_mem__DOT__ddt_arready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__ddt_rdata = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__ddt_rresp = 3U;
    vlSelfRef.top__DOT__u_mem__DOT__ddt_awready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__ddt_wready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__ddt_bresp = 3U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__arready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__awready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__wready = 1U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__rdata = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__rresp = 3U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__bresp = 3U;
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("src/design\\top.sv", 5, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 10000 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtop___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtop___024root___eval_triggers_vec__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_triggers_vec__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtop___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtop___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_anySet__stl\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtop___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtop___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtop___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtop___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vtop___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge top.cpu_clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge top.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @(posedge top.u_cpu.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @(negedge top.u_cpu.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 4U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 4 is active: @(posedge top.u_cpu.u_reg_file.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 5U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 5 is active: @(negedge top.u_cpu.u_reg_file.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 6U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 6 is active: @(posedge top.u_cpu.u_fetch.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 7U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 7 is active: @(negedge top.u_cpu.u_fetch.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 8U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 8 is active: @(posedge top.u_cpu.u_if_id.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 9U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 9 is active: @(negedge top.u_cpu.u_if_id.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000000aU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 10 is active: @(posedge top.u_cpu.u_id_ex.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000000bU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 11 is active: @(negedge top.u_cpu.u_id_ex.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000000cU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 12 is active: @(posedge top.u_cpu.u_ex_mem.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000000dU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 13 is active: @(negedge top.u_cpu.u_ex_mem.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000000eU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 14 is active: @(posedge top.u_cpu.u_lsu.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000000fU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 15 is active: @(negedge top.u_cpu.u_lsu.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000010U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 16 is active: @(posedge top.u_cpu.u_data_decoder.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000011U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 17 is active: @(negedge top.u_cpu.u_data_decoder.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000012U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 18 is active: @(posedge top.u_cpu.u_mmio_interface.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000013U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 19 is active: @(negedge top.u_cpu.u_mmio_interface.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000014U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 20 is active: @(posedge top.u_cpu.u_mem_wb.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000015U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 21 is active: @(negedge top.u_cpu.u_mem_wb.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000016U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 22 is active: @(posedge top.u_cpu.u_meta.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000017U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 23 is active: @(negedge top.u_cpu.u_meta.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000018U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 24 is active: @(posedge top.u_cpu.u_uart_module.u_baud_rate_gen.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000019U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 25 is active: @(negedge top.u_cpu.u_uart_module.u_baud_rate_gen.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000001aU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 26 is active: @(posedge top.u_cpu.u_uart_module.u_uart_tx.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000001bU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 27 is active: @(negedge top.u_cpu.u_uart_module.u_uart_tx.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000001cU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 28 is active: @(posedge top.u_cpu.u_uart_module.u_uart_rx.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000001dU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 29 is active: @(negedge top.u_cpu.u_uart_module.u_uart_rx.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000001eU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 30 is active: @(posedge top.u_mem.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x0000001fU)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 31 is active: @(negedge top.u_mem.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000020U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 32 is active: @(posedge top.u_mem.u_boot_rom.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000021U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 33 is active: @(negedge top.u_mem.u_boot_rom.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000022U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 34 is active: @(posedge top.u_mem.u_ram.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000023U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 35 is active: @(negedge top.u_mem.u_ram.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000024U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 36 is active: @(posedge top.u_mem.u_default_if.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000025U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 37 is active: @(negedge top.u_mem.u_default_if.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000026U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 38 is active: @(posedge top.u_mem.u_default_data.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 0x00000027U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 39 is active: @(negedge top.u_mem.u_default_data.rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1638864771569018232ull);
    vlSelf->led = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 14009161575225144129ull);
    vlSelf->i_rx = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12198057735809740419ull);
    vlSelf->o_tx = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 598518241268350681ull);
    vlSelf->top__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17741742976451700217ull);
    vlSelf->top__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14231290532059103644ull);
    vlSelf->top__DOT__led = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 9985121575536492059ull);
    vlSelf->top__DOT__i_rx = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11692890848332476011ull);
    vlSelf->top__DOT__o_tx = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7932833553665761448ull);
    vlSelf->top__DOT__cpu_clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4206076891273424050ull);
    vlSelf->top__DOT__mmcm_locked = 1U;
    ;
    vlSelf->top__DOT__rst_sync = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2559717649366408128ull);
    vlSelf->top__DOT__core_rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16755396315393746331ull);
    vlSelf->top__DOT__if_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16221231876571914004ull);
    vlSelf->top__DOT__if_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9705105521337566797ull);
    vlSelf->top__DOT__if_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17598374702292732375ull);
    vlSelf->top__DOT__if_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 348832079245604551ull);
    vlSelf->top__DOT__if_rready = 1U;
    ;
    vlSelf->top__DOT__if_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8575737250027345964ull);
    vlSelf->top__DOT__if_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10598689172775003539ull);
    vlSelf->top__DOT__data_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8316044051849798005ull);
    vlSelf->top__DOT__data_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3673912827988051640ull);
    vlSelf->top__DOT__data_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2283742148748257789ull);
    vlSelf->top__DOT__data_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4114655009785684048ull);
    vlSelf->top__DOT__data_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 11713016566758666175ull);
    vlSelf->top__DOT__data_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2435245628409971015ull);
    vlSelf->top__DOT__data_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5853595192592117288ull);
    vlSelf->top__DOT__data_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14400635549520519112ull);
    vlSelf->top__DOT__data_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9266039482039024853ull);
    vlSelf->top__DOT__data_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 17061815993873166657ull);
    vlSelf->top__DOT__data_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7484870446793109062ull);
    vlSelf->top__DOT__data_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9126297532343279244ull);
    vlSelf->top__DOT__data_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6576278240631572791ull);
    vlSelf->top__DOT__data_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17809168030188264662ull);
    vlSelf->top__DOT__data_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16523122328297393000ull);
    vlSelf->top__DOT__data_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13893710738800185108ull);
    vlSelf->top__DOT__data_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12353181793027089881ull);
    vlSelf->top__DOT__halt = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6400994347834525699ull);
    vlSelf->top__DOT__instr_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3855564837602636107ull);
    vlSelf->top__DOT__data_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8167140621540713626ull);
    vlSelf->top__DOT__illegal_instr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3399563802915775014ull);
    vlSelf->top__DOT__stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3879500066681000023ull);
    vlSelf->top__DOT__u_cpu__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16567926023002496702ull);
    vlSelf->top__DOT__u_cpu__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9860291316912889012ull);
    vlSelf->top__DOT__u_cpu__DOT__if_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2014487846862453725ull);
    vlSelf->top__DOT__u_cpu__DOT__if_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1055031064688402867ull);
    vlSelf->top__DOT__u_cpu__DOT__if_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2208130187366544037ull);
    vlSelf->top__DOT__u_cpu__DOT__if_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8985997714576552899ull);
    vlSelf->top__DOT__u_cpu__DOT__if_rready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__if_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1877145970184097644ull);
    vlSelf->top__DOT__u_cpu__DOT__if_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 17581195345707279295ull);
    vlSelf->top__DOT__u_cpu__DOT__data_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 415744424671976990ull);
    vlSelf->top__DOT__u_cpu__DOT__data_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4354347611148540040ull);
    vlSelf->top__DOT__u_cpu__DOT__data_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8234865643994290280ull);
    vlSelf->top__DOT__u_cpu__DOT__data_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11176944061179141916ull);
    vlSelf->top__DOT__u_cpu__DOT__data_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 1271147910787510911ull);
    vlSelf->top__DOT__u_cpu__DOT__data_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9336334547768395110ull);
    vlSelf->top__DOT__u_cpu__DOT__data_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5832299318261226150ull);
    vlSelf->top__DOT__u_cpu__DOT__data_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5575170594401704754ull);
    vlSelf->top__DOT__u_cpu__DOT__data_bready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__data_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11320327842630128017ull);
    vlSelf->top__DOT__u_cpu__DOT__data_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7304350450329289411ull);
    vlSelf->top__DOT__u_cpu__DOT__data_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3375042340965289174ull);
    vlSelf->top__DOT__u_cpu__DOT__data_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11667737128678735363ull);
    vlSelf->top__DOT__u_cpu__DOT__data_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11367298186687823610ull);
    vlSelf->top__DOT__u_cpu__DOT__data_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17383302423901058971ull);
    vlSelf->top__DOT__u_cpu__DOT__data_rready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__data_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13028743107237619413ull);
    vlSelf->top__DOT__u_cpu__DOT__halt = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6627435080495307066ull);
    vlSelf->top__DOT__u_cpu__DOT__instr_fault_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1804323492376260258ull);
    vlSelf->top__DOT__u_cpu__DOT__data_fault_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12353850690048648280ull);
    vlSelf->top__DOT__u_cpu__DOT__illegal_instr_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13817364818702078484ull);
    vlSelf->top__DOT__u_cpu__DOT__stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17188706285506359592ull);
    vlSelf->top__DOT__u_cpu__DOT__i_rx = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2128764290866881978ull);
    vlSelf->top__DOT__u_cpu__DOT__o_tx = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16854106170721955721ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_pc_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15097604899420171104ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_if_id_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8078186626949710136ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_id_ex_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 223084719751230462ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_ex_mem_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4117061632852785908ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_mem_wb_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16225053052923729896ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_if_id_clear = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7893489290650109912ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_id_ex_clear = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5469036487018072866ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_meta_is_stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12873730535212990782ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_meta_is_l_use = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16572838530136802213ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_meta_branch_flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15078727076717298173ull);
    vlSelf->top__DOT__u_cpu__DOT__hz_meta_is_instr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6816719318409899848ull);
    vlSelf->top__DOT__u_cpu__DOT__fetch_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1279166563776813514ull);
    vlSelf->top__DOT__u_cpu__DOT__fetch_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11679940868392193645ull);
    vlSelf->top__DOT__u_cpu__DOT__data_fetch_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5298173521683232047ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_stage_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8902802427972294959ull);
    vlSelf->top__DOT__u_cpu__DOT__lsu_pre_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 753705374506364162ull);
    vlSelf->top__DOT__u_cpu__DOT__lsu_data_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16454257257769358616ull);
    vlSelf->top__DOT__u_cpu__DOT__wb_data_wait = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9019010367444750032ull);
    vlSelf->top__DOT__u_cpu__DOT__stop_in_flight = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14264972082003674030ull);
    vlSelf->top__DOT__u_cpu__DOT__freeze = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8267843214054549182ull);
    vlSelf->top__DOT__u_cpu__DOT__id_kill = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9548787355365433245ull);
    vlSelf->top__DOT__u_cpu__DOT__fwd_jalr_rs1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5432546865846782348ull);
    vlSelf->top__DOT__u_cpu__DOT__pc_target = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13233041282662907912ull);
    vlSelf->top__DOT__u_cpu__DOT__wb_rd_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18087017386623093102ull);
    vlSelf->top__DOT__u_cpu__DOT__load_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16701816040768789722ull);
    vlSelf->top__DOT__u_cpu__DOT__wb_cap_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14225525712208152980ull);
    vlSelf->top__DOT__u_cpu__DOT__wb_cap_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5278720090514152025ull);
    vlSelf->top__DOT__u_cpu__DOT__wb_cap_resp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16694944601653424089ull);
    vlSelf->top__DOT__u_cpu__DOT__wb_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6787373264399551431ull);
    vlSelf->top__DOT__u_cpu__DOT__wb_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2641711933837524541ull);
    vlSelf->top__DOT__u_cpu__DOT__data_araddr_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17780791505015481803ull);
    vlSelf->top__DOT__u_cpu__DOT__data_arvalid_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11536806104229397143ull);
    vlSelf->top__DOT__u_cpu__DOT__data_arready_in = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11659525072419500773ull);
    vlSelf->top__DOT__u_cpu__DOT__data_rdata_in = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9477207808105841415ull);
    vlSelf->top__DOT__u_cpu__DOT__data_rvalid_in = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16703263486157413371ull);
    vlSelf->top__DOT__u_cpu__DOT__data_rready_out = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__data_rresp_in = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12464040752079141001ull);
    vlSelf->top__DOT__u_cpu__DOT__data_awaddr_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14401978863874801377ull);
    vlSelf->top__DOT__u_cpu__DOT__data_awvalid_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13084699965488757729ull);
    vlSelf->top__DOT__u_cpu__DOT__data_awready_in = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4827733501114548300ull);
    vlSelf->top__DOT__u_cpu__DOT__data_wdata_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2043772906881729382ull);
    vlSelf->top__DOT__u_cpu__DOT__data_wstrb_out = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 9720341168968518266ull);
    vlSelf->top__DOT__u_cpu__DOT__data_wvalid_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2561499522641578426ull);
    vlSelf->top__DOT__u_cpu__DOT__data_wready_in = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8113669074242058306ull);
    vlSelf->top__DOT__u_cpu__DOT__data_bvalid_in = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10704015111838854068ull);
    vlSelf->top__DOT__u_cpu__DOT__data_bready_out = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__data_bresp_in = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14296578432124840728ull);
    vlSelf->top__DOT__u_cpu__DOT__mmio_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14934276257990206666ull);
    vlSelf->top__DOT__u_cpu__DOT__mmio_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8583709222423735875ull);
    vlSelf->top__DOT__u_cpu__DOT__mmio_arready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__mmio_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15501531976049335782ull);
    vlSelf->top__DOT__u_cpu__DOT__mmio_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10614779938302573770ull);
    vlSelf->top__DOT__u_cpu__DOT__mmio_rready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__mmio_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2284976048851905133ull);
    vlSelf->top__DOT__u_cpu__DOT__mmio_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17933196116185744982ull);
    vlSelf->top__DOT__u_cpu__DOT__mmio_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13698393788169917800ull);
    vlSelf->top__DOT__u_cpu__DOT__mmio_awready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__mmio_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2442118779408987966ull);
    vlSelf->top__DOT__u_cpu__DOT__mmio_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 8051199011406522326ull);
    vlSelf->top__DOT__u_cpu__DOT__mmio_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8254468801382952144ull);
    vlSelf->top__DOT__u_cpu__DOT__mmio_wready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__mmio_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4411498746281009504ull);
    vlSelf->top__DOT__u_cpu__DOT__mmio_bready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__mmio_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9361785547323096301ull);
    vlSelf->top__DOT__u_cpu__DOT__stop_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14983109203291172548ull);
    vlSelf->top__DOT__u_cpu__DOT__instr_fault_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11156612380566043682ull);
    vlSelf->top__DOT__u_cpu__DOT__data_fault_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14908851895271691864ull);
    vlSelf->top__DOT__u_cpu__DOT__illegal_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14112804012245885379ull);
    vlSelf->top__DOT__u_cpu__DOT__if_fault_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17154426814918887826ull);
    vlSelf->top__DOT__u_cpu__DOT__instr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5488419772755685208ull);
    vlSelf->top__DOT__u_cpu__DOT__if_id_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5207318822568469084ull);
    vlSelf->top__DOT__u_cpu__DOT__reg_w_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10223263319588754604ull);
    vlSelf->top__DOT__u_cpu__DOT__rdst_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 5363107868656384082ull);
    vlSelf->top__DOT__u_cpu__DOT__rdst_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17065176272422443287ull);
    vlSelf->top__DOT__u_cpu__DOT__rs1_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 185376667495125910ull);
    vlSelf->top__DOT__u_cpu__DOT__rs2_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 8129940687886298745ull);
    vlSelf->top__DOT__u_cpu__DOT__rs1_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14929891142440176797ull);
    vlSelf->top__DOT__u_cpu__DOT__rs2_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1908695070480338884ull);
    vlSelf->top__DOT__u_cpu__DOT__pc_in1_sel = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4031094445959648418ull);
    vlSelf->top__DOT__u_cpu__DOT__if_id_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1709853132189231410ull);
    vlSelf->top__DOT__u_cpu__DOT__if_id_instr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18411245862516480260ull);
    vlSelf->top__DOT__u_cpu__DOT__if_id_opcode = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 4754013638719211555ull);
    vlSelf->top__DOT__u_cpu__DOT__if_id_rs1_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 617149556172435529ull);
    vlSelf->top__DOT__u_cpu__DOT__if_id_rs2_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 12227066991358328730ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5494201134156193131ull);
    vlSelf->top__DOT__u_cpu__DOT__imm_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10333335306906697625ull);
    vlSelf->top__DOT__u_cpu__DOT__illegal_instr_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4368574086141845601ull);
    vlSelf->top__DOT__u_cpu__DOT__d_is_branch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15609380771558330870ull);
    vlSelf->top__DOT__u_cpu__DOT__d_is_jal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10496328843272864426ull);
    vlSelf->top__DOT__u_cpu__DOT__d_is_jalr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 67005864643446593ull);
    vlSelf->top__DOT__u_cpu__DOT__d_stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13525898123576513929ull);
    vlSelf->top__DOT__u_cpu__DOT__imm_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3219742408583586275ull);
    vlSelf->top__DOT__u_cpu__DOT__imm_type = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 17771432074263927410ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13811012327199315214ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_rs1_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 5510206514123928825ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_rs2_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 11391892174079173309ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_rd_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 1284006743651788119ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_opcode = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 7288527285578457779ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_rs1_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7200547187505777306ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_rs2_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 685965317621172872ull);
    vlSelf->top__DOT__u_cpu__DOT__fwd_store_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 317700501002020394ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_imm_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6943186970993868990ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_alu_in1_ropc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2604175333716274025ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_alu_in2_roi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17683051422305902623ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_alu_op = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 5414918197405413712ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_alu_bypass = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12459983598956300446ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12647249009249248702ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16655142461626830243ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 7048750492435766523ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_pc_in1_sel = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14392788305842454303ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_is_branch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7944670826139486196ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_is_jal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3809299081348756410ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_is_jalr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2795056145993351996ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16251735131458765682ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_imm_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9222393995847866136ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_mem_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18405855007728579971ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6628400893274382243ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_illegal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10121776630907968425ull);
    vlSelf->top__DOT__u_cpu__DOT__id_ex_if_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 607238315433891626ull);
    vlSelf->top__DOT__u_cpu__DOT__alu_op = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 12758967225510099876ull);
    vlSelf->top__DOT__u_cpu__DOT__alu_in1_sel = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15870090315687284172ull);
    vlSelf->top__DOT__u_cpu__DOT__alu_in2_sel = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15916634701875632495ull);
    vlSelf->top__DOT__u_cpu__DOT__alu_bypass = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9049029015462005213ull);
    vlSelf->top__DOT__u_cpu__DOT__alu_zero = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5196151352496716699ull);
    vlSelf->top__DOT__u_cpu__DOT__alu_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3482279785517445549ull);
    vlSelf->top__DOT__u_cpu__DOT__branch_taken = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15477828405886214499ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_rs2_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2732589158360952590ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_rd_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 13775499201085202000ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3986449201690900979ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6891396199096775498ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16433501515530112205ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 7358728625184629902ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11669702140753607184ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_mem_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13334913426715958517ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_mem_stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9505698503944766965ull);
    vlSelf->top__DOT__u_cpu__DOT__funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 12989651974382408143ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11728375109217349596ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8396010597759043545ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_wb_rd_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 9841072902432727225ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_wb_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7909046141216083319ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_wb_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5380692490876238206ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_wb_mem_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10993301162385855416ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_wb_funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 16246485897158250710ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_wb_addr_lo = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 540307271919636495ull);
    vlSelf->top__DOT__u_cpu__DOT__mem_wb_stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7768551789704405039ull);
    vlSelf->top__DOT__u_cpu__DOT__fwd_alu_in1_ex_mem = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10733249911357145927ull);
    vlSelf->top__DOT__u_cpu__DOT__fwd_alu_in1_mem_wb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17135258373737799870ull);
    vlSelf->top__DOT__u_cpu__DOT__fwd_alu_in2_ex_mem = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1072029671802425005ull);
    vlSelf->top__DOT__u_cpu__DOT__fwd_alu_in2_mem_wb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 946633850927973668ull);
    vlSelf->top__DOT__u_cpu__DOT__uart_rx_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 236328670290886422ull);
    vlSelf->top__DOT__u_cpu__DOT__uart_rx_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15455322392752234046ull);
    vlSelf->top__DOT__u_cpu__DOT__uart_tx_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3504418244210139330ull);
    vlSelf->top__DOT__u_cpu__DOT__uart_tx_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16057404499623725037ull);
    vlSelf->top__DOT__u_cpu__DOT__uart_tx_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9125081331044349150ull);
    vlSelf->top__DOT__u_cpu__DOT__uart_rx_ack = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 183998068053005876ull);
    vlSelf->top__DOT__u_cpu__DOT__meta_clear = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8372965580738632536ull);
    vlSelf->top__DOT__u_cpu__DOT__meta_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6067929932348624926ull);
    vlSelf->top__DOT__u_cpu__DOT__meta_instr_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4717391587955926335ull);
    vlSelf->top__DOT__u_cpu__DOT__meta_stall_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1130141206269518050ull);
    vlSelf->top__DOT__u_cpu__DOT__meta_l_use_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11974591466552408835ull);
    vlSelf->top__DOT__u_cpu__DOT__meta_br_flush_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11027260000732731440ull);
    vlSelf->top__DOT__u_cpu__DOT__ex_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15648314063978679340ull);
    vlSelf->top__DOT__u_cpu__DOT__pc_plus4 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14684096156417736432ull);
    vlSelf->top__DOT__u_cpu__DOT__u_reg_file__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18027378294612932837ull);
    vlSelf->top__DOT__u_cpu__DOT__u_reg_file__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3002108317674633884ull);
    vlSelf->top__DOT__u_cpu__DOT__u_reg_file__DOT__w_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11125760556759432438ull);
    vlSelf->top__DOT__u_cpu__DOT__u_reg_file__DOT__w_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 16697683123321591561ull);
    vlSelf->top__DOT__u_cpu__DOT__u_reg_file__DOT__w_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7145056019833606318ull);
    vlSelf->top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr1 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 3980630415661116629ull);
    vlSelf->top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr2 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 18391865539816622524ull);
    vlSelf->top__DOT__u_cpu__DOT__u_reg_file__DOT__r_data1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17410595935663273407ull);
    vlSelf->top__DOT__u_cpu__DOT__u_reg_file__DOT__r_data2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18321702580344504813ull);
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->top__DOT__u_cpu__DOT__u_reg_file__DOT__registers[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1375488913775379883ull);
    }
    vlSelf->top__DOT__u_cpu__DOT__u_reg_file__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3297519375640141125ull);
    vlSelf->top__DOT__u_cpu__DOT__u_pc__DOT__pcinc_in1_pcor = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16851312681292167869ull);
    vlSelf->top__DOT__u_cpu__DOT__u_pc__DOT__rs1_in = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6719742064158421509ull);
    vlSelf->top__DOT__u_cpu__DOT__u_pc__DOT__pc_in = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12681547185263708947ull);
    vlSelf->top__DOT__u_cpu__DOT__u_pc__DOT__imm_in = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11631770352401890670ull);
    vlSelf->top__DOT__u_cpu__DOT__u_pc__DOT__pc_target = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14697162960234971018ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7832311244746792999ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13166187286818707543ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2105337662738273503ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__redirect = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15266068184550593897ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12786901197806317678ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__if_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6229959752458379057ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__if_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11591694479231151411ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__if_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1864647047926649376ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__if_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4200460408903579898ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__if_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15544209708562797195ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__if_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 4311559697125202432ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__if_rready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__pc_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9693175954539707274ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__instr_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1468933106870571601ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__mem_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17686624133726886141ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__fetch_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17695519168357337970ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__req_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9974759072789248373ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__pend_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17964651193708151225ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__pend_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5920843441111154898ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12132048285286545827ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__hold_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 247824624071590188ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__hold_stale = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2025633427288600901ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17761270106818833269ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__af_mis[__Vi0] = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1350784183924851011ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale[__Vi0] = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7525383331321622147ull);
    }
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__af_head = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14712880483425361171ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__af_tail = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12081253003414243109ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__inflight = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2251817517115647761ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12528040759692102766ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__cb_pc[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11219522585569420309ull);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__cb_fault[__Vi0] = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6169381306577961483ull);
    }
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1518389343161025119ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__cb_tail = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10891146373598406057ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__cap_cnt = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 8402516590882607914ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4124524533131806420ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__space = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13111951522156011543ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_hold = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5193414861982665471ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_redirect = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15247916388693323959ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_pend = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5346656315789073032ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__push_stale = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 910017365737994955ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__ar_hs = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15434241462374664923ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__r_hs = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17599931193172153220ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__r_good = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8267251101353724751ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_cb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 897292604037915768ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_r = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13070515744979871971ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__cb_push = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12161821209388551437ull);
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__unnamedblk2__DOT__i = 0;
    vlSelf->top__DOT__u_cpu__DOT__u_fetch__DOT__unnamedblk1__DOT__i = 0;
    vlSelf->top__DOT__u_cpu__DOT__u_if_id__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1145499779361180189ull);
    vlSelf->top__DOT__u_cpu__DOT__u_if_id__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12847311957314696313ull);
    vlSelf->top__DOT__u_cpu__DOT__u_if_id__DOT__stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15566924946628490291ull);
    vlSelf->top__DOT__u_cpu__DOT__u_if_id__DOT__clear = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13470232160199828080ull);
    vlSelf->top__DOT__u_cpu__DOT__u_if_id__DOT__i_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10765200432517393084ull);
    vlSelf->top__DOT__u_cpu__DOT__u_if_id__DOT__i_instr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1234545193755713786ull);
    vlSelf->top__DOT__u_cpu__DOT__u_if_id__DOT__i_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3850679653673074379ull);
    vlSelf->top__DOT__u_cpu__DOT__u_if_id__DOT__o_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17559934121176884045ull);
    vlSelf->top__DOT__u_cpu__DOT__u_if_id__DOT__o_instr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12951357879896183226ull);
    vlSelf->top__DOT__u_cpu__DOT__u_if_id__DOT__o_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10608612721074035515ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__instr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7712587552028302743ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__rs1_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 4945051592285926543ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__rs2_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 8837135569965211088ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__rd_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 11563687111316596053ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__is_branch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10379186895055268256ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__is_jal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4909949182507575189ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__is_jalr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11768527583289785051ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__alu_op = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 614433129012183184ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in1_ropc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8828509067018798463ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in2_roi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16665180949367735310ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__alu_bypass = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10464277090208206809ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8866491598192990622ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11739623892037405603ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1998229035342382277ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__mem_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12454217358620454161ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__imm_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11423781144757114500ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__imm_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5343541932634433718ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__pcinc_in1_pcor = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1420556243783142219ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 17467309864389117867ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9494467740727014300ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11690810960829512030ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__opcode = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 14033807547098626134ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 4286665488713578528ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12257389963667019108ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_type = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 7085091365075589682ull);
    vlSelf->top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5752634554344949698ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4202962358208806530ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13875397835701865626ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2281051171144713645ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__clear = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4400261062257027211ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_opcode = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 17442344079847020893ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10792140619631381405ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs1_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 9339156862480739075ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs2_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 8298472585690227042ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rd_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 14448320289122401521ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs1_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8346839603311729519ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs2_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17480617795270747041ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_imm_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13681968149835850959ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_in1_ropc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7303136654383254051ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_in2_roi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14304510051488234324ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_op = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 2565827696800735932ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_bypass = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1495857250318665362ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5879310793040865548ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17139715878403979798ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 3688173474208473984ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_pc_in1_sel = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15086693220247663742ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_branch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15134211230587499217ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_jal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5770438735666731193ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_jalr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2830090932688011736ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8724877826504831843ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_imm_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8069195475784123029ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_mem_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18167896706276376191ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17316694341476350469ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_illegal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17570775234308682190ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__i_if_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11442484667099014091ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_opcode = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 11129129801425507308ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15271286360628006098ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs1_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 283017112868812989ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs2_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 3574474372321117563ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rd_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 12984176471721188750ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs1_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3826439623865758109ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs2_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6499344847661296931ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_imm_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4407752167856928844ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_in1_ropc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16885227484426425208ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_in2_roi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10734705282134552559ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_op = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10808664846348322835ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_bypass = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2972231075069595891ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3523503022685008631ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2606612806465431215ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 16993841792319285157ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_pc_in1_sel = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9885189521357891889ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_branch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16274182555381420388ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_jal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 198351487419454170ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_jalr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17388554476111584421ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1966324880233432582ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_imm_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9113504122671084017ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17137999036766863655ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17588967732318939571ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_illegal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11849800933921088822ull);
    vlSelf->top__DOT__u_cpu__DOT__u_id_ex__DOT__o_if_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14763171621308087149ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__alu_op = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 3698921485622522461ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__alu_bypass = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14399363269344454242ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__imm_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3197456585352560311ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__r_data1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1570526093805463890ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__r_data2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1409329273906830918ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13756167786618630183ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__use_pc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1078871121476092030ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__imm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11735666898553062257ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__use_imm = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8249888503038968983ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in1_ex_mem = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18390966804841982401ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in2_ex_mem = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3723901592368306464ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in1_mem_wb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18018686800036732070ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in2_mem_wb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5152474141055742037ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__ex_mem_rd_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4840226558596673081ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__mem_wb_rd_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9489974849175278294ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__alu_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17273129919794626247ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__out_zero = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12649638899292985373ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__data1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14033296306717898790ull);
    vlSelf->top__DOT__u_cpu__DOT__u_alu__DOT__data2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12677144840115112110ull);
    vlSelf->top__DOT__u_cpu__DOT__u_branch_unit__DOT__is_branch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10719116638813294877ull);
    vlSelf->top__DOT__u_cpu__DOT__u_branch_unit__DOT__is_jal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7703027015238868792ull);
    vlSelf->top__DOT__u_cpu__DOT__u_branch_unit__DOT__is_jalr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5856648441951243275ull);
    vlSelf->top__DOT__u_cpu__DOT__u_branch_unit__DOT__id_ex_funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 15902523838472667598ull);
    vlSelf->top__DOT__u_cpu__DOT__u_branch_unit__DOT__alu_zero = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17790343773329336385ull);
    vlSelf->top__DOT__u_cpu__DOT__u_branch_unit__DOT__branch_taken = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5212736706948631459ull);
    vlSelf->top__DOT__u_cpu__DOT__u_branch_unit__DOT__branch_passed = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5030301645421667381ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7888388374344854589ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16537054146316863610ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7818678224456211535ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__clear = 0U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_rs2_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9336971152071132446ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_rd_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 2739287339523139962ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14669067594467879768ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6351371920640940057ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2985048040457793449ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 9412367441948507410ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 203494942249891652ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_mem_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7813078134312673428ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_is_stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8773021055720258409ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_rs2_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5869243600437026815ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_rd_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 753116648867410408ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10292274103674830670ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9210779398141457192ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13084720815004650655ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11185812184069419793ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6260754685393536649ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_mem_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10892158202561411278ull);
    vlSelf->top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_is_stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14237039978273251702ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12948491782431935492ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7737778042350625772ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 16127016370453433794ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9386777117828265671ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9942609637845796759ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18402796318964868897ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__rs2_in = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 898974249383291671ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__mem_advance = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6333542797771174673ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__freeze = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3413496217219324620ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15196899224753704798ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3094864953172968789ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4334111514242817397ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6895260708398125119ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 1612395870220791190ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_rready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16312828179941066062ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17668522530902170655ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3434976304496050398ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10653699116736533678ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 17386278157895838263ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5978337290473319304ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13077524986640830205ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7449133412819362840ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 18078101860842808607ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_bready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__mem_stage_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12645048360467844616ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__pre_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 712983990338250849ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__data_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10914789960222458720ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__is_access = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8251057259001901596ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__region = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13221668627467461450ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__misaligned = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7496811284551350441ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__load_req = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10529205438915875515ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__store_req = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6956787234771186201ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__is_mmio = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11511018821833921006ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__ar_sent = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8728020809254856954ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__ar_hs = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9707250141179007159ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__ar_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4791578360403694950ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__aw_sent = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3561489701458468761ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__w_sent = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3574586387038160575ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8643258934038306014ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__aw_hs = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15507157878097450813ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__w_hs = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18246875938582864897ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_now = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5611111592870047137ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__wr_accepted = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4468083950903741203ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__b_hs = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1531781241568017555ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__b_out = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 8816762846390476623ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__b_out_next = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 7521321048997107195ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__store_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15598278837751135411ull);
    vlSelf->top__DOT__u_cpu__DOT__u_lsu__DOT__size_mask = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10118736067687361922ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1182136588613398971ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15442600345307835578ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9691669793027521906ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11253965452203855736ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10511680245145230872ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16939483102505697541ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13736570541625598637ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 7930063869533082606ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13975892127264564110ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3405986550025831847ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7589285107399717653ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12748226772699535561ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 13336904087747624533ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12809663022398723064ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9636684012034551940ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4684609361905101431ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_bready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 633022819065690918ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 445000447987956961ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12809135966724674166ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_arready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16990613400955280088ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2639335925180096371ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12046824086823197356ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13345203165908418433ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18313735648179788285ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_awready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8057219872816307564ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 13749352010295514720ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12236531251622778304ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16360404363139941364ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_bready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10104336326717941270ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5824186886325952910ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15999343494981551248ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 353844953523587410ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2854542208223511832ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13568684094667607346ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9520105093627114644ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12514971899289796455ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11555698411858601501ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6178354332823931885ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11891996475984410861ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 8847179523906632612ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10613259786718129956ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5936885803625086304ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5856205448371081633ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_bready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14568185799934946163ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_mmio = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1726042388071686604ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5213737990913813646ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_sel_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3986884436818198197ull);
    vlSelf->top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_sel_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2270458079173769120ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8385758919868018485ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14574089800891878430ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4444766514901487337ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13087975194887900457ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_arready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10159343368972228306ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7391382682919090367ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10734932608173236142ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12507004624267816115ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14850502620024377476ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_awready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13945614777623529120ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 62308185427333644ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12849086291459761714ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1364578693212835543ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_bready = 1U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 15627126866506802398ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17267691848944482590ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15356853333470203746ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7196484373421059390ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16887952324479239752ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14174967400616704653ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_ack = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3851714163575522579ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12488748786413831571ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_clear = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1144347962504303804ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_instr_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11475705187978647459ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_stall_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3084433088616267828ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_l_use_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17462417015042043346ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_br_flush_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6570157298738049858ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12884773629555534833ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__wr_word = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14092291242483607759ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_uart_status = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5511136183284684421ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_uart_tx_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5273281683126468450ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_meta_control = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5304502809947765728ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1162164458973071577ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_resp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 7156485998048856680ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14669179428232139349ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10142254623780817774ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18109970598488093329ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__clear = 0U;
    ;
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_rd_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 13923154941835402916ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14736627032190275575ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8451880071755809701ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_mem_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1313149726775100537ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10525197786771706860ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_addr_lo = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12351117036365495692ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_is_stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13693850607897057769ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_rd_addr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 7384382967528729072ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7100372228757356830ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8018061022180096745ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_mem_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18191514426540426859ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 4573584107824225348ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_addr_lo = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 8519963444057757316ull);
    vlSelf->top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_is_stop = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4348901849203510213ull);
    vlSelf->top__DOT__u_cpu__DOT__u_write_back__DOT__funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 13785737474654964202ull);
    vlSelf->top__DOT__u_cpu__DOT__u_write_back__DOT__addr_lo = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10777022504544325421ull);
    vlSelf->top__DOT__u_cpu__DOT__u_write_back__DOT__mem_to_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16894684121405876318ull);
    vlSelf->top__DOT__u_cpu__DOT__u_write_back__DOT__result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17804413335232687464ull);
    vlSelf->top__DOT__u_cpu__DOT__u_write_back__DOT__data_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15000843242478815271ull);
    vlSelf->top__DOT__u_cpu__DOT__u_write_back__DOT__data_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16524627041891313141ull);
    vlSelf->top__DOT__u_cpu__DOT__u_write_back__DOT__rd_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12218077640704718416ull);
    vlSelf->top__DOT__u_cpu__DOT__u_write_back__DOT__load_fault = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7413105722613849470ull);
    vlSelf->top__DOT__u_cpu__DOT__u_write_back__DOT__shifted = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17041340336956245205ull);
    vlSelf->top__DOT__u_cpu__DOT__u_write_back__DOT__load_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2488811366009352609ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_opcode = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 11655397744511882528ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_opcode = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 14248825787575374136ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs1 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 7343419553731480626ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs2 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 15266395898104832517ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs1 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 13915792495109900019ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs2 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 9625791418816634218ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 15283912167248669870ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__ex_mem_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 7766146968050012492ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 8725704424712435505ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 353918750773127495ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3010665898506165864ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__branch_taken = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2196127443208838396ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__data_fetch_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14788181270823633053ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__wb_data_wait = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9621012741098469753ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__freeze = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1655632407760590035ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__stop_in_flight = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4081614502932356566ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__ex_mem_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13354339180414584040ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9098000789250471735ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__pc_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17005728253754950457ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 271360114694653116ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17921916155907571393ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__ex_mem_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14946796914762576329ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5960587620736316573ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_clear = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10053779630800038399ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_clear = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8097055758901574506ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in1_ex_mem = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 432501992718985906ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in2_ex_mem = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15328666864928392262ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in1_mem_wb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14941616020324730431ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in2_mem_wb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14742287847833388096ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_branch_flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11893052528100824152ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_is_stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13373550337775275739ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_is_l_use = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13739414742229114838ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_is_instr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14882402438492977784ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_id_ex_rd_if_id_rs1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4358048641331923918ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_id_ex_rd_if_id_rs2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16468605150277882877ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_ex_mem_rd_id_ex_rs1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17945689251980107448ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_ex_mem_rd_id_ex_rs2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7454374197893395543ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_mem_wb_rd_id_ex_rs1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8335614634655751742ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_mem_wb_rd_id_ex_rs2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14255689839579463624ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs1_not_x0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12291815866373798744ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs2_not_x0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14398470115389088241ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rd_not_x0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10596891841374827162ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs1_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9585628088695300569ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs2_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8193924015858267261ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs1_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12794382123407571615ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs2_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5874509529767932806ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 12498128593443545780ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 12475797449245826129ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs1 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 14294695116119390523ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs2 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 18380775045989207130ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 12252012372871425275ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 203071297349927176ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 14710111127900449997ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__ex_mem_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 5639169893341709913ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__mem_wb_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 12209811135102713665ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_id_ex_rd_if_id_rs1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9183542106800875607ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_id_ex_rd_if_id_rs2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2936652391383093400ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_ex_mem_rd_id_ex_rs1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 323085278050603111ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_ex_mem_rd_id_ex_rs2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13478812335069255927ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_mem_wb_rd_id_ex_rs1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 867649300793284259ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_mem_wb_rd_id_ex_rs2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 663792302502542603ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1_not_x0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2853448005579748525ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2_not_x0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5007100989411250314ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rd_not_x0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8841247386690299817ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs1_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5481380772974984729ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs2_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14400067609347505248ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2079739605775928996ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5916902631770127792ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__dep_id_ex_rd_if_id_rs1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10106776590283451630ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__dep_id_ex_rd_if_id_rs2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2951203302802807585ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_rd_not_x0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11444969792256240904ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 667540088932704030ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14586454395160246025ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__branch_taken = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18113163809148537320ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__data_fetch_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12017403493371809631ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__wb_data_wait = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13254729612360855340ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__freeze = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2360163778870499206ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__stop_in_flight = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15692258328951514670ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_rs1_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2094445007335160326ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_rs2_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6436171069787114320ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_clear = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12182210021063229083ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_clear = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 896872377697652957ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__pc_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4158329137411868534ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8083264851556106838ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11842181017050262170ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__ex_mem_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4270299310376365092ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__mem_wb_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1994438081733069221ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_branch_flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4030447046203049196ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10824084004727825759ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_l_use = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15988927625831317673ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_instr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9024061159822472079ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__is_l_use_no_gap = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4307761914958492497ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_id_ex_rd_if_id_rs1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6512102911314331458ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_id_ex_rd_if_id_rs2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16780917648656867889ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_ex_mem_rd_id_ex_rs1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17075040846329317339ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_ex_mem_rd_id_ex_rs2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11181957706558479923ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_mem_wb_rd_id_ex_rs1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2612679365697168035ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_mem_wb_rd_id_ex_rs2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14065824132206354955ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs1_not_x0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 690016653129958722ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs2_not_x0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7554104431261706134ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs1_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16282590966670206216ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs2_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12039115999465917594ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__ex_mem_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10166740856441771536ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__mem_wb_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11442973484878402872ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in1_ex_mem = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2981388218600941580ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in2_ex_mem = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15440727931919374547ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in1_mem_wb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12833922050376096531ull);
    vlSelf->top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in2_mem_wb = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18442774245700921577ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 912823704964583931ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5556835080538839357ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__is_instr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10768990842193473047ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8770551328155900558ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__clear = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6039680242967262555ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__is_stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4857920598539359320ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__is_l_use = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5215389153777482933ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__is_br_flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 820656720393044536ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__meta_instr_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9084906644972353960ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__meta_stall_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12307462395252423692ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__meta_l_use_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2468398084888740226ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__meta_br_flush_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12546549840680518013ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__instr_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15613914127732262431ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__stall_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11702730034716601678ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 385372348010913071ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12465170206570378654ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__post_flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17606337142754423697ull);
    vlSelf->top__DOT__u_cpu__DOT__u_meta__DOT__boot_mask = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9282785484628760661ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12224280729881158266ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4510447572018550276ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__tx_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 12152597433388317739ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__tx_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4818342332185469195ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__tx = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14319926349211274516ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__tx_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12331538592966652725ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__rx = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17029404336207428360ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__rx_ack = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18037276058494489077ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__rx_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8218613692307612004ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__rx_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8237237501743756986ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__baud_tick = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7945419344816783491ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3428648623789851457ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14182898808704165710ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__tick = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4648708756349761468ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__counter = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 2835788487314668094ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14557378142358012247ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12821487577799100424ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__baud_tick = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12030469669097954363ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7645260634200897064ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1366688795846715356ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6067448268784034389ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx_busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12320547757889225146ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11746956410530002952ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_cntr = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 17572450131146350811ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_reg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 13148543671612513037ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__start_pending = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7184307467909918821ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tick_cntr = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 11851978793981453463ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__bit_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3040908119648994564ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9813285147877400329ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2655017050229763002ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__baud_tick = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7667987229750022713ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6593058326580702250ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_ack = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4217439574401249868ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 13198869938745160291ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16929887877890105782ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_meta = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9140465133638197477ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_sync = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13067130842168283833ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2592516311158284691ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 7439003926959544005ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_reg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5032701374223230750ull);
    vlSelf->top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_cntr = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 7683527147408055680ull);
    vlSelf->top__DOT__u_mem__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7813591398241433944ull);
    vlSelf->top__DOT__u_mem__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10616523132091601486ull);
    vlSelf->top__DOT__u_mem__DOT__if_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12764081798586627913ull);
    vlSelf->top__DOT__u_mem__DOT__if_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11223306526007039169ull);
    vlSelf->top__DOT__u_mem__DOT__if_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11165073220053791255ull);
    vlSelf->top__DOT__u_mem__DOT__if_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15183912582078899624ull);
    vlSelf->top__DOT__u_mem__DOT__if_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7224168922686394652ull);
    vlSelf->top__DOT__u_mem__DOT__if_rready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__if_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13107644894169154657ull);
    vlSelf->top__DOT__u_mem__DOT__data_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13839942053664445784ull);
    vlSelf->top__DOT__u_mem__DOT__data_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6064327861983788053ull);
    vlSelf->top__DOT__u_mem__DOT__data_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11664243764591334860ull);
    vlSelf->top__DOT__u_mem__DOT__data_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9394684982107123292ull);
    vlSelf->top__DOT__u_mem__DOT__data_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13378881443075525761ull);
    vlSelf->top__DOT__u_mem__DOT__data_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13341778881311668114ull);
    vlSelf->top__DOT__u_mem__DOT__data_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14364373352015202192ull);
    vlSelf->top__DOT__u_mem__DOT__data_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17624459881305768310ull);
    vlSelf->top__DOT__u_mem__DOT__data_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 831489624268422636ull);
    vlSelf->top__DOT__u_mem__DOT__data_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3245581765786335239ull);
    vlSelf->top__DOT__u_mem__DOT__data_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9523867621854041820ull);
    vlSelf->top__DOT__u_mem__DOT__data_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 1865847514083879173ull);
    vlSelf->top__DOT__u_mem__DOT__data_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8905391402929494911ull);
    vlSelf->top__DOT__u_mem__DOT__data_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5885434695631131931ull);
    vlSelf->top__DOT__u_mem__DOT__data_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12222794981000324150ull);
    vlSelf->top__DOT__u_mem__DOT__data_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12879846196028598645ull);
    vlSelf->top__DOT__u_mem__DOT__data_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2035007289977241792ull);
    vlSelf->top__DOT__u_mem__DOT__rom_if_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18149564941575840392ull);
    vlSelf->top__DOT__u_mem__DOT__rom_if_arready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__rom_if_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12556761840380491412ull);
    vlSelf->top__DOT__u_mem__DOT__rom_if_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 721836749691520463ull);
    vlSelf->top__DOT__u_mem__DOT__rom_if_rresp = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__ram_if_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4906549793032402907ull);
    vlSelf->top__DOT__u_mem__DOT__ram_if_arready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__ram_if_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7308053901280963700ull);
    vlSelf->top__DOT__u_mem__DOT__ram_if_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1163698626663739345ull);
    vlSelf->top__DOT__u_mem__DOT__ram_if_rresp = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__dif_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8140133356972765842ull);
    vlSelf->top__DOT__u_mem__DOT__dif_arready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__dif_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6509025277948747295ull);
    vlSelf->top__DOT__u_mem__DOT__dif_rdata = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__dif_rresp = 3U;
    ;
    vlSelf->top__DOT__u_mem__DOT__dif_awready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__dif_wready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__dif_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15780464568915586077ull);
    vlSelf->top__DOT__u_mem__DOT__dif_bresp = 3U;
    ;
    vlSelf->top__DOT__u_mem__DOT__rom_d_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1684621759965454270ull);
    vlSelf->top__DOT__u_mem__DOT__rom_d_arready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__rom_d_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10531408248449975852ull);
    vlSelf->top__DOT__u_mem__DOT__rom_d_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9736064865879391513ull);
    vlSelf->top__DOT__u_mem__DOT__rom_d_rresp = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__ram_d_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11847392282570519735ull);
    vlSelf->top__DOT__u_mem__DOT__ram_d_arready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__ram_d_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 852920222985685479ull);
    vlSelf->top__DOT__u_mem__DOT__ram_d_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9267298028319384295ull);
    vlSelf->top__DOT__u_mem__DOT__ram_d_rresp = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__ddt_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10247178037482290926ull);
    vlSelf->top__DOT__u_mem__DOT__ddt_arready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__ddt_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 698173134453138754ull);
    vlSelf->top__DOT__u_mem__DOT__ddt_rdata = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__ddt_rresp = 3U;
    ;
    vlSelf->top__DOT__u_mem__DOT__rom_d_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18293282332334106283ull);
    vlSelf->top__DOT__u_mem__DOT__rom_d_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17523713315219949825ull);
    vlSelf->top__DOT__u_mem__DOT__rom_d_awready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__rom_d_wready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__rom_d_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10353649641962131380ull);
    vlSelf->top__DOT__u_mem__DOT__rom_d_bresp = 2U;
    ;
    vlSelf->top__DOT__u_mem__DOT__ram_d_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15331818122284433303ull);
    vlSelf->top__DOT__u_mem__DOT__ram_d_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5012761397105555442ull);
    vlSelf->top__DOT__u_mem__DOT__ram_d_awready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__ram_d_wready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__ram_d_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 330106570467864617ull);
    vlSelf->top__DOT__u_mem__DOT__ram_d_bresp = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__ddt_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14714871162400454567ull);
    vlSelf->top__DOT__u_mem__DOT__ddt_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6263400245180778721ull);
    vlSelf->top__DOT__u_mem__DOT__ddt_awready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__ddt_wready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__ddt_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3651639932263852293ull);
    vlSelf->top__DOT__u_mem__DOT__ddt_bresp = 3U;
    ;
    vlSelf->top__DOT__u_mem__DOT__if_sel = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 15861388572980008661ull);
    vlSelf->top__DOT__u_mem__DOT__if_sel_q = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3422169338668140665ull);
    vlSelf->top__DOT__u_mem__DOT__rd_sel = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9740762103178614493ull);
    vlSelf->top__DOT__u_mem__DOT__rd_sel_q = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 95628579846195457ull);
    vlSelf->top__DOT__u_mem__DOT__wr_sel = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 17311626505542346491ull);
    vlSelf->top__DOT__u_mem__DOT__wr_sel_q = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 228522210018461829ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9710773415425657888ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4593681748917770090ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__if_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17229475484290017029ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__if_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5120431099905049905ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__if_arready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__if_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17027110547419092199ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__if_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17415386036177442085ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__if_rready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__if_rresp = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4746309007744003341ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 769116463899141351ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_arready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10183592190618627522ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12589611875999254357ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7745653418920907240ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_rresp = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7466656073249340095ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4873099941422878104ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_awready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10753830681568413850ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 1017587344515171617ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18071573834056495284ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_wready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16762184752199697680ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 478231338554151421ull);
    vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__data_bresp = 2U;
    ;
    for (int __Vi0 = 0; __Vi0 < 2048; ++__Vi0) {
        vlSelf->top__DOT__u_mem__DOT__u_boot_rom__DOT__container[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15082076374560562337ull);
    }
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4759357883937669236ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 751286644345252753ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__if_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10469821126502081835ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__if_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14714337894498551882ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__if_arready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__if_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10237948529945035109ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__if_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3600871006538062720ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__if_rready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__if_rresp = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2754587589111172482ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9761043266785366837ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_arready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13936469728074108037ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4881196521941483658ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15569537489548792953ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_rresp = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18003464917894001767ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12414583143222443155ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_awready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6901551428737655401ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 8064330269382782817ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15344949927498652461ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_wready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10353521829979863420ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12241954392558659970ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__data_bresp = 0U;
    ;
    for (int __Vi0 = 0; __Vi0 < 32768; ++__Vi0) {
        vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__container[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4826038751416673602ull);
    }
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__b_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10834839271648747490ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__b_idx = VL_SCOPED_RAND_RESET_I(15, __VscopeHash, 5200761344927711549ull);
    vlSelf->top__DOT__u_mem__DOT__u_ram__DOT__unnamedblk1__DOT__i = 0;
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6130123551650035553ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3579981833181966264ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16369009689450119190ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3995122723992896136ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__arready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__rdata = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 692004651061322182ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__rready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__rresp = 3U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__awaddr = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__awvalid = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__awready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__wdata = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__wstrb = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__wvalid = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__wready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4838129685289160529ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__bready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_if__DOT__bresp = 3U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6231765149506116841ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3061716237785084000ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__araddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13858801636045484254ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12645242248688942450ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__arready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__rdata = 0U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 691033762628652812ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16803428303905733141ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__rresp = 3U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__awaddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11602336414254692962ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7812607761845291795ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__awready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8946812658917610968ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 5814885809241877334ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15589726959392198843ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__wready = 1U;
    ;
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6668322014668747197ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1563741448183788392ull);
    vlSelf->top__DOT__u_mem__DOT__u_default_data__DOT__bresp = 3U;
    ;
    vlSelf->__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__4__Vfuncout = 0;
    vlSelf->__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__4__return_op = 0;
    vlSelf->__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__5__Vfuncout = 0;
    vlSelf->__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__5__return_op = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_3 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_4 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_5 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__cpu_clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_reg_file__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_reg_file__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_fetch__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_fetch__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_if_id__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_if_id__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_id_ex__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_id_ex__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_ex_mem__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_ex_mem__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_lsu__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_lsu__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_data_decoder__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_data_decoder__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_mmio_interface__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_mem_wb__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_mem_wb__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_meta__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_meta__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_boot_rom__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_boot_rom__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_ram__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_ram__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_default_if__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_default_if__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_default_data__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_default_data__DOT__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
