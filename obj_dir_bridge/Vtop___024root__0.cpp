// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

void Vtop___024root___eval_triggers_vec__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_triggers_vec__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
}

bool Vtop___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_anySet__ico\n"); );
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

extern const VlUnpacked<CData/*0:0*/, 16> Vtop__ConstPool__TABLE_h50f0aed2_0;

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*3:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_6;
    __VdfgRegularize_h6e95ff9d_0_6 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_7;
    __VdfgRegularize_h6e95ff9d_0_7 = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_8;
    __VdfgRegularize_h6e95ff9d_0_8 = 0;
    // Body
    vlSelfRef.top__DOT__rst_n = vlSelfRef.rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_illegal = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_illegal;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_if_fault 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_if_fault;
    vlSelfRef.top__DOT__u_mem__DOT__dif_bvalid = vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__bvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__if_id_pc = vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__o_pc;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_mem_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_write;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_mem_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_mem_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_hold = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__uart_tx_start = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_start;
    vlSelfRef.top__DOT__u_cpu__DOT__uart_rx_ack = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_ack;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_enable 
        = (1U & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_meta_control) 
                 >> 1U));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_clear 
        = (1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_meta_control));
    vlSelfRef.top__DOT__i_rx = vlSelfRef.i_rx;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx;
    vlSelfRef.top__DOT__u_mem__DOT__data_bready = vlSelfRef.top__DOT__data_bready;
    vlSelfRef.top__DOT__u_mem__DOT__data_rready = vlSelfRef.top__DOT__data_rready;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_uart_tx_data;
    vlSelfRef.top__DOT__if_arready = vlSelfRef.top__DOT__u_mem__DOT__if_arready;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__baud_tick 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__tick;
    vlSelfRef.top__DOT__u_cpu__DOT__instr_fault_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__instr_fault_q;
    vlSelfRef.top__DOT__u_cpu__DOT__data_fault_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_fault_q;
    vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__illegal_q;
    vlSelfRef.top__DOT__u_cpu__DOT__stop = vlSelfRef.top__DOT__u_cpu__DOT__stop_q;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_instr_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__instr_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_stall_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__stall_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_l_use_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_br_flush_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rx_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_bresp = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_bresp;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx_busy 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__start_pending) 
           | (0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state)));
    vlSelfRef.top__DOT__u_mem__DOT__ram_if_rdata = vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_rdata;
    vlSelfRef.top__DOT__u_mem__DOT__rom_if_rdata = vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_rdata;
    vlSelfRef.top__DOT__u_cpu__DOT__if_id_fault = vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__o_fault;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__space 
        = VL_GTS_III(32, 2U, ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cap_cnt) 
                              + (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__inflight)));
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_rs2_val 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_rs2_val;
    vlSelfRef.top__DOT__core_rst_n = (1U & ((IData)(vlSelfRef.top__DOT__rst_sync) 
                                            >> 1U));
    vlSelfRef.top__DOT__clk = vlSelfRef.clk;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_pc_in1_sel 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_pc_in1_sel;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_rresp = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rresp;
    vlSelfRef.top__DOT__u_mem__DOT__dif_rvalid = vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__rvalid;
    vlSelfRef.top__DOT__u_mem__DOT__ram_if_rvalid = vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_rvalid;
    vlSelfRef.top__DOT__u_mem__DOT__rom_if_rvalid = vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_rvalid;
    if ((1U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel_q))) {
        vlSelfRef.top__DOT__u_mem__DOT__if_rresp = 0U;
        vlSelfRef.top__DOT__u_mem__DOT__if_rdata = vlSelfRef.top__DOT__u_mem__DOT__rom_if_rdata;
        vlSelfRef.top__DOT__u_mem__DOT__if_rvalid = vlSelfRef.top__DOT__u_mem__DOT__rom_if_rvalid;
    } else if ((2U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel_q))) {
        vlSelfRef.top__DOT__u_mem__DOT__if_rresp = 0U;
        vlSelfRef.top__DOT__u_mem__DOT__if_rdata = vlSelfRef.top__DOT__u_mem__DOT__ram_if_rdata;
        vlSelfRef.top__DOT__u_mem__DOT__if_rvalid = vlSelfRef.top__DOT__u_mem__DOT__ram_if_rvalid;
    } else {
        vlSelfRef.top__DOT__u_mem__DOT__if_rresp = 3U;
        vlSelfRef.top__DOT__u_mem__DOT__if_rdata = 0U;
        vlSelfRef.top__DOT__u_mem__DOT__if_rvalid = vlSelfRef.top__DOT__u_mem__DOT__dif_rvalid;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_mem_read 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_read;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_stop = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_is_stop;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_stop = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_stop;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_stop = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_is_stop;
    vlSelfRef.top__DOT__data_arready = vlSelfRef.top__DOT__u_mem__DOT__data_arready;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_bvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_bvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_rvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rvalid;
    vlSelfRef.top__DOT__u_mem__DOT__ddt_bvalid = vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__bvalid;
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_bvalid = vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_bvalid;
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_bvalid = vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_bvalid;
    if ((1U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel_q))) {
        vlSelfRef.top__DOT__u_mem__DOT__data_bresp = 2U;
        vlSelfRef.top__DOT__u_mem__DOT__data_bvalid 
            = vlSelfRef.top__DOT__u_mem__DOT__rom_d_bvalid;
    } else if ((2U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel_q))) {
        vlSelfRef.top__DOT__u_mem__DOT__data_bresp = 0U;
        vlSelfRef.top__DOT__u_mem__DOT__data_bvalid 
            = vlSelfRef.top__DOT__u_mem__DOT__ram_d_bvalid;
    } else {
        vlSelfRef.top__DOT__u_mem__DOT__data_bresp = 3U;
        vlSelfRef.top__DOT__u_mem__DOT__data_bvalid 
            = vlSelfRef.top__DOT__u_mem__DOT__ddt_bvalid;
    }
    vlSelfRef.top__DOT__u_mem__DOT__ddt_rvalid = vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__rvalid;
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_rvalid = vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_rvalid;
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_rvalid = vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_branch 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_branch;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_jal = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_jal;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_jalr = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_jalr;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_funct3 = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_in1_ropc 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_in1_ropc;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_in2_roi 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_in2_roi;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_op;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_bypass 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_bypass;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_imm_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_imm_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs2_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs2_data;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_imm_val = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_imm_val;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs1_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs1_data;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_pc = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_pc;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_result = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_result;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_funct3 = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_addr_lo 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_addr_lo;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_rdata = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rdata;
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_rdata = vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_rdata;
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_rdata = vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_rdata;
    if ((1U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel_q))) {
        vlSelfRef.top__DOT__u_mem__DOT__data_rresp = 0U;
        vlSelfRef.top__DOT__u_mem__DOT__data_rvalid 
            = vlSelfRef.top__DOT__u_mem__DOT__rom_d_rvalid;
        vlSelfRef.top__DOT__u_mem__DOT__data_rdata 
            = vlSelfRef.top__DOT__u_mem__DOT__rom_d_rdata;
    } else if ((2U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel_q))) {
        vlSelfRef.top__DOT__u_mem__DOT__data_rresp = 0U;
        vlSelfRef.top__DOT__u_mem__DOT__data_rvalid 
            = vlSelfRef.top__DOT__u_mem__DOT__ram_d_rvalid;
        vlSelfRef.top__DOT__u_mem__DOT__data_rdata 
            = vlSelfRef.top__DOT__u_mem__DOT__ram_d_rdata;
    } else {
        vlSelfRef.top__DOT__u_mem__DOT__data_rresp = 3U;
        vlSelfRef.top__DOT__u_mem__DOT__data_rvalid 
            = vlSelfRef.top__DOT__u_mem__DOT__ddt_rvalid;
        vlSelfRef.top__DOT__u_mem__DOT__data_rdata = 0U;
    }
    vlSelfRef.top__DOT__data_awready = vlSelfRef.top__DOT__u_mem__DOT__data_awready;
    vlSelfRef.top__DOT__data_wready = vlSelfRef.top__DOT__u_mem__DOT__data_wready;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rd_addr = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_mem_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_mem_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_rd_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_rd_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr = vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__o_instr;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs2_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs2_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs1_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs1_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3 = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_opcode = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_opcode;
    vlSelfRef.top__DOT__u_cpu__DOT__halt = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__instr_fault_q) 
                                            | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__data_fault_q) 
                                               | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__illegal_q)));
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_read 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_mem_read;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_mem_write;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_result;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_pc 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_id_pc;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_mem_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_mem_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_mem_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_mem_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx_start 
        = vlSelfRef.top__DOT__u_cpu__DOT__uart_tx_start;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rx_ack 
        = vlSelfRef.top__DOT__u_cpu__DOT__uart_rx_ack;
    vlSelfRef.top__DOT__u_cpu__DOT__meta_enable = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__meta_clear = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__i_rx = vlSelfRef.top__DOT__i_rx;
    vlSelfRef.top__DOT__u_cpu__DOT__o_tx = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_bready 
        = vlSelfRef.top__DOT__u_mem__DOT__data_bready;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_bready 
        = vlSelfRef.top__DOT__u_mem__DOT__data_bready;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__bready 
        = vlSelfRef.top__DOT__u_mem__DOT__data_bready;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_rready 
        = vlSelfRef.top__DOT__u_mem__DOT__data_rready;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_rready 
        = vlSelfRef.top__DOT__u_mem__DOT__data_rready;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__rready 
        = vlSelfRef.top__DOT__u_mem__DOT__data_rready;
    vlSelfRef.top__DOT__u_cpu__DOT__uart_tx_data = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_data;
    vlSelfRef.top__DOT__u_cpu__DOT__if_arready = vlSelfRef.top__DOT__if_arready;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__baud_tick 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__baud_tick;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__baud_tick 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__baud_tick;
    vlSelfRef.top__DOT__instr_fault = vlSelfRef.top__DOT__u_cpu__DOT__instr_fault_out;
    vlSelfRef.top__DOT__data_fault = vlSelfRef.top__DOT__u_cpu__DOT__data_fault_out;
    vlSelfRef.top__DOT__illegal_instr = vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr_out;
    vlSelfRef.top__DOT__stop = vlSelfRef.top__DOT__u_cpu__DOT__stop;
    vlSelfRef.top__DOT__u_cpu__DOT__meta_instr_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_instr_count;
    vlSelfRef.top__DOT__u_cpu__DOT__meta_stall_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_stall_count;
    vlSelfRef.top__DOT__u_cpu__DOT__meta_l_use_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_l_use_count;
    vlSelfRef.top__DOT__u_cpu__DOT__meta_br_flush_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_br_flush_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rx_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_data;
    vlSelfRef.top__DOT__u_cpu__DOT__uart_rx_valid = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rx_valid;
    vlSelfRef.top__DOT__if_rresp = vlSelfRef.top__DOT__u_mem__DOT__if_rresp;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_bresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_bresp;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx_busy 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx_busy;
    vlSelfRef.top__DOT__data_bresp = vlSelfRef.top__DOT__u_mem__DOT__data_bresp;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_if_fault 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_id_fault;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__rs2_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_rs2_val;
    vlSelfRef.top__DOT__u_mem__DOT__rst_n = vlSelfRef.top__DOT__core_rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__rst_n = vlSelfRef.top__DOT__core_rst_n;
    vlSelfRef.top__DOT__cpu_clk = vlSelfRef.top__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pcinc_in1_pcor 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_pc_in1_sel;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_rresp;
    vlSelfRef.top__DOT__data_rresp = vlSelfRef.top__DOT__u_mem__DOT__data_rresp;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_mem_read 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_mem_read;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_mem_read 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_mem_read;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_is_stop 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_stop;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_is_stop 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_stop;
    vlSelfRef.top__DOT__u_cpu__DOT__stop_in_flight 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_stop) 
           | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_stop) 
              | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_stop)));
    vlSelfRef.top__DOT__u_cpu__DOT__data_arready = vlSelfRef.top__DOT__data_arready;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_bvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_bvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__is_branch 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_branch;
    vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__is_jal 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_jal;
    vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__is_jalr 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_jalr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_funct3 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__id_ex_funct3 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__use_pc 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_in1_ropc;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__use_imm 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_in2_roi;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_bypass 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_bypass;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__imm_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_imm_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__r_data2 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs2_data;
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__imm_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_imm_val;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__imm 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_imm_val;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__r_data1 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs1_data;
    vlSelfRef.top__DOT__u_cpu__DOT__pc_plus4 = ((IData)(4U) 
                                                + vlSelfRef.top__DOT__u_cpu__DOT__id_ex_pc);
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pc_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_pc;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__pc 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_pc;
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__result 
        = vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_result;
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__funct3 
        = vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__addr_lo 
        = vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_addr_lo;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_rdata;
    vlSelfRef.top__DOT__u_cpu__DOT__data_awready = vlSelfRef.top__DOT__data_awready;
    vlSelfRef.top__DOT__u_cpu__DOT__data_wready = vlSelfRef.top__DOT__data_wready;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_rd_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rd 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__mem_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_mem_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__ex_mem_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_rd_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__ex_mem_rd 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_rd 
        = vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr;
    vlSelfRef.top__DOT__u_cpu__DOT__if_id_rs1_addr 
        = (0x0000001fU & (vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr 
                          >> 0x0000000fU));
    vlSelfRef.top__DOT__u_cpu__DOT__if_id_rs2_addr 
        = (0x0000001fU & (vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr 
                          >> 0x00000014U));
    vlSelfRef.top__DOT__u_cpu__DOT__if_id_opcode = 
        (0x0000007fU & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr);
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs2_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs1_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_funct3 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__funct3 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_opcode 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_opcode;
    vlSelfRef.top__DOT__halt = vlSelfRef.top__DOT__u_cpu__DOT__halt;
    vlSelfRef.top__DOT__u_cpu__DOT__freeze = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__halt) 
                                              | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__stop_q));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_read 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_read;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_result 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_addr_lo 
        = (3U & vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result);
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__ex_mem_rd_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx_start 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx_start;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_ack 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rx_ack;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__meta_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__clear 
        = vlSelfRef.top__DOT__u_cpu__DOT__meta_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rx 
        = vlSelfRef.top__DOT__u_cpu__DOT__i_rx;
    vlSelfRef.top__DOT__o_tx = vlSelfRef.top__DOT__u_cpu__DOT__o_tx;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__uart_tx_data;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_arready 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_arready;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__bit_done 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__baud_tick) 
           & (0x0fU == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tick_cntr)));
    vlSelfRef.top__DOT__led = ((((IData)(vlSelfRef.top__DOT__illegal_instr) 
                                 << 3U) | ((IData)(vlSelfRef.top__DOT__data_fault) 
                                           << 2U)) 
                               | (((IData)(vlSelfRef.top__DOT__instr_fault) 
                                   << 1U) | (IData)(vlSelfRef.top__DOT__stop)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_instr_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__meta_instr_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_stall_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__meta_stall_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_l_use_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__meta_l_use_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_br_flush_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__meta_br_flush_count;
    vlSelfRef.top__DOT__u_cpu__DOT__uart_rx_data = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rx_data;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__uart_rx_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__if_rresp = vlSelfRef.top__DOT__if_rresp;
    vlSelfRef.top__DOT__u_cpu__DOT__uart_tx_busy = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx_busy;
    vlSelfRef.top__DOT__if_rdata = vlSelfRef.top__DOT__u_mem__DOT__if_rdata;
    vlSelfRef.top__DOT__u_cpu__DOT__data_bresp = vlSelfRef.top__DOT__data_bresp;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__rst_n 
        = vlSelfRef.top__DOT__u_mem__DOT__rst_n;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__rst_n 
        = vlSelfRef.top__DOT__u_mem__DOT__rst_n;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__rst_n 
        = vlSelfRef.top__DOT__u_mem__DOT__rst_n;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__rst_n 
        = vlSelfRef.top__DOT__u_mem__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_mem__DOT__clk = vlSelfRef.top__DOT__cpu_clk;
    vlSelfRef.top__DOT__u_cpu__DOT__clk = vlSelfRef.top__DOT__cpu_clk;
    vlSelfRef.top__DOT__u_cpu__DOT__data_rresp = vlSelfRef.top__DOT__data_rresp;
    vlSelfRef.top__DOT__if_rvalid = vlSelfRef.top__DOT__u_mem__DOT__if_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_mem_read 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_mem_read;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__stop_in_flight 
        = vlSelfRef.top__DOT__u_cpu__DOT__stop_in_flight;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_arready 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_arready;
    vlSelfRef.top__DOT__data_bvalid = vlSelfRef.top__DOT__u_mem__DOT__data_bvalid;
    vlSelfRef.top__DOT__data_rvalid = vlSelfRef.top__DOT__u_mem__DOT__data_rvalid;
    vlSelfRef.top__DOT__data_rdata = vlSelfRef.top__DOT__u_mem__DOT__data_rdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_awready 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_awready;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wready 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_wready;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rd 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rd;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__ex_mem_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__ex_mem_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__ex_mem_rd 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__ex_mem_rd;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__mem_wb_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__mem_wb_rd 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_rd;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__rd_addr 
        = (0x0000001fU & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                          >> 7U));
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__rs1_addr 
        = (0x0000001fU & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                          >> 0x0000000fU));
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__rs2_addr 
        = (0x0000001fU & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                          >> 0x00000014U));
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3 
        = (7U & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                 >> 0x0000000cU));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_id_rs1_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_id_rs2_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_opcode 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_id_opcode;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_opcode 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_id_opcode;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__size_mask 
        = ((0U == (3U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__funct3)))
            ? 1U : (0x0000000fU & (3U | (- (IData)(
                                                   (1U 
                                                    != 
                                                    (3U 
                                                     & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__funct3))))))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_opcode;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__freeze 
        = vlSelfRef.top__DOT__u_cpu__DOT__freeze;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__freeze 
        = vlSelfRef.top__DOT__u_cpu__DOT__freeze;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_access 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_read) 
           | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_write));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wdata 
        = (vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__rs2_in 
           << (0x00000018U & (vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res 
                              << 3U)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_araddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_awaddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__misaligned 
        = ((0U != (3U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__funct3))) 
           & ((1U == (3U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__funct3)))
               ? (3U == (3U & vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res))
               : (0U != (3U & vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__region 
        = (3U & (((0x00002000U > vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res)
                   ? 1U : (2U & (- (IData)((0x00022000U 
                                            > vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res))))) 
                 | (- (IData)((vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res 
                               >> 0x0000001fU)))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rx;
    vlSelfRef.o_tx = vlSelfRef.top__DOT__o_tx;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx_data;
    vlSelfRef.led = vlSelfRef.top__DOT__led;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__uart_rx_data;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_rresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_rresp;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_busy 
        = vlSelfRef.top__DOT__u_cpu__DOT__uart_tx_busy;
    vlSelfRef.top__DOT__u_cpu__DOT__if_rdata = vlSelfRef.top__DOT__if_rdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_bresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_bresp;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rst_n;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__clk 
        = vlSelfRef.top__DOT__u_mem__DOT__clk;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__clk 
        = vlSelfRef.top__DOT__u_mem__DOT__clk;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__clk 
        = vlSelfRef.top__DOT__u_mem__DOT__clk;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__clk 
        = vlSelfRef.top__DOT__u_mem__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__clk 
        = vlSelfRef.top__DOT__u_cpu__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__clk 
        = vlSelfRef.top__DOT__u_cpu__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__clk 
        = vlSelfRef.top__DOT__u_cpu__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__clk 
        = vlSelfRef.top__DOT__u_cpu__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__clk 
        = vlSelfRef.top__DOT__u_cpu__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__clk 
        = vlSelfRef.top__DOT__u_cpu__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__clk 
        = vlSelfRef.top__DOT__u_cpu__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__clk 
        = vlSelfRef.top__DOT__u_cpu__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__clk 
        = vlSelfRef.top__DOT__u_cpu__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__clk 
        = vlSelfRef.top__DOT__u_cpu__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__clk 
        = vlSelfRef.top__DOT__u_cpu__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_rresp;
    vlSelfRef.top__DOT__u_cpu__DOT__if_rvalid = vlSelfRef.top__DOT__if_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__stop_in_flight 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__stop_in_flight;
    vlSelfRef.top__DOT__u_cpu__DOT__data_bvalid = vlSelfRef.top__DOT__data_bvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__data_rvalid = vlSelfRef.top__DOT__data_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__data_rdata = vlSelfRef.top__DOT__data_rdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rd_not_x0 
        = (0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rd));
    vlSelfRef.top__DOT__u_cpu__DOT__rdst_addr = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__rs1_addr = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__rs1_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__rs2_addr = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__rs2_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__funct3 = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode 
        = (0x0000007fU & vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr);
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in1_ropc = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in2_roi = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_bypass = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_write = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_read = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_op = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_to_reg = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_to_reg = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__pcinc_in1_pcor = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_branch = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_jal = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_jalr = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 5U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__stop = 0U;
    if ((0x00000040U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        if ((0x00000020U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((0x00000010U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_bypass = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 0U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__stop = 1U;
                    } else {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                        if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 1U;
                            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in1_ropc = 1U;
                            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 4U;
                            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_jal = 1U;
                        } else {
                            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                        }
                    } else {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in1_ropc = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__pcinc_in1_pcor = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 0U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_jalr = 1U;
                        if ((0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))) {
                            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                        }
                    } else {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in2_roi = 0U;
                    if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_op 
                            = ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                ? 0x0cU : 0x0dU);
                    } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_op = 0U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                    } else {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_op = 4U;
                    }
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 2U;
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_branch = 1U;
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        }
    } else if ((0x00000020U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        if ((0x00000010U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_to_reg = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 3U;
                    } else {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__4__return_op 
                        = ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                            ? ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                ? ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                    ? 6U : 5U) : ((1U 
                                                   & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                                   ? 
                                                  ((0x40000000U 
                                                    & vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr)
                                                    ? 0x0bU
                                                    : 0x0aU)
                                                   : 4U))
                            : ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                ? ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                    ? 0x0cU : 0x0dU)
                                : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                    ? 8U : ((0x40000000U 
                                             & vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr)
                                             ? 1U : 0U))));
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 1U;
                    vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__4__Vfuncout 
                        = vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__4__return_op;
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in2_roi = 0U;
                    if ((1U & (~ ((0U == (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                                          >> 0x19U)) 
                                  | ((0x20U == (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                                                >> 0x19U)) 
                                     & ((0U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3)) 
                                        | (5U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3)))))))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                    }
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_op 
                        = vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__4__Vfuncout;
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            }
        } else if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_write = 1U;
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 1U;
                if ((2U < (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        }
    } else if ((0x00000010U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 1U;
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in1_ropc = 1U;
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 3U;
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            }
        } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__5__return_op 
                    = ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                        ? ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                            ? ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                ? 6U : 5U) : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                               ? ((0x40000000U 
                                                   & vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr)
                                                   ? 0x0bU
                                                   : 0x0aU)
                                               : 4U))
                        : ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                            ? ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                ? 0x0cU : 0x0dU) : 
                           ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                             ? 8U : 0U)));
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 1U;
                vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__5__Vfuncout 
                    = vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__5__return_op;
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 0U;
                if ((((1U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3)) 
                      & (0U != (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                                >> 0x19U))) | (((5U 
                                                 == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3)) 
                                                & (0U 
                                                   != 
                                                   (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                                                    >> 0x19U))) 
                                               & (0x20U 
                                                  != 
                                                  (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                                                   >> 0x19U))))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_op 
                    = vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__5__Vfuncout;
                if ((0x00000013U == vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr)) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 0U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        }
    } else if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    if ((0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        }
    } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
    } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 1U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_to_reg = 1U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_read = 1U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 0U;
            if ((((3U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3)) 
                  | (6U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))) 
                 | (7U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3)))) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_opcode;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_ex_mem_rd_id_ex_rs2 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2) 
           == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__ex_mem_rd));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_mem_wb_rd_id_ex_rs2 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2) 
           == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__mem_wb_rd));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2_not_x0 
        = (0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_ex_mem_rd_id_ex_rs1 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1) 
           == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__ex_mem_rd));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_mem_wb_rd_id_ex_rs1 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1) 
           == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__mem_wb_rd));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1_not_x0 
        = (0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wstrb 
        = (0x0000000fU & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__size_mask) 
                          << (3U & vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res)));
    __VdfgRegularize_h6e95ff9d_0_6 = ((0x33U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode)) 
                                      | ((0x23U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode)) 
                                         | (0x63U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__freeze 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__freeze;
    vlSelfRef.top__DOT__u_cpu__DOT__data_wdata_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__data_araddr_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__data_awaddr_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_awaddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mmio 
        = (3U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__region));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__pre_fault 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_access) 
           & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__misaligned) 
              | ((0U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__region)) 
                 | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_write) 
                    & (1U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__region))))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_uart_status 
        = ((((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_start) 
             | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_busy)) 
            << 1U) | ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_ack)) 
                      & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_valid)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_rdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_rdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__clk 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__clk 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__clk 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__clk;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_rvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_bvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_bvalid;
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_sel_q) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_bresp 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_bresp;
        vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_bvalid 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_bvalid;
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_bresp 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_bresp;
        vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_bvalid 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_bvalid;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_rdata;
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_sel_q) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rresp 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rresp;
        vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rvalid 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rvalid;
        vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rdata 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rdata;
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rresp 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rresp;
        vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rvalid 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rvalid;
        vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rdata 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rdata;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rd_not_x0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rd_not_x0;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rd_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__rdst_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs1_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__rs1_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr1 
        = vlSelfRef.top__DOT__u_cpu__DOT__rs1_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs2_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__rs2_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr2 
        = vlSelfRef.top__DOT__u_cpu__DOT__rs2_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_funct3 
        = vlSelfRef.top__DOT__u_cpu__DOT__funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__alu_in1_sel = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in1_ropc;
    vlSelfRef.top__DOT__u_cpu__DOT__alu_in2_sel = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in2_roi;
    vlSelfRef.top__DOT__u_cpu__DOT__alu_bypass = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_bypass;
    vlSelfRef.top__DOT__u_cpu__DOT__alu_op = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_op;
    vlSelfRef.top__DOT__u_cpu__DOT__imm_to_reg = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__pc_in1_sel = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__pcinc_in1_pcor;
    vlSelfRef.top__DOT__u_cpu__DOT__d_stop = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__stop;
    vlSelfRef.top__DOT__u_cpu__DOT__reg_w_enable = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_write = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_write;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_read = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_read;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_to_reg = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__d_is_branch = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_branch;
    vlSelfRef.top__DOT__u_cpu__DOT__d_is_jal = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_jal;
    vlSelfRef.top__DOT__u_cpu__DOT__d_is_jalr = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_jalr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_type 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type;
    vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr_fault 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_id_ex_rd_if_id_rs1 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs1) 
           == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rd));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_id_ex_rd_if_id_rs2 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs2) 
           == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rd));
    __VdfgRegularize_h6e95ff9d_0_7 = ((0x33U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode)) 
                                      | ((0x23U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode)) 
                                         | (0x63U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_ex_mem_rd_id_ex_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_ex_mem_rd_id_ex_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_mem_wb_rd_id_ex_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_mem_wb_rd_id_ex_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs2_not_x0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2_not_x0;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_ex_mem_rd_id_ex_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_ex_mem_rd_id_ex_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_mem_wb_rd_id_ex_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_mem_wb_rd_id_ex_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs1_not_x0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1_not_x0;
    vlSelfRef.top__DOT__u_cpu__DOT__data_wstrb_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wstrb;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2_valid 
        = __VdfgRegularize_h6e95ff9d_0_6;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1_valid 
        = ((IData)(__VdfgRegularize_h6e95ff9d_0_6) 
           | ((0x13U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode)) 
              | ((3U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode)) 
                 | ((0x67U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode)) 
                    | (0x73U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode))))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_wdata_out;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_araddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_araddr_out;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awaddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_awaddr_out;
    vlSelfRef.top__DOT__u_cpu__DOT__lsu_pre_fault = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__pre_fault;
    __VdfgRegularize_h6e95ff9d_0_8 = (1U & (~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__freeze) 
                                               | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__pre_fault))));
    vlSelfRef.top__DOT__u_cpu__DOT__data_bresp_in = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_bresp;
    vlSelfRef.top__DOT__u_cpu__DOT__data_rresp_in = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rresp;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__r_hs 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_rd_not_x0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rd_not_x0;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_in1_ropc 
        = vlSelfRef.top__DOT__u_cpu__DOT__alu_in1_sel;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_in2_roi 
        = vlSelfRef.top__DOT__u_cpu__DOT__alu_in2_sel;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_bypass 
        = vlSelfRef.top__DOT__u_cpu__DOT__alu_bypass;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_op 
        = vlSelfRef.top__DOT__u_cpu__DOT__alu_op;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_imm_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__imm_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_pc_in1_sel 
        = vlSelfRef.top__DOT__u_cpu__DOT__pc_in1_sel;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_stop 
        = vlSelfRef.top__DOT__u_cpu__DOT__d_stop;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_out 
        = ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_type))
            ? ((- (IData)((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_type))))) 
               & ((((- (IData)((vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                >> 0x0000001fU))) << 0x00000014U) 
                   | ((((0x000001feU & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                        >> 0x0000000bU)) 
                        | (1U & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                 >> 0x00000014U))) 
                       << 0x0000000bU) | (0x000007feU 
                                          & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                             >> 0x00000014U)))) 
                  & (- (IData)((1U & (~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_type) 
                                         >> 1U)))))))
            : ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_type))
                ? ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_type))
                    ? (0xfffff000U & vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr)
                    : (((- (IData)((vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                    >> 0x0000001fU))) 
                        << 0x0000000cU) | ((0x00000800U 
                                            & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                               << 4U)) 
                                           | ((0x000007e0U 
                                               & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                                  >> 0x00000014U)) 
                                              | (0x0000001eU 
                                                 & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                                    >> 7U))))))
                : (((- (IData)((vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                >> 0x0000001fU))) << 0x0000000bU) 
                   | (0x000007ffU & ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_type))
                                      ? ((0x000007e0U 
                                          & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                             >> 0x00000014U)) 
                                         | (0x0000001fU 
                                            & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                               >> 7U)))
                                      : (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                         >> 0x00000014U))))));
    vlSelfRef.top__DOT__u_cpu__DOT__id_kill = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr_fault) 
                                               | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__if_id_fault));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_id_ex_rd_if_id_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_id_ex_rd_if_id_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_id_ex_rd_if_id_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_id_ex_rd_if_id_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs2_valid 
        = __VdfgRegularize_h6e95ff9d_0_7;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs1_valid 
        = ((IData)(__VdfgRegularize_h6e95ff9d_0_7) 
           | ((0x13U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode)) 
              | ((3U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode)) 
                 | ((0x67U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode)) 
                    | (0x73U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode))))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_ex_mem_rd_id_ex_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_ex_mem_rd_id_ex_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_mem_wb_rd_id_ex_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_mem_wb_rd_id_ex_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs2_not_x0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs2_not_x0;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_ex_mem_rd_id_ex_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_ex_mem_rd_id_ex_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_mem_wb_rd_id_ex_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_mem_wb_rd_id_ex_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs1_not_x0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs1_not_x0;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wstrb 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_wstrb_out;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs2_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs1_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_araddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_araddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_mmio 
        = (vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_araddr 
           >> 0x0000001fU);
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_awaddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awaddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_awaddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awaddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio 
        = (vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awaddr 
           >> 0x0000001fU);
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_reg_write 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__lsu_pre_fault)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_reg_write));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_mem_to_reg 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__lsu_pre_fault)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_to_reg));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__load_req 
        = ((IData)(__VdfgRegularize_h6e95ff9d_0_8) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_read));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__store_req 
        = ((IData)(__VdfgRegularize_h6e95ff9d_0_8) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_write));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_bresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_bresp_in;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_rresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_rresp_in;
    vlSelfRef.top__DOT__u_cpu__DOT__data_bvalid_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_bvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__data_rvalid_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__data_rdata_in = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rdata;
    if (vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_valid) {
        vlSelfRef.top__DOT__u_cpu__DOT__wb_rresp = vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_resp;
        vlSelfRef.top__DOT__u_cpu__DOT__wb_rdata = vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_data;
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__wb_rresp = vlSelfRef.top__DOT__u_cpu__DOT__data_rresp_in;
        vlSelfRef.top__DOT__u_cpu__DOT__wb_rdata = vlSelfRef.top__DOT__u_cpu__DOT__data_rdata_in;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_val 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_out;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_illegal 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_kill;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_mem_read 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_kill)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_read));
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_mem_write 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_kill)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_write));
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_branch 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_kill)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__d_is_branch));
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_jal 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_kill)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__d_is_jal));
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_jalr 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_kill)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__d_is_jalr));
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_reg_write 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_kill)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__reg_w_enable));
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_mem_to_reg 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_kill)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_to_reg));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_id_ex_rd_if_id_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_id_ex_rd_if_id_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__dep_id_ex_rd_if_id_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_id_ex_rd_if_id_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_id_ex_rd_if_id_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_id_ex_rd_if_id_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__dep_id_ex_rd_if_id_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_id_ex_rd_if_id_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs2_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs2_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs1_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs1_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wstrb 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wstrb;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wstrb 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wstrb;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs2_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs2_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs1_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs1_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_wdata = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__data_wdata = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_araddr = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__data_araddr = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_arready 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_arready) 
           | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_mmio));
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_awaddr = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_awaddr;
    vlSelfRef.top__DOT__u_cpu__DOT__data_awaddr = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_awaddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awready 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_awready) 
           | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wready 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wready) 
           | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_arvalid 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_sent)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__load_req));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_awvalid 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__aw_sent)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__store_req));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wvalid 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__w_sent)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__store_req));
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__data_rresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__wb_rresp;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_bvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_bvalid_in;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_rvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_rvalid_in;
    vlSelfRef.top__DOT__u_cpu__DOT__wb_data_wait = 
        ((~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_valid) 
             | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__data_rvalid_in))) 
         & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_mem_to_reg));
    vlSelfRef.top__DOT__u_cpu__DOT__imm_val = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_val;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_rs2_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs2_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_rs1_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs1_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_wstrb = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wstrb;
    vlSelfRef.top__DOT__u_cpu__DOT__data_wstrb = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wstrb;
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4 = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs2_not_x0) 
                                                & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs2_valid));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_5 = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs1_not_x0) 
                                                & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs1_valid));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_wdata;
    vlSelfRef.top__DOT__data_wdata = vlSelfRef.top__DOT__u_cpu__DOT__data_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_araddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_araddr;
    vlSelfRef.top__DOT__data_araddr = vlSelfRef.top__DOT__u_cpu__DOT__data_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__data_arready_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_arready;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_awaddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_awaddr;
    vlSelfRef.top__DOT__data_awaddr = vlSelfRef.top__DOT__u_cpu__DOT__data_awaddr;
    vlSelfRef.top__DOT__u_cpu__DOT__data_awready_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awready;
    vlSelfRef.top__DOT__u_cpu__DOT__data_wready_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wready;
    vlSelfRef.top__DOT__u_cpu__DOT__data_arvalid_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_arvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__data_awvalid_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_awvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__data_wvalid_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__load_fault 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__mem_to_reg) 
           & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__data_rresp) 
              >> 1U));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__b_hs 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_bvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__wb_data_wait 
        = vlSelfRef.top__DOT__u_cpu__DOT__wb_data_wait;
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__data_rdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__wb_rdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_imm_val 
        = vlSelfRef.top__DOT__u_cpu__DOT__imm_val;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wstrb 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_wstrb;
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_hold = 1U;
    }
    vlSelfRef.top__DOT__data_wstrb = vlSelfRef.top__DOT__u_cpu__DOT__data_wstrb;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in2_ex_mem 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4) 
           & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_ex_mem_rd_id_ex_rs2) 
              & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__ex_mem_reg_write)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in2_mem_wb 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4) 
           & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_mem_wb_rd_id_ex_rs2) 
              & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__mem_wb_reg_write)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in1_ex_mem 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_5) 
           & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_ex_mem_rd_id_ex_rs1) 
              & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__ex_mem_reg_write)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in1_mem_wb 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_5) 
           & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_mem_wb_rd_id_ex_rs1) 
              & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__mem_wb_reg_write)));
    vlSelfRef.top__DOT__u_mem__DOT__data_wdata = vlSelfRef.top__DOT__data_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word 
        = (0x7ffffffcU & vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_araddr);
    vlSelfRef.top__DOT__u_mem__DOT__data_araddr = vlSelfRef.top__DOT__data_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_arready 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_arready_in;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__wr_word 
        = (0x7ffffffcU & vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_awaddr);
    vlSelfRef.top__DOT__u_mem__DOT__data_awaddr = vlSelfRef.top__DOT__data_awaddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_awready 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_awready_in;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wready 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_wready_in;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_arvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_arvalid_out;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_awvalid_out;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_wvalid_out;
    vlSelfRef.top__DOT__u_cpu__DOT__load_fault = vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__load_fault;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_fault 
        = (((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__freeze)) 
            & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__pre_fault)) 
           | (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_rvalid) 
               & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_rresp) 
                  >> 1U)) | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__b_hs) 
                             & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_bresp) 
                                >> 1U))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__wb_data_wait 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__wb_data_wait;
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted 
        = (vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__data_rdata 
           >> ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__addr_lo) 
               << 3U));
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__load_val 
        = ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__funct3))
            ? ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__funct3))
                ? vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted
                : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__funct3))
                    ? (0x0000ffffU & vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted)
                    : (0x000000ffU & vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted)))
            : ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__funct3))
                ? vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted
                : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__funct3))
                    ? (((- (IData)((1U & (vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted 
                                          >> 0x0fU)))) 
                        << 0x00000010U) | (0x0000ffffU 
                                           & vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted))
                    : (((- (IData)((1U & (vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted 
                                          >> 7U)))) 
                        << 8U) | (0x000000ffU & vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted)))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__rd_data 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__mem_to_reg)
            ? vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__load_val
            : vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__result);
    vlSelfRef.top__DOT__u_mem__DOT__data_wstrb = vlSelfRef.top__DOT__data_wstrb;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in2_ex_mem 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in2_ex_mem;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in2_mem_wb 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in2_mem_wb;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in1_ex_mem 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in1_ex_mem;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in1_mem_wb 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in1_mem_wb;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_wdata 
        = vlSelfRef.top__DOT__u_mem__DOT__data_wdata;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_wdata 
        = vlSelfRef.top__DOT__u_mem__DOT__data_wdata;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__wdata 
        = vlSelfRef.top__DOT__u_mem__DOT__data_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_resp = 0U;
    if ((1U & (~ ((((((((0U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word) 
                        | (4U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
                       | (8U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
                      | (0x00001000U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
                     | (0x00001004U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
                    | (0x00001008U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
                   | (0x0000100cU == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
                  | (0x00001010U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word))))) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_resp = 2U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_val = 0U;
    if (((((((((0U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word) 
               | (4U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
              | (8U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
             | (0x00001000U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
            | (0x00001004U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
           | (0x00001008U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
          | (0x0000100cU == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
         | (0x00001010U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word))) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_val 
            = ((0U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)
                ? (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_uart_status)
                : ((4U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)
                    ? (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_data)
                    : ((8U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)
                        ? 0U : ((0x00001000U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)
                                 ? ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_meta_control) 
                                    << 8U) : ((0x00001004U 
                                               == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)
                                               ? vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_instr_count
                                               : ((0x00001008U 
                                                   == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)
                                                   ? vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_stall_count
                                                   : 
                                                  ((0x0000100cU 
                                                    == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)
                                                    ? vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_l_use_count
                                                    : vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_br_flush_count)))))));
    }
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_araddr 
        = vlSelfRef.top__DOT__u_mem__DOT__data_araddr;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__araddr 
        = vlSelfRef.top__DOT__u_mem__DOT__data_araddr;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_araddr 
        = (vlSelfRef.top__DOT__u_mem__DOT__data_araddr 
           - (IData)(0x00002000U));
    vlSelfRef.top__DOT__u_mem__DOT__rd_sel = (3U & 
                                              (((0x00002000U 
                                                 > vlSelfRef.top__DOT__u_mem__DOT__data_araddr)
                                                 ? 1U
                                                 : 
                                                (2U 
                                                 & (- (IData)(
                                                              (0x00022000U 
                                                               > vlSelfRef.top__DOT__u_mem__DOT__data_araddr))))) 
                                               | (- (IData)(
                                                            (vlSelfRef.top__DOT__u_mem__DOT__data_araddr 
                                                             >> 0x0000001fU)))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_hs 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_arvalid) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_arready));
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_awaddr 
        = vlSelfRef.top__DOT__u_mem__DOT__data_awaddr;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__awaddr 
        = vlSelfRef.top__DOT__u_mem__DOT__data_awaddr;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_awaddr 
        = (vlSelfRef.top__DOT__u_mem__DOT__data_awaddr 
           - (IData)(0x00002000U));
    vlSelfRef.top__DOT__u_mem__DOT__wr_sel = (3U & 
                                              (((0x00002000U 
                                                 > vlSelfRef.top__DOT__u_mem__DOT__data_awaddr)
                                                 ? 1U
                                                 : 
                                                (2U 
                                                 & (- (IData)(
                                                              (0x00022000U 
                                                               > vlSelfRef.top__DOT__u_mem__DOT__data_awaddr))))) 
                                               | (- (IData)(
                                                            (vlSelfRef.top__DOT__u_mem__DOT__data_awaddr 
                                                             >> 0x0000001fU)))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__aw_hs 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_awvalid) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_awready));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__w_hs 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wvalid) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wready));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_arvalid 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_arvalid) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_mmio));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_arvalid 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_mmio)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_arvalid));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_awvalid 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awvalid) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_awvalid 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awvalid));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wvalid 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wvalid) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wvalid 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wvalid));
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_enable 
        = ((~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__wb_data_wait) 
               | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__load_fault))) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_reg_write));
    vlSelfRef.top__DOT__u_cpu__DOT__lsu_data_fault 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_fault;
    vlSelfRef.top__DOT__u_cpu__DOT__wb_rd_data = vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__rd_data;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_wstrb 
        = vlSelfRef.top__DOT__u_mem__DOT__data_wstrb;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_wstrb 
        = vlSelfRef.top__DOT__u_mem__DOT__data_wstrb;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__wstrb 
        = vlSelfRef.top__DOT__u_mem__DOT__data_wstrb;
    vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in2_ex_mem 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in2_ex_mem;
    vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in2_mem_wb 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in2_mem_wb;
    vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in1_ex_mem 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in1_ex_mem;
    vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in1_mem_wb 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in1_mem_wb;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_done 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_sent) 
           | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_hs));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_3 = ((1U 
                                                 != (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel)) 
                                                & (2U 
                                                   != (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_now 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__store_req) 
           & ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_q)) 
              & (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__aw_sent) 
                  | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__aw_hs)) 
                 & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__w_sent) 
                    | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__w_hs)))));
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_arvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_arvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__data_arvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_arvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_awvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_awvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__data_awvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_awvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_wvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__data_wvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__wb_rd_data;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__mem_wb_rd_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__wb_rd_data;
    if (vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in2_ex_mem) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in2_ex_mem = 1U;
        vlSelfRef.top__DOT__u_cpu__DOT__fwd_store_data 
            = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result;
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in2_ex_mem = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__fwd_store_data 
            = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in2_mem_wb)
                ? vlSelfRef.top__DOT__u_cpu__DOT__wb_rd_data
                : vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs2_data);
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in2_mem_wb 
        = vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in2_mem_wb;
    if (vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in1_ex_mem) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in1_ex_mem = 1U;
        vlSelfRef.top__DOT__u_cpu__DOT__fwd_jalr_rs1 
            = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result;
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in1_ex_mem = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__fwd_jalr_rs1 
            = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in1_mem_wb)
                ? vlSelfRef.top__DOT__u_cpu__DOT__wb_rd_data
                : vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs1_data);
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in1_mem_wb 
        = vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in1_mem_wb;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_accepted 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_now) 
           | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_q));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__b_out_next 
        = (3U & (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__b_out) 
                  + (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_now)) 
                 - (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__b_hs)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_arvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_arvalid;
    vlSelfRef.top__DOT__data_arvalid = vlSelfRef.top__DOT__u_cpu__DOT__data_arvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_awvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_awvalid;
    vlSelfRef.top__DOT__data_awvalid = vlSelfRef.top__DOT__u_cpu__DOT__data_awvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_wvalid;
    vlSelfRef.top__DOT__data_wvalid = vlSelfRef.top__DOT__u_cpu__DOT__data_wvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_data1 
        = ((((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_enable) 
             & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_addr) 
                == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr1)))
             ? vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_data
             : vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__registers
            [vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr1]) 
           & (- (IData)((0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr1)))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_data2 
        = ((((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_enable) 
             & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_addr) 
                == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr2)))
             ? vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_data
             : vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__registers
            [vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr2]) 
           & (- (IData)((0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr2)))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_rs2_val 
        = vlSelfRef.top__DOT__u_cpu__DOT__fwd_store_data;
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__rs1_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__fwd_jalr_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2 = 0U;
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_bypass) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_out = 0U;
    } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__imm_to_reg) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_out 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__imm;
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
            = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__use_pc)
                ? vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__pc
                : ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in1_ex_mem)
                    ? vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__ex_mem_rd_data
                    : ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in1_mem_wb)
                        ? vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__mem_wb_rd_data
                        : vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__r_data1)));
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2 
            = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__use_imm)
                ? vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__imm
                : ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in2_ex_mem)
                    ? vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__ex_mem_rd_data
                    : ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in2_mem_wb)
                        ? vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__mem_wb_rd_data
                        : vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__r_data2)));
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_out 
            = ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                ? ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                    ? ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                        ? 0U : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                                 ? (VL_LTS_III(32, vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1, vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)
                                     ? 1U : 0U) : (
                                                   (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                                    < vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)
                                                    ? 1U
                                                    : 0U)))
                    : ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                        ? ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                            ? VL_SHIFTRS_III(32,32,5, vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1, 
                                             (0x0000001fU 
                                              & vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2))
                            : (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                               >> (0x0000001fU & vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)))
                        : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                            ? 0U : (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                    << (0x0000001fU 
                                        & vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)))))
                : ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                    ? ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                        ? ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                            ? 0U : (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                    & vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2))
                        : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                            ? (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                               | vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)
                            : (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                               ^ vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)))
                    : ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                        ? 0U : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                                 ? (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                    - vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)
                                 : (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                    + vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)))));
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__store_done 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_accepted) 
           & ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mmio)) 
              | (0U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__b_out_next))));
    vlSelfRef.top__DOT__u_mem__DOT__data_arvalid = vlSelfRef.top__DOT__data_arvalid;
    vlSelfRef.top__DOT__u_mem__DOT__data_awvalid = vlSelfRef.top__DOT__data_awvalid;
    vlSelfRef.top__DOT__u_mem__DOT__data_wvalid = vlSelfRef.top__DOT__data_wvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__rs1_data = vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_data1;
    vlSelfRef.top__DOT__u_cpu__DOT__rs2_data = vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_data2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in1 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pcinc_in1_pcor)
            ? vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__rs1_in
            : vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pc_in);
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__imm_in;
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pc_target 
        = (0xfffffffeU & (vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in1 
                          + vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in2));
    vlSelfRef.top__DOT__u_cpu__DOT__alu_out = vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_out;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__out_zero 
        = (0U == vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_out);
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__mem_stage_busy 
        = (((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__store_done)) 
            & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__store_req)) 
           | ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_done)) 
              & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__load_req)));
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_arvalid = 
        ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_arvalid) 
         & (1U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel)));
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_arvalid = 
        ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_arvalid) 
         & (2U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel)));
    vlSelfRef.top__DOT__u_mem__DOT__ddt_arvalid = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_arvalid) 
                                                   & ((1U 
                                                       != (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel)) 
                                                      & (2U 
                                                         != (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel))));
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_awvalid = 
        ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_awvalid) 
         & (1U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel)));
    vlSelfRef.top__DOT__u_mem__DOT__ddt_awvalid = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_awvalid) 
                                                   & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_3));
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_awvalid = 
        ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_awvalid) 
         & (2U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel)));
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_wvalid = 
        ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_wvalid) 
         & (1U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel)));
    vlSelfRef.top__DOT__u_mem__DOT__ddt_wvalid = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_wvalid) 
                                                  & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_3));
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_wvalid = 
        ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_wvalid) 
         & (2U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs1_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__rs1_data;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs2_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__rs2_data;
    vlSelfRef.top__DOT__u_cpu__DOT__pc_target = vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pc_target;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_result = (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_jal) 
                                                  | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_jalr))
                                                  ? vlSelfRef.top__DOT__u_cpu__DOT__pc_plus4
                                                  : vlSelfRef.top__DOT__u_cpu__DOT__alu_out);
    vlSelfRef.top__DOT__u_cpu__DOT__alu_zero = vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__out_zero;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_stage_busy 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__mem_stage_busy;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_arvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__rom_d_arvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_arvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__ram_d_arvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__arvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__ddt_arvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_awvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__rom_d_awvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__awvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__ddt_awvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_awvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__ram_d_awvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_wvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__rom_d_wvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__wvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__ddt_wvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_wvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__ram_d_wvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_pc 
        = vlSelfRef.top__DOT__u_cpu__DOT__pc_target;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_result 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_result;
    vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__alu_zero 
        = vlSelfRef.top__DOT__u_cpu__DOT__alu_zero;
    vlSelfRef.top__DOT__u_cpu__DOT__data_fetch_valid 
        = (1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_stage_busy)));
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__b_write 
        = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_awvalid) 
           & (IData)(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_wvalid));
    __Vtableidx2 = (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__alu_zero) 
                     << 3U) | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__id_ex_funct3));
    vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__branch_passed 
        = Vtop__ConstPool__TABLE_h50f0aed2_0[__Vtableidx2];
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__data_fetch_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_fetch_valid;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__b_idx 
        = (0x00007fffU & ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__b_write)
                           ? (vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_awaddr 
                              >> 2U) : (vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_araddr 
                                        >> 2U)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__branch_taken 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__is_jal) 
           | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__is_jalr) 
              | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__is_branch) 
                 & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__branch_passed))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__data_fetch_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__data_fetch_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__branch_taken = vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__branch_taken;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_enable = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__mem_wb_enable = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__ex_mem_enable = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect 
        = vlSelfRef.top__DOT__u_cpu__DOT__branch_taken;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__branch_taken 
        = vlSelfRef.top__DOT__u_cpu__DOT__branch_taken;
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__freeze) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_enable 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_enable;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__mem_wb_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_enable 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__mem_wb_enable;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__ex_mem_enable = 0U;
    } else {
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__wb_data_wait) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_enable = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__mem_wb_enable = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__ex_mem_enable = 0U;
        } else if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__data_fetch_valid)))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_enable = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__mem_wb_enable = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__ex_mem_enable = 0U;
        }
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_enable 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_enable;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_enable 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__mem_wb_enable;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__ex_mem_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__ex_mem_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__branch_taken 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__branch_taken;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_id_ex_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_mem_wb_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_ex_mem_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__ex_mem_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_clear = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_branch_flush = 0U;
    if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__freeze)))) {
        if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__wb_data_wait)))) {
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__data_fetch_valid) {
                if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__branch_taken) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_clear = 1U;
                    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_branch_flush = 1U;
                }
            }
        }
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__pc_enable = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_enable = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_clear = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_stall = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_l_use = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_instr = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__is_l_use_no_gap 
        = ((((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_mem_read) 
             & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_reg_write)) 
            & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_rd_not_x0)) 
           & (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_rs1_valid) 
               & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__dep_id_ex_rd_if_id_rs1)) 
              | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_rs2_valid) 
                 & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__dep_id_ex_rd_if_id_rs2))));
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__freeze) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__pc_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_enable = 0U;
    } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__wb_data_wait) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__pc_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_stall = 1U;
    } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__data_fetch_valid) {
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__branch_taken) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_clear = 1U;
        } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__stop_in_flight) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_clear = 1U;
        } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__is_l_use_no_gap) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__pc_enable = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_enable = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_clear = 1U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_stall = 1U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_l_use = 1U;
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_instr = 1U;
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__pc_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_stall = 1U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__stall 
        = (1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__hz_id_ex_enable)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__stall 
        = (1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__hz_mem_wb_enable)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__stall 
        = (1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__hz_ex_mem_enable)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__mem_advance 
        = vlSelfRef.top__DOT__u_cpu__DOT__hz_ex_mem_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_clear 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_branch_flush 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_branch_flush;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__pc_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__pc_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_clear 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_is_stall 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_stall;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_is_l_use 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_l_use;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_is_instr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_instr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_if_id_clear 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_branch_flush 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_branch_flush;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_pc_enable = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__pc_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_id_ex_clear 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_is_stall 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_is_stall;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_is_l_use 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_is_l_use;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_is_instr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_is_instr;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_if_id_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__clear 
        = vlSelfRef.top__DOT__u_cpu__DOT__hz_if_id_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__is_br_flush 
        = vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_branch_flush;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__clear 
        = vlSelfRef.top__DOT__u_cpu__DOT__hz_id_ex_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__is_stall 
        = vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_is_stall;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__is_l_use 
        = vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_is_l_use;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__is_instr 
        = vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_is_instr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__stall 
        = (1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__hz_if_id_enable)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__stall 
        = (1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__hz_if_id_enable)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__stall)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_araddr 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid)
            ? vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_addr
            : ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff)
                ? vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_pc
                : ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pend_valid)
                    ? vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pend_pc
                    : vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_pc)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_redirect = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_pend = 0U;
    if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid)))) {
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_redirect = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff)))) {
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pend_valid) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_pend = 1U;
            }
        }
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__push_stale 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_hold) 
           & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff) 
              | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_stale)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_arvalid 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid) 
           || ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff)
                ? VL_GTS_III(32, 2U, (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__inflight))
                : (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__space)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_cb = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__r_good 
        = ((~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff) 
               | vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale
               [vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_head])) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__r_hs));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__ar_hs 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_arvalid) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_arready));
    vlSelfRef.top__DOT__u_cpu__DOT__if_arvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_arvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__if_araddr = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_r = 0U;
    if ((1U & ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff)) 
               & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__stall))))) {
        if ((0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cap_cnt))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_cb = 1U;
        }
        if ((0U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cap_cnt))) {
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__r_good) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_r = 1U;
            }
        }
    }
    vlSelfRef.top__DOT__if_arvalid = vlSelfRef.top__DOT__u_cpu__DOT__if_arvalid;
    vlSelfRef.top__DOT__if_araddr = vlSelfRef.top__DOT__u_cpu__DOT__if_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_push 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_r)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__r_good));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__fetch_valid 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_cb) 
           | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_r));
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_cb) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__instr_out 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr
            [vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head];
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pc_out 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_pc
            [vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head];
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__mem_fault 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_fault
            [vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head];
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__instr_out 
            = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_r)
                ? vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_rdata
                : 0x00000013U);
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pc_out 
            = (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc
               [vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_head] 
               & (- (IData)((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_r))));
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__mem_fault 
            = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_r) 
               & (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_rresp) 
                   >> 1U) | vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_mis
                  [vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_head]));
    }
    vlSelfRef.top__DOT__u_mem__DOT__if_arvalid = vlSelfRef.top__DOT__if_arvalid;
    vlSelfRef.top__DOT__u_mem__DOT__if_araddr = vlSelfRef.top__DOT__if_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__fetch_valid = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__fetch_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__instr = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__instr_out;
    vlSelfRef.top__DOT__u_cpu__DOT__fetch_pc = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pc_out;
    vlSelfRef.top__DOT__u_cpu__DOT__if_fault_out = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__mem_fault;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_araddr 
        = vlSelfRef.top__DOT__u_mem__DOT__if_araddr;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_araddr 
        = (vlSelfRef.top__DOT__u_mem__DOT__if_araddr 
           - (IData)(0x00002000U));
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__araddr 
        = vlSelfRef.top__DOT__u_mem__DOT__if_araddr;
    vlSelfRef.top__DOT__u_mem__DOT__if_sel = (3U & 
                                              (((0x00002000U 
                                                 > vlSelfRef.top__DOT__u_mem__DOT__if_araddr)
                                                 ? 1U
                                                 : 
                                                (2U 
                                                 & (- (IData)(
                                                              (0x00022000U 
                                                               > vlSelfRef.top__DOT__u_mem__DOT__if_araddr))))) 
                                               | (- (IData)(
                                                            (vlSelfRef.top__DOT__u_mem__DOT__if_araddr 
                                                             >> 0x0000001fU)))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__i_instr 
        = vlSelfRef.top__DOT__u_cpu__DOT__instr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__i_pc 
        = vlSelfRef.top__DOT__u_cpu__DOT__fetch_pc;
    vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__i_fault 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_fault_out;
    vlSelfRef.top__DOT__u_mem__DOT__rom_if_arvalid 
        = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__if_arvalid) 
           & (1U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel)));
    vlSelfRef.top__DOT__u_mem__DOT__ram_if_arvalid 
        = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__if_arvalid) 
           & (2U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel)));
    vlSelfRef.top__DOT__u_mem__DOT__dif_arvalid = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__if_arvalid) 
                                                   & ((1U 
                                                       != (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel)) 
                                                      & (2U 
                                                         != (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel))));
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_arvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__rom_if_arvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_arvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__ram_if_arvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__arvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__dif_arvalid;
}

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtop___024root___eval_phase__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtop___024root___eval_triggers_vec__ico(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vtop___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vtop___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtop___024root___eval_triggers_vec__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_triggers_vec__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (((QData)((IData)(
                                                      (((((((~ (IData)(vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__rst_n)) 
                                                            & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_default_data__DOT__rst_n__0)) 
                                                           << 3U) 
                                                          | (((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__clk) 
                                                              & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_default_data__DOT__clk__0))) 
                                                             << 2U)) 
                                                         | ((((~ (IData)(vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__rst_n)) 
                                                              & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_default_if__DOT__rst_n__0)) 
                                                             << 1U) 
                                                            | ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__clk) 
                                                               & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_default_if__DOT__clk__0))))) 
                                                        << 4U) 
                                                       | (((((~ (IData)(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__rst_n)) 
                                                             & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_ram__DOT__rst_n__0)) 
                                                            << 3U) 
                                                           | (((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__clk) 
                                                               & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_ram__DOT__clk__0))) 
                                                              << 2U)) 
                                                          | ((((~ (IData)(vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__rst_n)) 
                                                               & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_boot_rom__DOT__rst_n__0)) 
                                                              << 1U) 
                                                             | ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__clk) 
                                                                & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__u_boot_rom__DOT__clk__0)))))))) 
                                      << 0x00000020U) 
                                     | (QData)((IData)(
                                                       ((((((((((~ (IData)(vlSelfRef.top__DOT__u_mem__DOT__rst_n)) 
                                                                & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__rst_n__0)) 
                                                               << 3U) 
                                                              | (((IData)(vlSelfRef.top__DOT__u_mem__DOT__clk) 
                                                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_mem__DOT__clk__0))) 
                                                                 << 2U)) 
                                                             | ((((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rst_n)) 
                                                                  & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rst_n__0)) 
                                                                 << 1U) 
                                                                | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__clk) 
                                                                   & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__clk__0))))) 
                                                            << 0x0000000cU) 
                                                           | ((((((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__rst_n)) 
                                                                  & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__rst_n__0)) 
                                                                 << 3U) 
                                                                | (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__clk) 
                                                                    & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__clk__0))) 
                                                                   << 2U)) 
                                                               | ((((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__rst_n)) 
                                                                    & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__rst_n__0)) 
                                                                   << 1U) 
                                                                  | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__clk) 
                                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__clk__0))))) 
                                                              << 8U)) 
                                                          | (((((((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__rst_n)) 
                                                                  & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_meta__DOT__rst_n__0)) 
                                                                 << 3U) 
                                                                | (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__clk) 
                                                                    & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_meta__DOT__clk__0))) 
                                                                   << 2U)) 
                                                               | ((((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__rst_n)) 
                                                                    & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_mem_wb__DOT__rst_n__0)) 
                                                                   << 1U) 
                                                                  | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__clk) 
                                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_mem_wb__DOT__clk__0))))) 
                                                              << 4U) 
                                                             | (((((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rst_n)) 
                                                                   & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rst_n__0)) 
                                                                  << 3U) 
                                                                 | (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__clk) 
                                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_mmio_interface__DOT__clk__0))) 
                                                                    << 2U)) 
                                                                | ((((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rst_n)) 
                                                                     & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_data_decoder__DOT__rst_n__0)) 
                                                                    << 1U) 
                                                                   | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__clk) 
                                                                      & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_data_decoder__DOT__clk__0))))))) 
                                                         << 0x00000010U) 
                                                        | ((((((((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__rst_n)) 
                                                                 & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_lsu__DOT__rst_n__0)) 
                                                                << 3U) 
                                                               | (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__clk) 
                                                                   & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_lsu__DOT__clk__0))) 
                                                                  << 2U)) 
                                                              | ((((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__rst_n)) 
                                                                   & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_ex_mem__DOT__rst_n__0)) 
                                                                  << 1U) 
                                                                 | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__clk) 
                                                                    & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_ex_mem__DOT__clk__0))))) 
                                                             << 0x0000000cU) 
                                                            | ((((((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__rst_n)) 
                                                                   & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_id_ex__DOT__rst_n__0)) 
                                                                  << 3U) 
                                                                 | (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__clk) 
                                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_id_ex__DOT__clk__0))) 
                                                                    << 2U)) 
                                                                | ((((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__rst_n)) 
                                                                     & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_if_id__DOT__rst_n__0)) 
                                                                    << 1U) 
                                                                   | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__clk) 
                                                                      & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_if_id__DOT__clk__0))))) 
                                                               << 8U)) 
                                                           | (((((((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__rst_n)) 
                                                                   & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_fetch__DOT__rst_n__0)) 
                                                                  << 3U) 
                                                                 | (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__clk) 
                                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_fetch__DOT__clk__0))) 
                                                                    << 2U)) 
                                                                | ((((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__rst_n)) 
                                                                     & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_reg_file__DOT__rst_n__0)) 
                                                                    << 1U) 
                                                                   | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__clk) 
                                                                      & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__u_reg_file__DOT__clk__0))))) 
                                                               << 4U) 
                                                              | (((((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__rst_n)) 
                                                                    & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__rst_n__0)) 
                                                                   << 3U) 
                                                                  | (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__clk) 
                                                                      & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__u_cpu__DOT__clk__0))) 
                                                                     << 2U)) 
                                                                 | ((((~ (IData)(vlSelfRef.top__DOT__rst_n)) 
                                                                      & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__rst_n__0)) 
                                                                     << 1U) 
                                                                    | ((IData)(vlSelfRef.top__DOT__cpu_clk) 
                                                                       & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__top__DOT__cpu_clk__0)))))))))));
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

bool Vtop___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_anySet__act\n"); );
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

void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*6:0*/ __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__counter;
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__counter = 0;
    // Body
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__counter 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__counter;
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__rst_n) {
        if ((0x40U <= (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__counter))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__tick = 1U;
            __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__counter = 0U;
        } else {
            __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__counter 
                = (0x0000007fU & ((IData)(1U) + (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__counter)));
            vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__tick = 0U;
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__tick = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__counter = 0U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__counter 
        = __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__counter;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__baud_tick 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__tick;
}

void Vtop___024root___nba_sequent__TOP__1(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__1\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*3:0*/ __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tick_cntr;
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tick_cntr = 0;
    CData/*1:0*/ __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state;
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state = 0;
    CData/*2:0*/ __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_cntr;
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_cntr = 0;
    CData/*7:0*/ __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_reg;
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_reg = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__start_pending;
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__start_pending = 0;
    // Body
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tick_cntr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tick_cntr;
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_cntr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_cntr;
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_reg;
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state;
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__start_pending 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__start_pending;
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__rst_n) {
        if ((0U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state))) {
            __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tick_cntr = 0U;
        } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__baud_tick) {
            __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tick_cntr 
                = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__bit_done)
                    ? 0U : (0x0000000fU & ((IData)(1U) 
                                           + (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tick_cntr))));
        }
        if ((1U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx = 0U;
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__bit_done) {
                __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state = 2U;
                __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_cntr = 0U;
                vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx 
                    = (1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_reg));
            }
        } else if ((2U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx 
                = (1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_reg));
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__bit_done) {
                if ((7U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_cntr))) {
                    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state = 3U;
                    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx = 1U;
                } else {
                    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_reg 
                        = (0x0000007fU & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_reg) 
                                          >> 1U));
                    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_cntr 
                        = (7U & ((IData)(1U) + (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_cntr)));
                    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx 
                        = (1U & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_reg) 
                                 >> 1U));
                }
            }
        } else if ((3U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx = 1U;
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__bit_done) {
                __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state = 0U;
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx = 1U;
            if (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx_start) 
                 & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__start_pending)))) {
                __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_reg 
                    = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx_data;
                __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__start_pending = 1U;
            }
            if (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__start_pending) 
                 & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__baud_tick))) {
                __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state = 1U;
                vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx = 0U;
                __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__start_pending = 0U;
            }
        }
        if ((1U & (~ VL_ONEHOT_I((((3U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state)) 
                                   << 2U) | (((2U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state)) 
                                              << 1U) 
                                             | (1U 
                                                == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state)))))))) {
            if ((0U != (((3U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state)) 
                         << 2U) | (((2U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state)) 
                                    << 1U) | (1U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state)))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: uart_tx.sv:49: Assertion failed in %m: unique case, but multiple matches found for '2'h%X'\n",4, 'M',vlSymsp->name(),"top.u_cpu.u_uart_module.u_uart_tx", 'T',-12
                                 , '#',64,VL_TIME_UNITED_Q(1)
                                 , '#',2,(IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state));
                    VL_STOP_MT("src/design/core/uart_module\\uart_tx.sv", 49, "");
                }
            }
        }
    } else {
        __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tick_cntr = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_cntr = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_reg = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx = 1U;
        __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__start_pending = 0U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tick_cntr 
        = __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tick_cntr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_cntr 
        = __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_cntr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_reg 
        = __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__data_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state 
        = __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__start_pending 
        = __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__start_pending;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx_busy 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__start_pending) 
           | (0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__cur_state)));
    vlSelfRef.top__DOT__u_cpu__DOT__o_tx = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx_busy 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx_busy;
    vlSelfRef.top__DOT__o_tx = vlSelfRef.top__DOT__u_cpu__DOT__o_tx;
    vlSelfRef.top__DOT__u_cpu__DOT__uart_tx_busy = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx_busy;
    vlSelfRef.o_tx = vlSelfRef.top__DOT__o_tx;
}

void Vtop___024root___nba_sequent__TOP__2(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__2\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__stall_count;
    __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__stall_count = 0;
    CData/*1:0*/ __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__boot_mask;
    __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__boot_mask = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__instr_count;
    __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__instr_count = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count;
    __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count;
    __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count = 0;
    // Body
    __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__stall_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__stall_count;
    __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count;
    __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count;
    __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__boot_mask 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__boot_mask;
    __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__instr_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__instr_count;
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__rst_n) {
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__clear) {
            __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__stall_count = 0U;
            __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count = 0U;
            __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count = 0U;
            __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__instr_count = 0U;
        } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__enable) {
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__is_stall) {
                __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__stall_count 
                    = ((IData)(1U) + vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__stall_count);
            }
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__is_l_use) {
                __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count 
                    = ((IData)(1U) + vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count);
            }
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__is_br_flush) {
                __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count 
                    = ((IData)(2U) + vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count);
            }
            if ((((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__is_instr) 
                  & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__post_flush))) 
                 & (0U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__boot_mask)))) {
                __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__instr_count 
                    = ((IData)(1U) + vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__instr_count);
            }
        }
        if ((0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__boot_mask))) {
            __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__boot_mask 
                = (3U & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__boot_mask) 
                         - (IData)(1U)));
        }
    } else {
        __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__stall_count = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__instr_count = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__boot_mask = 2U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__stall_count 
        = __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__stall_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count 
        = __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count 
        = __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__boot_mask 
        = __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__boot_mask;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__instr_count 
        = __Vdly__top__DOT__u_cpu__DOT__u_meta__DOT__instr_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_stall_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__stall_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_l_use_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__l_use_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_br_flush_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__br_flush_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_instr_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__instr_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__post_flush 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__rst_n) 
           && (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__is_br_flush));
    vlSelfRef.top__DOT__u_cpu__DOT__meta_stall_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_stall_count;
    vlSelfRef.top__DOT__u_cpu__DOT__meta_l_use_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_l_use_count;
    vlSelfRef.top__DOT__u_cpu__DOT__meta_br_flush_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_br_flush_count;
    vlSelfRef.top__DOT__u_cpu__DOT__meta_instr_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__meta_instr_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_stall_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__meta_stall_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_l_use_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__meta_l_use_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_br_flush_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__meta_br_flush_count;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_instr_count 
        = vlSelfRef.top__DOT__u_cpu__DOT__meta_instr_count;
}

void Vtop___024root___nba_sequent__TOP__3(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__3\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vdly__top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_start;
    __Vdly__top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_start = 0;
    // Body
    __Vdly__top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_start 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_start;
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rst_n) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_ack = 0U;
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_arvalid) {
            if ((4U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_ack = 1U;
            }
            vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rresp 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_resp;
            vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rdata 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_val;
        }
        vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_meta_control 
            = (0xfeU & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_meta_control));
        __Vdly__top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_start = 0U;
        if (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_awvalid) 
             & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wvalid))) {
            if ((8U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__wr_word)) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_bresp = 0U;
                if ((1U & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wstrb) 
                           & (~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_busy) 
                                 | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_start)))))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_uart_tx_data 
                        = (0x000000ffU & vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wdata);
                    __Vdly__top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_start = 1U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_bresp 
                    = ((0x00001000U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__wr_word)
                        ? 0U : 2U);
            }
            if ((8U != vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__wr_word)) {
                if ((0x00001000U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__wr_word)) {
                    if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wstrb))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_meta_control 
                            = (0x000000ffU & vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wdata);
                    }
                }
            }
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_ack = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_bresp = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_meta_control = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_start = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_uart_tx_data = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rresp = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rdata = 0U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_bvalid 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rst_n) 
           && ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_awvalid) 
               & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wvalid)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rvalid 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rst_n) 
           && (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_arvalid));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_start 
        = __Vdly__top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_start;
    vlSelfRef.top__DOT__u_cpu__DOT__uart_rx_ack = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_ack;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_bresp = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_bresp;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_enable 
        = (1U & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_meta_control) 
                 >> 1U));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_clear 
        = (1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_meta_control));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_uart_tx_data;
    vlSelfRef.top__DOT__u_cpu__DOT__uart_tx_start = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_start;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_rresp = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rresp;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_bvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_bvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_rvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_rdata = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_rdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rx_ack 
        = vlSelfRef.top__DOT__u_cpu__DOT__uart_rx_ack;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_bresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_bresp;
    vlSelfRef.top__DOT__u_cpu__DOT__meta_enable = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__meta_clear = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__uart_tx_data = vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_data;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx_start 
        = vlSelfRef.top__DOT__u_cpu__DOT__uart_tx_start;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_rresp;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_bvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_bvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_rdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__meta_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__clear 
        = vlSelfRef.top__DOT__u_cpu__DOT__meta_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__uart_tx_data;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx_start 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx_start;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tx_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__tx_data;
}

void Vtop___024root___nba_sequent__TOP__4(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__4\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*1:0*/ __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state;
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state = 0;
    CData/*2:0*/ __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_cntr;
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_cntr = 0;
    CData/*3:0*/ __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter;
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter = 0;
    // Body
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state;
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_cntr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_cntr;
    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter;
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rst_n) {
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_ack) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_valid = 0U;
        }
        if ((1U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state))) {
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__baud_tick) {
                if ((7U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter))) {
                    if (vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_sync) {
                        __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state = 0U;
                    } else {
                        __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state = 2U;
                        __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_cntr = 0U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_valid = 0U;
                    }
                }
                __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter 
                    = ((0x0fU == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter))
                        ? 0U : (0x0000000fU & ((IData)(1U) 
                                               + (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter))));
            }
        } else if ((2U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state))) {
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__baud_tick) {
                if ((7U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter))) {
                    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_cntr 
                        = (7U & ((IData)(1U) + (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_cntr)));
                    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_reg 
                        = (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_sync) 
                            << 7U) | (0x0000007fU & 
                                      ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_reg) 
                                       >> 1U)));
                    if ((7U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_cntr))) {
                        __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state = 3U;
                    }
                }
                __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter 
                    = ((0x0fU == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter))
                        ? 0U : (0x0000000fU & ((IData)(1U) 
                                               + (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter))));
            }
        } else if ((3U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state))) {
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__baud_tick) {
                if ((7U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter))) {
                    if (vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_sync) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_valid = 1U;
                    }
                    __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state = 0U;
                }
                __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter 
                    = ((0x0fU == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter))
                        ? 0U : (0x0000000fU & ((IData)(1U) 
                                               + (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter))));
            }
        } else if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_sync)))) {
            __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter = 0U;
            __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state = 1U;
        }
        if ((1U & (~ VL_ONEHOT_I((((3U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state)) 
                                   << 2U) | (((2U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state)) 
                                              << 1U) 
                                             | (1U 
                                                == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state)))))))) {
            if ((0U != (((3U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state)) 
                         << 2U) | (((2U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state)) 
                                    << 1U) | (1U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state)))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: uart_rx.sv:54: Assertion failed in %m: unique case, but multiple matches found for '2'h%X'\n",4, 'M',vlSymsp->name(),"top.u_cpu.u_uart_module.u_uart_rx", 'T',-12
                                 , '#',64,VL_TIME_UNITED_Q(1)
                                 , '#',2,(IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state));
                    VL_STOP_MT("src/design/core/uart_module\\uart_rx.sv", 54, "");
                }
            }
        }
    } else {
        __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_reg = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_cntr = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_valid = 0U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state 
        = __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__cur_state;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_cntr 
        = __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_cntr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter 
        = __Vdly__top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__tick_counter;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__data_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rx_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_sync 
        = ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rst_n))) 
           || (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_meta));
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rx_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_data;
    vlSelfRef.top__DOT__u_cpu__DOT__uart_rx_valid = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rx_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__uart_rx_data = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rx_data;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__uart_rx_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_meta 
        = ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rst_n))) 
           || (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__uart_rx_data;
}

void Vtop___024root___nba_sequent__TOP__5(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__5\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__rst_sync = ((IData)(vlSelfRef.top__DOT__rst_n)
                                     ? (1U | (2U & 
                                              ((IData)(vlSelfRef.top__DOT__rst_sync) 
                                               << 1U)))
                                     : 0U);
    vlSelfRef.top__DOT__core_rst_n = (1U & ((IData)(vlSelfRef.top__DOT__rst_sync) 
                                            >> 1U));
}

void Vtop___024root___nba_sequent__TOP__6(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__6\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__0__Vfuncout;
    __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__0__Vfuncout = 0;
    CData/*0:0*/ __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__0__p;
    __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__0__p = 0;
    CData/*0:0*/ __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__1__Vfuncout;
    __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__1__Vfuncout = 0;
    CData/*0:0*/ __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__1__p;
    __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__1__p = 0;
    CData/*0:0*/ __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__2__Vfuncout;
    __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__2__Vfuncout = 0;
    CData/*0:0*/ __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__2__p;
    __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__2__p = 0;
    CData/*0:0*/ __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__3__Vfuncout;
    __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__3__Vfuncout = 0;
    CData/*0:0*/ __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__3__p;
    __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__3__p = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid;
    __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head;
    __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__af_head;
    __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__af_head = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_tail;
    __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_tail = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__req_pc;
    __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__req_pc = 0;
    CData/*0:0*/ __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v0;
    __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v0 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc__v0;
    __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc__v0 = 0;
    CData/*0:0*/ __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc__v0;
    __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc__v0 = 0;
    CData/*0:0*/ __VdlySet__top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc__v0;
    __VdlySet__top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc__v0 = 0;
    CData/*0:0*/ __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__af_mis__v0;
    __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__af_mis__v0 = 0;
    CData/*0:0*/ __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_mis__v0;
    __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_mis__v0 = 0;
    CData/*0:0*/ __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v1;
    __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v1 = 0;
    CData/*0:0*/ __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v1;
    __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v1 = 0;
    CData/*0:0*/ __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v2;
    __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v2 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr__v0;
    __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr__v0 = 0;
    CData/*0:0*/ __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr__v0;
    __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr__v0 = 0;
    CData/*0:0*/ __VdlySet__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr__v0;
    __VdlySet__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr__v0 = 0;
    IData/*31:0*/ __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_pc__v0;
    __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_pc__v0 = 0;
    CData/*0:0*/ __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_pc__v0;
    __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_pc__v0 = 0;
    CData/*0:0*/ __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_fault__v0;
    __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_fault__v0 = 0;
    CData/*0:0*/ __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_fault__v0;
    __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_fault__v0 = 0;
    // Body
    __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head;
    __VdlySet__top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc__v0 = 0U;
    __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_tail 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_tail;
    __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid;
    __VdlySet__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr__v0 = 0U;
    __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__af_head 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_head;
    __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__req_pc 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_pc;
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__rst_n) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__inflight 
            = (3U & (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__inflight) 
                      + (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__ar_hs)) 
                     - (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__r_hs)));
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff) {
            __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head = 0U;
        } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_cb) {
            __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__2__p 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head;
            __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__2__Vfuncout 
                = (1U & ((~ (IData)(__Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__2__p)) 
                         & ((IData)(1U) + (IData)(__Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__2__p))));
            __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head 
                = __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__2__Vfuncout;
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__inflight = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head = 0U;
    }
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__rst_n) {
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__unnamedblk2__DOT__i = 0U;
            while (VL_GTS_III(32, 2U, vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__unnamedblk2__DOT__i)) {
                __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v0 
                    = (1U & vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__unnamedblk2__DOT__i);
                vlSelfRef.__VdlyCommitQueuetop__DOT__u_cpu__DOT__u_fetch__DOT__af_stale.enqueue(1U, (IData)(__VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v0));
                vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__unnamedblk2__DOT__i 
                    = ((IData)(1U) + vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__unnamedblk2__DOT__i);
            }
        }
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__ar_hs) {
            __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc__v0 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_araddr;
            __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc__v0 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_tail;
            __VdlySet__top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc__v0 = 1U;
            __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__af_mis__v0 
                = (0U != (3U & vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_araddr));
            __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_mis__v0 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_tail;
            __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v1 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__push_stale;
            __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v1 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_tail;
            vlSelfRef.__VdlyCommitQueuetop__DOT__u_cpu__DOT__u_fetch__DOT__af_stale.enqueue(__VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v1, (IData)(__VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v1));
            __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__0__p 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_tail;
            __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__0__Vfuncout 
                = (1U & ((~ (IData)(__Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__0__p)) 
                         & ((IData)(1U) + (IData)(__Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__0__p))));
            vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_tail 
                = __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__0__Vfuncout;
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__unnamedblk1__DOT__i = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_tail = 0U;
        while (VL_GTS_III(32, 2U, vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__unnamedblk1__DOT__i)) {
            __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v2 
                = (1U & vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__unnamedblk1__DOT__i);
            vlSelfRef.__VdlyCommitQueuetop__DOT__u_cpu__DOT__u_fetch__DOT__af_stale.enqueue(0U, (IData)(__VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale__v2));
            vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__unnamedblk1__DOT__i 
                = ((IData)(1U) + vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__unnamedblk1__DOT__i);
        }
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head 
        = __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head;
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__rst_n) {
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cap_cnt = 0U;
            __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_tail = 0U;
            if (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__ar_hs) 
                 & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_redirect))) {
                __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__req_pc 
                    = ((IData)(4U) + vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_pc);
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cap_cnt 
                = (3U & (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cap_cnt) 
                          + (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_push)) 
                         - (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_cb)));
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_push) {
                __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr__v0 
                    = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_rdata;
                __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr__v0 
                    = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_tail;
                __VdlySet__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr__v0 = 1U;
                __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_pc__v0 
                    = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc
                    [vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_head];
                __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_pc__v0 
                    = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_tail;
                __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_fault__v0 
                    = (1U & (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_rresp) 
                              >> 1U) | vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_mis
                             [vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_head]));
                __VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_fault__v0 
                    = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_tail;
                __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__3__p 
                    = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_tail;
                __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__3__Vfuncout 
                    = (1U & ((~ (IData)(__Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__3__p)) 
                             & ((IData)(1U) + (IData)(__Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__3__p))));
                __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_tail 
                    = __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__3__Vfuncout;
            }
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__ar_hs) {
                if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_hold) {
                    if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_stale)))) {
                        __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__req_pc 
                            = ((IData)(4U) + vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_addr);
                    }
                } else {
                    __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__req_pc 
                        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_pend)
                            ? ((IData)(4U) + vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pend_pc)
                            : ((IData)(4U) + vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_pc));
                }
            }
        }
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__r_hs) {
            __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__1__p 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_head;
            __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__1__Vfuncout 
                = (1U & ((~ (IData)(__Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__1__p)) 
                         & ((IData)(1U) + (IData)(__Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__1__p))));
            __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__af_head 
                = __Vfunc_top__DOT__u_cpu__DOT__u_fetch__DOT__ptr_inc__1__Vfuncout;
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cap_cnt = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__af_head = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_tail = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__req_pc = 0U;
    }
    vlSelfRef.__VdlyCommitQueuetop__DOT__u_cpu__DOT__u_fetch__DOT__af_stale.commit(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale);
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__rst_n) {
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff) {
            if ((1U & (~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__ar_hs) 
                          & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_redirect))))) {
                if ((1U & (~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_arvalid) 
                              & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_redirect))))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pend_pc 
                        = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_pc;
                }
            }
            vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pend_valid 
                = ((1U & (~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__ar_hs) 
                             & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_redirect)))) 
                   && (1U & (~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_arvalid) 
                                & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_redirect)))));
        } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__ar_hs) {
            if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_hold)))) {
                if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_pend) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pend_valid = 0U;
                }
            }
        } else if ((((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_arvalid) 
                     & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_pend)) 
                    & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid)))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pend_valid = 0U;
        }
        if (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_arvalid) 
             & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_arready)))) {
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid) {
                if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_stale = 1U;
                }
            } else {
                __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid = 1U;
                vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_addr 
                    = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_araddr;
                vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_stale = 0U;
            }
        } else if (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__ar_hs) 
                    & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_hold))) {
            __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid = 0U;
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pend_pc = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pend_valid = 0U;
        __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_addr = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_stale = 0U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_tail 
        = __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_tail;
    if (__VdlySet__top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc__v0) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc[__VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc__v0] 
            = __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc__v0;
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_mis[__VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__af_mis__v0] 
            = __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__af_mis__v0;
    }
    if (__VdlySet__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr__v0) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr[__VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr__v0] 
            = __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr__v0;
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_pc[__VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_pc__v0] 
            = __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_pc__v0;
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_fault[__VdlyDim0__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_fault__v0] 
            = __VdlyVal__top__DOT__u_cpu__DOT__u_fetch__DOT__cb_fault__v0;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_head 
        = __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__af_head;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_pc 
        = __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__req_pc;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__space 
        = VL_GTS_III(32, 2U, ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cap_cnt) 
                              + (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__inflight)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid 
        = __Vdly__top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_hold = 0U;
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_hold = 1U;
    }
}

extern const VlUnpacked<CData/*3:0*/, 32> Vtop__ConstPool__TABLE_hf1e08178_0;
extern const VlUnpacked<CData/*0:0*/, 32> Vtop__ConstPool__TABLE_h7037940f_0;
extern const VlUnpacked<CData/*0:0*/, 32> Vtop__ConstPool__TABLE_h50c17034_0;
extern const VlUnpacked<CData/*0:0*/, 32> Vtop__ConstPool__TABLE_h18b58e87_0;
extern const VlUnpacked<CData/*0:0*/, 32> Vtop__ConstPool__TABLE_h90f66a13_0;

void Vtop___024root___nba_sequent__TOP__7(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__7\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*4:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_cpu__DOT__wb_cap_valid;
    __Vdly__top__DOT__u_cpu__DOT__wb_cap_valid = 0;
    // Body
    __Vdly__top__DOT__u_cpu__DOT__wb_cap_valid = vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_valid;
    if (vlSelfRef.top__DOT__u_cpu__DOT__rst_n) {
        if (vlSelfRef.top__DOT__u_cpu__DOT__hz_mem_wb_enable) {
            __Vdly__top__DOT__u_cpu__DOT__wb_cap_valid = 0U;
        } else if ((((IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_mem_to_reg) 
                     & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__data_rvalid_in)) 
                    & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_valid)))) {
            __Vdly__top__DOT__u_cpu__DOT__wb_cap_valid = 1U;
            vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_data 
                = vlSelfRef.top__DOT__u_cpu__DOT__data_rdata_in;
            vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_resp 
                = vlSelfRef.top__DOT__u_cpu__DOT__data_rresp_in;
        }
    } else {
        __Vdly__top__DOT__u_cpu__DOT__wb_cap_valid = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_data = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_resp = 0U;
    }
    __Vtableidx1 = ((((IData)(vlSelfRef.top__DOT__u_cpu__DOT__lsu_data_fault) 
                      << 4U) | (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_illegal) 
                                 << 3U) | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_if_fault) 
                                           << 2U))) 
                    | (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_stop) 
                        << 1U) | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__rst_n)));
    if ((1U & Vtop__ConstPool__TABLE_hf1e08178_0[__Vtableidx1])) {
        vlSelfRef.top__DOT__u_cpu__DOT__stop_q = Vtop__ConstPool__TABLE_h7037940f_0
            [__Vtableidx1];
    }
    if ((2U & Vtop__ConstPool__TABLE_hf1e08178_0[__Vtableidx1])) {
        vlSelfRef.top__DOT__u_cpu__DOT__instr_fault_q 
            = Vtop__ConstPool__TABLE_h50c17034_0[__Vtableidx1];
    }
    if ((4U & Vtop__ConstPool__TABLE_hf1e08178_0[__Vtableidx1])) {
        vlSelfRef.top__DOT__u_cpu__DOT__illegal_q = Vtop__ConstPool__TABLE_h18b58e87_0
            [__Vtableidx1];
    }
    if ((8U & Vtop__ConstPool__TABLE_hf1e08178_0[__Vtableidx1])) {
        vlSelfRef.top__DOT__u_cpu__DOT__data_fault_q 
            = Vtop__ConstPool__TABLE_h90f66a13_0[__Vtableidx1];
    }
    vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_valid = __Vdly__top__DOT__u_cpu__DOT__wb_cap_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__stop = vlSelfRef.top__DOT__u_cpu__DOT__stop_q;
    vlSelfRef.top__DOT__u_cpu__DOT__instr_fault_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__instr_fault_q;
    vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__illegal_q;
    vlSelfRef.top__DOT__u_cpu__DOT__data_fault_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_fault_q;
    vlSelfRef.top__DOT__u_cpu__DOT__halt = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__instr_fault_q) 
                                            | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__data_fault_q) 
                                               | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__illegal_q)));
    vlSelfRef.top__DOT__stop = vlSelfRef.top__DOT__u_cpu__DOT__stop;
    vlSelfRef.top__DOT__instr_fault = vlSelfRef.top__DOT__u_cpu__DOT__instr_fault_out;
    vlSelfRef.top__DOT__illegal_instr = vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr_out;
    vlSelfRef.top__DOT__data_fault = vlSelfRef.top__DOT__u_cpu__DOT__data_fault_out;
    vlSelfRef.top__DOT__halt = vlSelfRef.top__DOT__u_cpu__DOT__halt;
    vlSelfRef.top__DOT__u_cpu__DOT__freeze = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__halt) 
                                              | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__stop_q));
    vlSelfRef.top__DOT__led = ((((IData)(vlSelfRef.top__DOT__illegal_instr) 
                                 << 3U) | ((IData)(vlSelfRef.top__DOT__data_fault) 
                                           << 2U)) 
                               | (((IData)(vlSelfRef.top__DOT__instr_fault) 
                                   << 1U) | (IData)(vlSelfRef.top__DOT__stop)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__freeze 
        = vlSelfRef.top__DOT__u_cpu__DOT__freeze;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__freeze 
        = vlSelfRef.top__DOT__u_cpu__DOT__freeze;
    vlSelfRef.led = vlSelfRef.top__DOT__led;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__freeze 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__freeze;
}

void Vtop___024root___nba_sequent__TOP__8(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__8\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__bvalid = 0U;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__rvalid 
        = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__rst_n) 
           && (IData)(vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__arvalid));
    vlSelfRef.top__DOT__u_mem__DOT__dif_bvalid = vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__bvalid;
    vlSelfRef.top__DOT__u_mem__DOT__dif_rvalid = vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__rvalid;
}

void Vtop___024root___nba_sequent__TOP__9(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__9\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_7;
    __VdfgRegularize_h6e95ff9d_0_7 = 0;
    // Body
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__rst_n) {
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__clear) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__o_pc = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__o_fault = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__o_instr = 0x00000013U;
        } else if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__stall)))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__o_pc 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__i_pc;
            vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__o_fault 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__i_fault;
            vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__o_instr 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__i_instr;
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__o_pc = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__o_fault = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__o_instr = 0x00000013U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__if_id_pc = vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__o_pc;
    vlSelfRef.top__DOT__u_cpu__DOT__if_id_fault = vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__o_fault;
    vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr = vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__o_instr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr;
    vlSelfRef.top__DOT__u_cpu__DOT__if_id_rs1_addr 
        = (0x0000001fU & (vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr 
                          >> 0x0000000fU));
    vlSelfRef.top__DOT__u_cpu__DOT__if_id_rs2_addr 
        = (0x0000001fU & (vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr 
                          >> 0x00000014U));
    vlSelfRef.top__DOT__u_cpu__DOT__if_id_opcode = 
        (0x0000007fU & vlSelfRef.top__DOT__u_cpu__DOT__if_id_instr);
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__rd_addr 
        = (0x0000001fU & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                          >> 7U));
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__rs1_addr 
        = (0x0000001fU & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                          >> 0x0000000fU));
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__rs2_addr 
        = (0x0000001fU & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                          >> 0x00000014U));
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3 
        = (7U & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                 >> 0x0000000cU));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_id_rs1_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_id_rs2_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_opcode 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_id_opcode;
    vlSelfRef.top__DOT__u_cpu__DOT__rdst_addr = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__rs1_addr = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__rs1_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__rs2_addr = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__rs2_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__funct3 = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode 
        = (0x0000007fU & vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr);
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in1_ropc = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in2_roi = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_bypass = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_write = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_read = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_op = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_to_reg = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_to_reg = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__pcinc_in1_pcor = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_branch = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_jal = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_jalr = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 5U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__stop = 0U;
    if ((0x00000040U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        if ((0x00000020U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((0x00000010U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_bypass = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 0U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__stop = 1U;
                    } else {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                        if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 1U;
                            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in1_ropc = 1U;
                            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 4U;
                            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_jal = 1U;
                        } else {
                            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                        }
                    } else {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in1_ropc = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__pcinc_in1_pcor = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 0U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_jalr = 1U;
                        if ((0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))) {
                            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                        }
                    } else {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in2_roi = 0U;
                    if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_op 
                            = ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                ? 0x0cU : 0x0dU);
                    } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_op = 0U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                    } else {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_op = 4U;
                    }
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 2U;
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_branch = 1U;
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        }
    } else if ((0x00000020U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        if ((0x00000010U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_to_reg = 1U;
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 3U;
                    } else {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__4__return_op 
                        = ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                            ? ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                ? ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                    ? 6U : 5U) : ((1U 
                                                   & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                                   ? 
                                                  ((0x40000000U 
                                                    & vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr)
                                                    ? 0x0bU
                                                    : 0x0aU)
                                                   : 4U))
                            : ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                ? ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                    ? 0x0cU : 0x0dU)
                                : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                    ? 8U : ((0x40000000U 
                                             & vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr)
                                             ? 1U : 0U))));
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 1U;
                    vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__4__Vfuncout 
                        = vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__4__return_op;
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in2_roi = 0U;
                    if ((1U & (~ ((0U == (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                                          >> 0x19U)) 
                                  | ((0x20U == (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                                                >> 0x19U)) 
                                     & ((0U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3)) 
                                        | (5U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3)))))))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                    }
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_op 
                        = vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__4__Vfuncout;
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            }
        } else if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_write = 1U;
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 1U;
                if ((2U < (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        }
    } else if ((0x00000010U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 1U;
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in1_ropc = 1U;
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 3U;
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            }
        } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__5__return_op 
                    = ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                        ? ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                            ? ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                ? 6U : 5U) : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                               ? ((0x40000000U 
                                                   & vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr)
                                                   ? 0x0bU
                                                   : 0x0aU)
                                               : 4U))
                        : ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                            ? ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                                ? 0x0cU : 0x0dU) : 
                           ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))
                             ? 8U : 0U)));
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 1U;
                vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__5__Vfuncout 
                    = vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__5__return_op;
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 0U;
                if ((((1U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3)) 
                      & (0U != (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                                >> 0x19U))) | (((5U 
                                                 == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3)) 
                                                & (0U 
                                                   != 
                                                   (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                                                    >> 0x19U))) 
                                               & (0x20U 
                                                  != 
                                                  (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr 
                                                   >> 0x19U))))) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_op 
                    = vlSelfRef.__Vfunc_top__DOT__u_cpu__DOT__u_decoder__DOT__calc_alu_op__5__Vfuncout;
                if ((0x00000013U == vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__instr)) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 0U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        }
    } else if ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
                    if ((0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))) {
                        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                    }
                } else {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
                }
            } else {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        }
    } else if ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
    } else if ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
        if ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__opcode))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write = 1U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_to_reg = 1U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_read = 1U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type = 0U;
            if ((((3U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3)) 
                  | (6U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3))) 
                 | (7U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__funct3)))) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
            }
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr = 1U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_opcode;
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr1 
        = vlSelfRef.top__DOT__u_cpu__DOT__rs1_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr2 
        = vlSelfRef.top__DOT__u_cpu__DOT__rs2_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__alu_in1_sel = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in1_ropc;
    vlSelfRef.top__DOT__u_cpu__DOT__alu_in2_sel = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_in2_roi;
    vlSelfRef.top__DOT__u_cpu__DOT__alu_bypass = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_bypass;
    vlSelfRef.top__DOT__u_cpu__DOT__alu_op = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__alu_op;
    vlSelfRef.top__DOT__u_cpu__DOT__imm_to_reg = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__pc_in1_sel = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__pcinc_in1_pcor;
    vlSelfRef.top__DOT__u_cpu__DOT__d_stop = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__stop;
    vlSelfRef.top__DOT__u_cpu__DOT__reg_w_enable = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_write = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_write;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_read = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_read;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_to_reg = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__mem_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__d_is_branch = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_branch;
    vlSelfRef.top__DOT__u_cpu__DOT__d_is_jal = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_jal;
    vlSelfRef.top__DOT__u_cpu__DOT__d_is_jalr = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__is_jalr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_type 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_type;
    vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr_fault 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__illegal_instr;
    __VdfgRegularize_h6e95ff9d_0_7 = ((0x33U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode)) 
                                      | ((0x23U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode)) 
                                         | (0x63U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_out 
        = ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_type))
            ? ((- (IData)((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_type))))) 
               & ((((- (IData)((vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                >> 0x0000001fU))) << 0x00000014U) 
                   | ((((0x000001feU & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                        >> 0x0000000bU)) 
                        | (1U & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                 >> 0x00000014U))) 
                       << 0x0000000bU) | (0x000007feU 
                                          & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                             >> 0x00000014U)))) 
                  & (- (IData)((1U & (~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_type) 
                                         >> 1U)))))))
            : ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_type))
                ? ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_type))
                    ? (0xfffff000U & vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr)
                    : (((- (IData)((vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                    >> 0x0000001fU))) 
                        << 0x0000000cU) | ((0x00000800U 
                                            & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                               << 4U)) 
                                           | ((0x000007e0U 
                                               & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                                  >> 0x00000014U)) 
                                              | (0x0000001eU 
                                                 & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                                    >> 7U))))))
                : (((- (IData)((vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                >> 0x0000001fU))) << 0x0000000bU) 
                   | (0x000007ffU & ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_type))
                                      ? ((0x000007e0U 
                                          & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                             >> 0x00000014U)) 
                                         | (0x0000001fU 
                                            & (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                               >> 7U)))
                                      : (vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__instr 
                                         >> 0x00000014U))))));
    vlSelfRef.top__DOT__u_cpu__DOT__id_kill = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__illegal_instr_fault) 
                                               | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__if_id_fault));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs2_valid 
        = __VdfgRegularize_h6e95ff9d_0_7;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs1_valid 
        = ((IData)(__VdfgRegularize_h6e95ff9d_0_7) 
           | ((0x13U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode)) 
              | ((3U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode)) 
                 | ((0x67U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode)) 
                    | (0x73U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_opcode))))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_val 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__u_imm_gen__DOT__imm_out;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs2_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs2_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs1_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs1_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__imm_val = vlSelfRef.top__DOT__u_cpu__DOT__u_decoder__DOT__imm_val;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_rs2_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs2_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_rs1_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_rs1_valid;
}

void Vtop___024root___nba_sequent__TOP__10(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__10\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*7:0*/ __VdlyVal__top__DOT__u_mem__DOT__u_ram__DOT__container__v0;
    __VdlyVal__top__DOT__u_mem__DOT__u_ram__DOT__container__v0 = 0;
    CData/*4:0*/ __VdlyLsb__top__DOT__u_mem__DOT__u_ram__DOT__container__v0;
    __VdlyLsb__top__DOT__u_mem__DOT__u_ram__DOT__container__v0 = 0;
    SData/*14:0*/ __VdlyDim0__top__DOT__u_mem__DOT__u_ram__DOT__container__v0;
    __VdlyDim0__top__DOT__u_mem__DOT__u_ram__DOT__container__v0 = 0;
    IData/*31:0*/ __VdlyMask__top__DOT__u_mem__DOT__u_ram__DOT__container__v0;
    __VdlyMask__top__DOT__u_mem__DOT__u_ram__DOT__container__v0 = 0;
    IData/*31:0*/ __VdlyElem__top__DOT__u_mem__DOT__u_ram__DOT__container__v0;
    __VdlyElem__top__DOT__u_mem__DOT__u_ram__DOT__container__v0 = 0;
    // Body
    if (vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__b_write) {
        vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__unnamedblk1__DOT__i = 0U;
        while (VL_GTS_III(32, 4U, vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__unnamedblk1__DOT__i)) {
            if ((1U & ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_wstrb) 
                       >> (3U & vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__unnamedblk1__DOT__i)))) {
                __VdlyVal__top__DOT__u_mem__DOT__u_ram__DOT__container__v0 
                    = (0x000000ffU & (vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_wdata 
                                      >> (0x0000001fU 
                                          & VL_MULS_III(32, (IData)(8U), vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__unnamedblk1__DOT__i))));
                __VdlyLsb__top__DOT__u_mem__DOT__u_ram__DOT__container__v0 
                    = (0x0000001fU & VL_MULS_III(32, (IData)(8U), vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__unnamedblk1__DOT__i));
                __VdlyDim0__top__DOT__u_mem__DOT__u_ram__DOT__container__v0 
                    = vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__b_idx;
                __VdlyMask__top__DOT__u_mem__DOT__u_ram__DOT__container__v0 = 0U;
                __VdlyMask__top__DOT__u_mem__DOT__u_ram__DOT__container__v0 
                    = (__VdlyMask__top__DOT__u_mem__DOT__u_ram__DOT__container__v0 
                       | (0x00000000ffffffffULL & ((IData)(0xffU) 
                                                   << (IData)(__VdlyLsb__top__DOT__u_mem__DOT__u_ram__DOT__container__v0))));
                __VdlyElem__top__DOT__u_mem__DOT__u_ram__DOT__container__v0 = 0U;
                __VdlyElem__top__DOT__u_mem__DOT__u_ram__DOT__container__v0 
                    = (((~ ((IData)(0x000000ffU) << (IData)(__VdlyLsb__top__DOT__u_mem__DOT__u_ram__DOT__container__v0))) 
                        & __VdlyElem__top__DOT__u_mem__DOT__u_ram__DOT__container__v0) 
                       | (0x00000000ffffffffULL & ((IData)(__VdlyVal__top__DOT__u_mem__DOT__u_ram__DOT__container__v0) 
                                                   << (IData)(__VdlyLsb__top__DOT__u_mem__DOT__u_ram__DOT__container__v0))));
                vlSelfRef.__VdlyCommitQueuetop__DOT__u_mem__DOT__u_ram__DOT__container.enqueue(__VdlyElem__top__DOT__u_mem__DOT__u_ram__DOT__container__v0, __VdlyMask__top__DOT__u_mem__DOT__u_ram__DOT__container__v0, (IData)(__VdlyDim0__top__DOT__u_mem__DOT__u_ram__DOT__container__v0));
            }
            vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__unnamedblk1__DOT__i 
                = ((IData)(1U) + vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__unnamedblk1__DOT__i);
        }
    }
    if (vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_arvalid) {
        vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_rdata 
            = vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__container
            [(0x00007fffU & (vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_araddr 
                             >> 2U))];
    }
    if (vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_arvalid) {
        vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_rdata 
            = vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__container
            [vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__b_idx];
    }
    vlSelfRef.__VdlyCommitQueuetop__DOT__u_mem__DOT__u_ram__DOT__container.commit(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__container);
    vlSelfRef.top__DOT__u_mem__DOT__ram_if_rdata = vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_rdata;
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_rdata = vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_rdata;
}

void Vtop___024root___nba_sequent__TOP__11(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__11\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__rst_n) {
        if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__stall)))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_mem_to_reg 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_mem_to_reg;
            vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_rs2_val 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_rs2_val;
            vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_is_stop 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_is_stop;
            vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_reg_write 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_reg_write;
            vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_rd_addr 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_rd_addr;
            vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_funct3 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_funct3;
            vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_mem_read 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_mem_read;
            vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_mem_write 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_mem_write;
            vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_result 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_result;
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_mem_to_reg = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_rs2_val = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_is_stop = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_reg_write = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_rd_addr = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_funct3 = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_mem_read = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_mem_write = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_result = 0U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_mem_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_rs2_val 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_rs2_val;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_stop = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_is_stop;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_rd_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3 = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_read 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_mem_read;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_mem_write;
    vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result = vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__o_result;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__rs2_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_rs2_val;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__ex_mem_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__ex_mem_rd 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__funct3 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_read 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_read;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__ex_mem_rd_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__ex_mem_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__ex_mem_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__ex_mem_rd 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__ex_mem_rd;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__size_mask 
        = ((0U == (3U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__funct3)))
            ? 1U : (0x0000000fU & (3U | (- (IData)(
                                                   (1U 
                                                    != 
                                                    (3U 
                                                     & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__funct3))))))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_access 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_read) 
           | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_write));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wdata 
        = (vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__rs2_in 
           << (0x00000018U & (vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res 
                              << 3U)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_araddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_awaddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__misaligned 
        = ((0U != (3U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__funct3))) 
           & ((1U == (3U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__funct3)))
               ? (3U == (3U & vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res))
               : (0U != (3U & vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__region 
        = (3U & (((0x00002000U > vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res)
                   ? 1U : (2U & (- (IData)((0x00022000U 
                                            > vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res))))) 
                 | (- (IData)((vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res 
                               >> 0x0000001fU)))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wstrb 
        = (0x0000000fU & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__size_mask) 
                          << (3U & vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__alu_res)));
    vlSelfRef.top__DOT__u_cpu__DOT__data_wdata_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__data_araddr_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__data_awaddr_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_awaddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mmio 
        = (3U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__region));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__pre_fault 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_access) 
           & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__misaligned) 
              | ((0U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__region)) 
                 | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_write) 
                    & (1U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__region))))));
    vlSelfRef.top__DOT__u_cpu__DOT__data_wstrb_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wstrb;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_wdata_out;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_araddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_araddr_out;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awaddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_awaddr_out;
    vlSelfRef.top__DOT__u_cpu__DOT__lsu_pre_fault = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__pre_fault;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wstrb 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_wstrb_out;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_araddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_araddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_awaddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awaddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_awaddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awaddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wstrb 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wstrb;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wstrb 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wstrb;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_wdata = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__data_wdata = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_araddr = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__data_araddr = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_awaddr = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_awaddr;
    vlSelfRef.top__DOT__u_cpu__DOT__data_awaddr = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_awaddr;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_wstrb = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wstrb;
    vlSelfRef.top__DOT__u_cpu__DOT__data_wstrb = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wstrb;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_wdata;
    vlSelfRef.top__DOT__data_wdata = vlSelfRef.top__DOT__u_cpu__DOT__data_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_araddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_araddr;
    vlSelfRef.top__DOT__data_araddr = vlSelfRef.top__DOT__u_cpu__DOT__data_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_awaddr 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_awaddr;
    vlSelfRef.top__DOT__data_awaddr = vlSelfRef.top__DOT__u_cpu__DOT__data_awaddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wstrb 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_wstrb;
    vlSelfRef.top__DOT__data_wstrb = vlSelfRef.top__DOT__u_cpu__DOT__data_wstrb;
    vlSelfRef.top__DOT__u_mem__DOT__data_wdata = vlSelfRef.top__DOT__data_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word 
        = (0x7ffffffcU & vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_araddr);
    vlSelfRef.top__DOT__u_mem__DOT__data_araddr = vlSelfRef.top__DOT__data_araddr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__wr_word 
        = (0x7ffffffcU & vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_awaddr);
    vlSelfRef.top__DOT__u_mem__DOT__data_awaddr = vlSelfRef.top__DOT__data_awaddr;
    vlSelfRef.top__DOT__u_mem__DOT__data_wstrb = vlSelfRef.top__DOT__data_wstrb;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_wdata 
        = vlSelfRef.top__DOT__u_mem__DOT__data_wdata;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_wdata 
        = vlSelfRef.top__DOT__u_mem__DOT__data_wdata;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__wdata 
        = vlSelfRef.top__DOT__u_mem__DOT__data_wdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_resp = 0U;
    if ((1U & (~ ((((((((0U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word) 
                        | (4U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
                       | (8U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
                      | (0x00001000U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
                     | (0x00001004U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
                    | (0x00001008U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
                   | (0x0000100cU == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
                  | (0x00001010U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word))))) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_resp = 2U;
    }
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__araddr 
        = vlSelfRef.top__DOT__u_mem__DOT__data_araddr;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_araddr 
        = (vlSelfRef.top__DOT__u_mem__DOT__data_araddr 
           - (IData)(0x00002000U));
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_awaddr 
        = vlSelfRef.top__DOT__u_mem__DOT__data_awaddr;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__awaddr 
        = vlSelfRef.top__DOT__u_mem__DOT__data_awaddr;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_awaddr 
        = (vlSelfRef.top__DOT__u_mem__DOT__data_awaddr 
           - (IData)(0x00002000U));
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_wstrb 
        = vlSelfRef.top__DOT__u_mem__DOT__data_wstrb;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_wstrb 
        = vlSelfRef.top__DOT__u_mem__DOT__data_wstrb;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__wstrb 
        = vlSelfRef.top__DOT__u_mem__DOT__data_wstrb;
}

void Vtop___024root___nba_sequent__TOP__12(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__12\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_arvalid) {
        vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_rdata 
            = vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__container
            [(0x000007ffU & (vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_araddr 
                             >> 2U))];
    }
    if (vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_arvalid) {
        vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_rdata 
            = vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__container
            [(0x000007ffU & (vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_araddr 
                             >> 2U))];
    }
    vlSelfRef.top__DOT__u_mem__DOT__rom_if_rdata = vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_rdata;
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_rdata = vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_rdata;
}

void Vtop___024root___nba_sequent__TOP__13(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__13\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VdlyVal__top__DOT__u_cpu__DOT__u_reg_file__DOT__registers__v0;
    __VdlyVal__top__DOT__u_cpu__DOT__u_reg_file__DOT__registers__v0 = 0;
    CData/*4:0*/ __VdlyDim0__top__DOT__u_cpu__DOT__u_reg_file__DOT__registers__v0;
    __VdlyDim0__top__DOT__u_cpu__DOT__u_reg_file__DOT__registers__v0 = 0;
    CData/*4:0*/ __VdlyDim0__top__DOT__u_cpu__DOT__u_reg_file__DOT__registers__v1;
    __VdlyDim0__top__DOT__u_cpu__DOT__u_reg_file__DOT__registers__v1 = 0;
    // Body
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__rst_n) {
        if (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_enable) 
             & (0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_addr)))) {
            __VdlyVal__top__DOT__u_cpu__DOT__u_reg_file__DOT__registers__v0 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_data;
            __VdlyDim0__top__DOT__u_cpu__DOT__u_reg_file__DOT__registers__v0 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_addr;
            vlSelfRef.__VdlyCommitQueuetop__DOT__u_cpu__DOT__u_reg_file__DOT__registers.enqueue(__VdlyVal__top__DOT__u_cpu__DOT__u_reg_file__DOT__registers__v0, (IData)(__VdlyDim0__top__DOT__u_cpu__DOT__u_reg_file__DOT__registers__v0));
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__i = 0U;
        while (VL_GTS_III(32, 0x00000020U, vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__i)) {
            __VdlyDim0__top__DOT__u_cpu__DOT__u_reg_file__DOT__registers__v1 
                = (0x0000001fU & vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__i);
            vlSelfRef.__VdlyCommitQueuetop__DOT__u_cpu__DOT__u_reg_file__DOT__registers.enqueue(0U, (IData)(__VdlyDim0__top__DOT__u_cpu__DOT__u_reg_file__DOT__registers__v1));
            vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__i 
                = ((IData)(1U) + vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__i);
        }
    }
    vlSelfRef.__VdlyCommitQueuetop__DOT__u_cpu__DOT__u_reg_file__DOT__registers.commit(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__registers);
}

void Vtop___024root___nba_sequent__TOP__14(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__14\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_6;
    __VdfgRegularize_h6e95ff9d_0_6 = 0;
    // Body
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__rst_n) {
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__clear) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_illegal = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_if_fault = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_write = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_to_reg = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_pc_in1_sel = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_read = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_reg_write = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_stop = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_branch = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_jalr = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_jal = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_funct3 = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_op = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_in2_roi = 1U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_in1_ropc = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_bypass = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_imm_to_reg = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs2_data = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_imm_val = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs1_data = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_pc = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rd_addr = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs2_addr = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs1_addr = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_opcode = 0x13U;
        } else if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__stall)))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_illegal 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_illegal;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_if_fault 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_if_fault;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_write 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_mem_write;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_to_reg 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_mem_to_reg;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_pc_in1_sel 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_pc_in1_sel;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_read 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_mem_read;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_reg_write 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_reg_write;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_stop 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_stop;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_branch 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_branch;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_jalr 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_jalr;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_jal 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_jal;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_funct3 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_funct3;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_op 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_op;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_in2_roi 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_in2_roi;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_in1_ropc 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_in1_ropc;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_bypass 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_bypass;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_imm_to_reg 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_imm_to_reg;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs2_data 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs2_data;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_imm_val 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_imm_val;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs1_data 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs1_data;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_pc 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_pc;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rd_addr 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rd_addr;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs2_addr 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs2_addr;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs1_addr 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs1_addr;
            vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_opcode 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_opcode;
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_illegal = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_if_fault = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_write = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_to_reg = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_pc_in1_sel = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_read = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_reg_write = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_stop = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_branch = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_jalr = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_jal = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_funct3 = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_op = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_in2_roi = 1U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_in1_ropc = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_bypass = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_imm_to_reg = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs2_data = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_imm_val = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs1_data = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_pc = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rd_addr = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs2_addr = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs1_addr = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_opcode = 0x13U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_illegal = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_illegal;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_if_fault 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_if_fault;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_mem_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_write;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_mem_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_pc_in1_sel 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_pc_in1_sel;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_mem_read 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_mem_read;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_stop = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_stop;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_branch 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_branch;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_jalr = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_jalr;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_jal = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_is_jal;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_funct3 = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_op;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_in2_roi 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_in2_roi;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_in1_ropc 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_in1_ropc;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_bypass 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_alu_bypass;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_imm_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_imm_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs2_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs2_data;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_imm_val = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_imm_val;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs1_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs1_data;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_pc = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_pc;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rd_addr = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs2_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs2_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs1_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_rs1_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__id_ex_opcode = vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__o_opcode;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_mem_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_mem_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_mem_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_mem_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pcinc_in1_pcor 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_pc_in1_sel;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_mem_read 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_mem_read;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_mem_read 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_mem_read;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_is_stop 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_stop;
    vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__is_branch 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_branch;
    vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__is_jalr 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_jalr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__is_jal 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_jal;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_funct3 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__id_ex_funct3 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_op;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__use_imm 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_in2_roi;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__use_pc 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_in1_ropc;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_bypass 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_alu_bypass;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__imm_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_imm_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__r_data2 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs2_data;
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__imm_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_imm_val;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__imm 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_imm_val;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__r_data1 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs1_data;
    vlSelfRef.top__DOT__u_cpu__DOT__pc_plus4 = ((IData)(4U) 
                                                + vlSelfRef.top__DOT__u_cpu__DOT__id_ex_pc);
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pc_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_pc;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__pc 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_pc;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_rd_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rd 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs2_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs1_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_opcode 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_ex_opcode;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_mem_read 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_mem_read;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rd 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rd;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_opcode;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rd_not_x0 
        = (0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rd));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2_not_x0 
        = (0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1_not_x0 
        = (0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1));
    __VdfgRegularize_h6e95ff9d_0_6 = ((0x33U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode)) 
                                      | ((0x23U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode)) 
                                         | (0x63U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rd_not_x0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rd_not_x0;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs2_not_x0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2_not_x0;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs1_not_x0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1_not_x0;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2_valid 
        = __VdfgRegularize_h6e95ff9d_0_6;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1_valid 
        = ((IData)(__VdfgRegularize_h6e95ff9d_0_6) 
           | ((0x13U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode)) 
              | ((3U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode)) 
                 | ((0x67U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode)) 
                    | (0x73U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_opcode))))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_rd_not_x0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rd_not_x0;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs2_not_x0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs2_not_x0;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs1_not_x0 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs1_not_x0;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs2_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs1_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs2_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs2_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs1_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_rs1_valid;
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4 = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs2_not_x0) 
                                                & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs2_valid));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_5 = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs1_not_x0) 
                                                & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__id_ex_rs1_valid));
}

void Vtop___024root___nba_sequent__TOP__15(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__15\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_rvalid 
        = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__rst_n) 
           && (IData)(vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_arvalid));
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_bvalid 
        = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__rst_n) 
           && ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_awvalid) 
               & (IData)(vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_wvalid)));
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_rvalid 
        = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__rst_n) 
           && (IData)(vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_arvalid));
    vlSelfRef.top__DOT__u_mem__DOT__rom_if_rvalid = vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_rvalid;
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_bvalid = vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_bvalid;
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_rvalid = vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_rvalid;
}

void Vtop___024root___nba_sequent__TOP__16(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__16\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_rvalid 
        = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__rst_n) 
           && (IData)(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_arvalid));
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_bvalid 
        = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__rst_n) 
           && (IData)(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__b_write));
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_rvalid 
        = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__rst_n) 
           && (IData)(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_arvalid));
    vlSelfRef.top__DOT__u_mem__DOT__ram_if_rvalid = vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_rvalid;
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_bvalid = vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_bvalid;
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_rvalid = vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_rvalid;
}

void Vtop___024root___nba_sequent__TOP__17(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__17\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.top__DOT__u_mem__DOT__rst_n) {
        if (((IData)(vlSelfRef.top__DOT__u_mem__DOT__if_arvalid) 
             & (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_arready))) {
            vlSelfRef.top__DOT__u_mem__DOT__if_sel_q 
                = vlSelfRef.top__DOT__u_mem__DOT__if_sel;
        }
        if (((((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_awvalid) 
               & (IData)(vlSelfRef.top__DOT__u_mem__DOT__data_wvalid)) 
              & (IData)(vlSelfRef.top__DOT__u_mem__DOT__data_awready)) 
             & (IData)(vlSelfRef.top__DOT__u_mem__DOT__data_wready))) {
            vlSelfRef.top__DOT__u_mem__DOT__wr_sel_q 
                = vlSelfRef.top__DOT__u_mem__DOT__wr_sel;
        }
        if (((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_arvalid) 
             & (IData)(vlSelfRef.top__DOT__u_mem__DOT__data_arready))) {
            vlSelfRef.top__DOT__u_mem__DOT__rd_sel_q 
                = vlSelfRef.top__DOT__u_mem__DOT__rd_sel;
        }
    } else {
        vlSelfRef.top__DOT__u_mem__DOT__if_sel_q = 1U;
        vlSelfRef.top__DOT__u_mem__DOT__wr_sel_q = 0U;
        vlSelfRef.top__DOT__u_mem__DOT__rd_sel_q = 0U;
    }
    vlSelfRef.top__DOT__u_mem__DOT__if_rresp = ((1U 
                                                 == (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel_q))
                                                 ? 0U
                                                 : 
                                                ((2U 
                                                  == (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel_q))
                                                  ? 0U
                                                  : 3U));
    vlSelfRef.top__DOT__u_mem__DOT__data_bresp = ((1U 
                                                   == (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel_q))
                                                   ? 2U
                                                   : 
                                                  ((2U 
                                                    == (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel_q))
                                                    ? 0U
                                                    : 3U));
    vlSelfRef.top__DOT__u_mem__DOT__data_rresp = ((1U 
                                                   == (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel_q))
                                                   ? 0U
                                                   : 
                                                  ((2U 
                                                    == (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel_q))
                                                    ? 0U
                                                    : 3U));
    vlSelfRef.top__DOT__if_rresp = vlSelfRef.top__DOT__u_mem__DOT__if_rresp;
    vlSelfRef.top__DOT__data_bresp = vlSelfRef.top__DOT__u_mem__DOT__data_bresp;
    vlSelfRef.top__DOT__data_rresp = vlSelfRef.top__DOT__u_mem__DOT__data_rresp;
    vlSelfRef.top__DOT__u_cpu__DOT__if_rresp = vlSelfRef.top__DOT__if_rresp;
    vlSelfRef.top__DOT__u_cpu__DOT__data_bresp = vlSelfRef.top__DOT__data_bresp;
    vlSelfRef.top__DOT__u_cpu__DOT__data_rresp = vlSelfRef.top__DOT__data_rresp;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_rresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_rresp;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_bresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_bresp;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_rresp;
}

void Vtop___024root___nba_sequent__TOP__18(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__18\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__rst_n) {
        if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__stall)))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_is_stop 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_is_stop;
            vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_result 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_result;
            vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_funct3 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_funct3;
            vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_addr_lo 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_addr_lo;
            vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_mem_to_reg 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_mem_to_reg;
            vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_reg_write 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_reg_write;
            vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_rd_addr 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_rd_addr;
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_is_stop = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_result = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_funct3 = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_addr_lo = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_mem_to_reg = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_reg_write = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_rd_addr = 0U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_stop = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_is_stop;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_result = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_result;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_funct3 = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_addr_lo 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_addr_lo;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_mem_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_mem_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_rd_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__o_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__result 
        = vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_result;
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__funct3 
        = vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__addr_lo 
        = vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_addr_lo;
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__mem_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_mem_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_rd 
        = vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__mem_wb_reg_write 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_reg_write;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__mem_wb_rd 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_rd;
}

void Vtop___024root___nba_sequent__TOP__19(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__19\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__bvalid 
        = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__rst_n) 
           && ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__awvalid) 
               & (IData)(vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__wvalid)));
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__rvalid 
        = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__rst_n) 
           && (IData)(vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__arvalid));
    vlSelfRef.top__DOT__u_mem__DOT__ddt_bvalid = vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__bvalid;
    vlSelfRef.top__DOT__u_mem__DOT__ddt_rvalid = vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__rvalid;
}

void Vtop___024root___nba_sequent__TOP__20(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__20\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__rst_n) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__b_out 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__b_out_next;
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__mem_advance) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_sent = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_q = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__aw_sent = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__w_sent = 0U;
        } else {
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_hs) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_sent = 1U;
            }
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_now) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_q = 1U;
            }
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__aw_hs) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__aw_sent = 1U;
            }
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__w_hs) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__w_sent = 1U;
            }
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__b_out = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_sent = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_q = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__aw_sent = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__w_sent = 0U;
    }
}

void Vtop___024root___nba_sequent__TOP__21(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__21\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rst_n) {
        if (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_arvalid) 
             & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_arready))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_sel_q 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_mmio;
        }
        if (((((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awvalid) 
               & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wvalid)) 
              & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awready)) 
             & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wready))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_sel_q 
                = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio;
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_sel_q = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_sel_q = 0U;
    }
}

void Vtop___024root___nba_sequent__TOP__22(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__22\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__baud_tick 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__baud_tick;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__baud_tick 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__baud_tick;
}

void Vtop___024root___nba_sequent__TOP__23(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__23\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_busy 
        = vlSelfRef.top__DOT__u_cpu__DOT__uart_tx_busy;
}

void Vtop___024root___nba_sequent__TOP__24(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__24\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rx_ack 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rx_ack;
}

void Vtop___024root___nba_sequent__TOP__25(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__25\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__rst_n = vlSelfRef.top__DOT__core_rst_n;
    vlSelfRef.top__DOT__u_mem__DOT__rst_n = vlSelfRef.top__DOT__core_rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__rst_n;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__rst_n 
        = vlSelfRef.top__DOT__u_mem__DOT__rst_n;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__rst_n 
        = vlSelfRef.top__DOT__u_mem__DOT__rst_n;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__rst_n 
        = vlSelfRef.top__DOT__u_mem__DOT__rst_n;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__rst_n 
        = vlSelfRef.top__DOT__u_mem__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_baud_rate_gen__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rst_n;
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_rx__DOT__rst_n 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__rst_n;
}

void Vtop___024root___nba_comb__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_8;
    __VdfgRegularize_h6e95ff9d_0_8 = 0;
    // Body
    __VdfgRegularize_h6e95ff9d_0_8 = (1U & (~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__freeze) 
                                               | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__pre_fault))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__load_req 
        = ((IData)(__VdfgRegularize_h6e95ff9d_0_8) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_read));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__store_req 
        = ((IData)(__VdfgRegularize_h6e95ff9d_0_8) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mem_write));
}

void Vtop___024root___nba_sequent__TOP__26(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__26\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_araddr 
        = vlSelfRef.top__DOT__u_mem__DOT__data_araddr;
    vlSelfRef.top__DOT__u_mem__DOT__wr_sel = (3U & 
                                              (((0x00002000U 
                                                 > vlSelfRef.top__DOT__u_mem__DOT__data_awaddr)
                                                 ? 1U
                                                 : 
                                                (2U 
                                                 & (- (IData)(
                                                              (0x00022000U 
                                                               > vlSelfRef.top__DOT__u_mem__DOT__data_awaddr))))) 
                                               | (- (IData)(
                                                            (vlSelfRef.top__DOT__u_mem__DOT__data_awaddr 
                                                             >> 0x0000001fU)))));
    vlSelfRef.top__DOT__u_mem__DOT__rd_sel = (3U & 
                                              (((0x00002000U 
                                                 > vlSelfRef.top__DOT__u_mem__DOT__data_araddr)
                                                 ? 1U
                                                 : 
                                                (2U 
                                                 & (- (IData)(
                                                              (0x00022000U 
                                                               > vlSelfRef.top__DOT__u_mem__DOT__data_araddr))))) 
                                               | (- (IData)(
                                                            (vlSelfRef.top__DOT__u_mem__DOT__data_araddr 
                                                             >> 0x0000001fU)))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_is_stop 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_stop;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_result 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_funct3 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_addr_lo 
        = (3U & vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result);
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_mem_to_reg 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__lsu_pre_fault)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_mem_to_reg));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_reg_write 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__lsu_pre_fault)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_reg_write));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__i_rd_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_rd_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_mmio 
        = (vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_araddr 
           >> 0x0000001fU);
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio 
        = (vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awaddr 
           >> 0x0000001fU);
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_3 = ((1U 
                                                 != (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel)) 
                                                & (2U 
                                                   != (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_arready 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_arready) 
           | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_mmio));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awready 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_awready) 
           | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wready 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wready) 
           | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio));
    vlSelfRef.top__DOT__u_cpu__DOT__data_arready_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_arready;
    vlSelfRef.top__DOT__u_cpu__DOT__data_awready_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awready;
    vlSelfRef.top__DOT__u_cpu__DOT__data_wready_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wready;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_arready 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_arready_in;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_awready 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_awready_in;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wready 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_wready_in;
}

void Vtop___024root___nba_sequent__TOP__27(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__27\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_illegal 
        = vlSelfRef.top__DOT__u_cpu__DOT__id_kill;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_if_fault 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_id_fault;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_mem_write 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_kill)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_write));
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_mem_to_reg 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_kill)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_to_reg));
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_pc_in1_sel 
        = vlSelfRef.top__DOT__u_cpu__DOT__pc_in1_sel;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_mem_read 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_kill)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_read));
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_reg_write 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_kill)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__reg_w_enable));
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_stop 
        = vlSelfRef.top__DOT__u_cpu__DOT__d_stop;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_branch 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_kill)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__d_is_branch));
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_jalr 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_kill)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__d_is_jalr));
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_is_jal 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_kill)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__d_is_jal));
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_funct3 
        = vlSelfRef.top__DOT__u_cpu__DOT__funct3;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_op 
        = vlSelfRef.top__DOT__u_cpu__DOT__alu_op;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_in2_roi 
        = vlSelfRef.top__DOT__u_cpu__DOT__alu_in2_sel;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_in1_ropc 
        = vlSelfRef.top__DOT__u_cpu__DOT__alu_in1_sel;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_alu_bypass 
        = vlSelfRef.top__DOT__u_cpu__DOT__alu_bypass;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_imm_to_reg 
        = vlSelfRef.top__DOT__u_cpu__DOT__imm_to_reg;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_imm_val 
        = vlSelfRef.top__DOT__u_cpu__DOT__imm_val;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_pc 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_id_pc;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rd_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__rdst_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs2_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__rs2_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs1_addr 
        = vlSelfRef.top__DOT__u_cpu__DOT__rs1_addr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_opcode 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_id_opcode;
}

void Vtop___024root___nba_comb__TOP__1(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__1\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_id_ex_rd_if_id_rs1 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs1) 
           == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rd));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_id_ex_rd_if_id_rs2 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__if_id_rs2) 
           == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rd));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_id_ex_rd_if_id_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_id_ex_rd_if_id_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_id_ex_rd_if_id_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_id_ex_rd_if_id_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_id_ex_rd_if_id_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_id_ex_rd_if_id_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__dep_id_ex_rd_if_id_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_id_ex_rd_if_id_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_id_ex_rd_if_id_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_id_ex_rd_if_id_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__dep_id_ex_rd_if_id_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_id_ex_rd_if_id_rs2;
}

void Vtop___024root___nba_comb__TOP__2(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__2\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_ex_mem_rd_id_ex_rs2 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2) 
           == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__ex_mem_rd));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_ex_mem_rd_id_ex_rs1 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1) 
           == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__ex_mem_rd));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_ex_mem_rd_id_ex_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_ex_mem_rd_id_ex_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_ex_mem_rd_id_ex_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_ex_mem_rd_id_ex_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_ex_mem_rd_id_ex_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_ex_mem_rd_id_ex_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_ex_mem_rd_id_ex_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_ex_mem_rd_id_ex_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in2_ex_mem 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4) 
           & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_ex_mem_rd_id_ex_rs2) 
              & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__ex_mem_reg_write)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in1_ex_mem 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_5) 
           & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_ex_mem_rd_id_ex_rs1) 
              & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__ex_mem_reg_write)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in2_ex_mem 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in2_ex_mem;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in1_ex_mem 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in1_ex_mem;
    vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in2_ex_mem 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in2_ex_mem;
    vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in1_ex_mem 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in1_ex_mem;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in2_ex_mem 
        = vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in2_ex_mem;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in1_ex_mem 
        = vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in1_ex_mem;
}

void Vtop___024root___nba_comb__TOP__3(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__3\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_mem__DOT__if_rdata = ((1U 
                                                 == (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel_q))
                                                 ? vlSelfRef.top__DOT__u_mem__DOT__rom_if_rdata
                                                 : 
                                                ((2U 
                                                  == (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel_q))
                                                  ? vlSelfRef.top__DOT__u_mem__DOT__ram_if_rdata
                                                  : 0U));
    vlSelfRef.top__DOT__u_mem__DOT__data_rdata = ((1U 
                                                   == (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel_q))
                                                   ? vlSelfRef.top__DOT__u_mem__DOT__rom_d_rdata
                                                   : 
                                                  ((2U 
                                                    == (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel_q))
                                                    ? vlSelfRef.top__DOT__u_mem__DOT__ram_d_rdata
                                                    : 0U));
    vlSelfRef.top__DOT__if_rdata = vlSelfRef.top__DOT__u_mem__DOT__if_rdata;
    vlSelfRef.top__DOT__data_rdata = vlSelfRef.top__DOT__u_mem__DOT__data_rdata;
    vlSelfRef.top__DOT__u_cpu__DOT__if_rdata = vlSelfRef.top__DOT__if_rdata;
    vlSelfRef.top__DOT__u_cpu__DOT__data_rdata = vlSelfRef.top__DOT__data_rdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_rdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_rdata;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_rdata;
}

void Vtop___024root___nba_comb__TOP__4(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__4\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_mem__DOT__if_rvalid = ((1U 
                                                  == (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel_q))
                                                  ? (IData)(vlSelfRef.top__DOT__u_mem__DOT__rom_if_rvalid)
                                                  : 
                                                 ((2U 
                                                   == (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel_q))
                                                   ? (IData)(vlSelfRef.top__DOT__u_mem__DOT__ram_if_rvalid)
                                                   : (IData)(vlSelfRef.top__DOT__u_mem__DOT__dif_rvalid)));
    vlSelfRef.top__DOT__if_rvalid = vlSelfRef.top__DOT__u_mem__DOT__if_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__if_rvalid = vlSelfRef.top__DOT__if_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_rvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__r_hs 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_rvalid;
}

void Vtop___024root___nba_comb__TOP__5(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__5\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__stop_in_flight 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_stop) 
           | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_stop) 
              | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_stop)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__stop_in_flight 
        = vlSelfRef.top__DOT__u_cpu__DOT__stop_in_flight;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__stop_in_flight 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__stop_in_flight;
}

void Vtop___024root___nba_comb__TOP__6(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__6\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_mem_wb_rd_id_ex_rs2 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs2) 
           == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__mem_wb_rd));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_mem_wb_rd_id_ex_rs1 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__id_ex_rs1) 
           == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__mem_wb_rd));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_mem_wb_rd_id_ex_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_mem_wb_rd_id_ex_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_mem_wb_rd_id_ex_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_dep_analyzer__DOT__dep_mem_wb_rd_id_ex_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_mem_wb_rd_id_ex_rs2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_mem_wb_rd_id_ex_rs2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_mem_wb_rd_id_ex_rs1 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__dep_mem_wb_rd_id_ex_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in2_mem_wb 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4) 
           & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_mem_wb_rd_id_ex_rs2) 
              & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__mem_wb_reg_write)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in1_mem_wb 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_5) 
           & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__dep_mem_wb_rd_id_ex_rs1) 
              & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__mem_wb_reg_write)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in2_mem_wb 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in2_mem_wb;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in1_mem_wb 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_fwd_unit__DOT__fwd_alu_in1_mem_wb;
    vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in2_mem_wb 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in2_mem_wb;
    vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in1_mem_wb 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__fwd_alu_in1_mem_wb;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in2_mem_wb 
        = vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in2_mem_wb;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in1_mem_wb 
        = vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in1_mem_wb;
}

void Vtop___024root___nba_comb__TOP__7(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__7\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_mem__DOT__data_bvalid = (
                                                   (1U 
                                                    == (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel_q))
                                                    ? (IData)(vlSelfRef.top__DOT__u_mem__DOT__rom_d_bvalid)
                                                    : 
                                                   ((2U 
                                                     == (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel_q))
                                                     ? (IData)(vlSelfRef.top__DOT__u_mem__DOT__ram_d_bvalid)
                                                     : (IData)(vlSelfRef.top__DOT__u_mem__DOT__ddt_bvalid)));
    vlSelfRef.top__DOT__u_mem__DOT__data_rvalid = (
                                                   (1U 
                                                    == (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel_q))
                                                    ? (IData)(vlSelfRef.top__DOT__u_mem__DOT__rom_d_rvalid)
                                                    : 
                                                   ((2U 
                                                     == (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel_q))
                                                     ? (IData)(vlSelfRef.top__DOT__u_mem__DOT__ram_d_rvalid)
                                                     : (IData)(vlSelfRef.top__DOT__u_mem__DOT__ddt_rvalid)));
    vlSelfRef.top__DOT__data_bvalid = vlSelfRef.top__DOT__u_mem__DOT__data_bvalid;
    vlSelfRef.top__DOT__data_rvalid = vlSelfRef.top__DOT__u_mem__DOT__data_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__data_bvalid = vlSelfRef.top__DOT__data_bvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__data_rvalid = vlSelfRef.top__DOT__data_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_bvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_bvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_rvalid;
}

void Vtop___024root___nba_comb__TOP__8(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__8\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rresp 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_sel_q)
            ? (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rresp)
            : (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rresp));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_bresp 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_sel_q)
            ? (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_bresp)
            : (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_bresp));
    vlSelfRef.top__DOT__u_cpu__DOT__data_rresp_in = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rresp;
    vlSelfRef.top__DOT__u_cpu__DOT__data_bresp_in = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_bresp;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_rresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_rresp_in;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_bresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_bresp_in;
}

void Vtop___024root___nba_comb__TOP__9(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__9\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__bit_done 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__baud_tick) 
           & (0x0fU == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_uart_module__DOT__u_uart_tx__DOT__tick_cntr)));
}

void Vtop___024root___nba_comb__TOP__10(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__10\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_uart_status 
        = ((((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_start) 
             | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_tx_busy)) 
            << 1U) | ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_ack)) 
                      & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_valid)));
}

void Vtop___024root___nba_comb__TOP__11(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__11\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_arvalid 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_sent)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__load_req));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_awvalid 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__aw_sent)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__store_req));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wvalid 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__w_sent)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__store_req));
    vlSelfRef.top__DOT__u_cpu__DOT__data_arvalid_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_arvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_hs 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_arvalid) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_arready));
    vlSelfRef.top__DOT__u_cpu__DOT__data_awvalid_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_awvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__aw_hs 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_awvalid) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_awready));
    vlSelfRef.top__DOT__u_cpu__DOT__data_wvalid_out 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__w_hs 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wvalid) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_wready));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_arvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_arvalid_out;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_done 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_sent) 
           | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_hs));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_awvalid_out;
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_wvalid_out;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_now 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__store_req) 
           & ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_q)) 
              & (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__aw_sent) 
                  | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__aw_hs)) 
                 & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__w_sent) 
                    | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__w_hs)))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_arvalid 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_arvalid) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_mmio));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_arvalid 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_mmio)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_arvalid));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_awvalid 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awvalid) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_awvalid 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_awvalid));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wvalid 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wvalid) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wvalid 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_mmio)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_wvalid));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_accepted 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_now) 
           | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_q));
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_arvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_arvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__data_arvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_arvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_awvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_awvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__data_awvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_awvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__mmio_wvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_wvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__data_wvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_wvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_arvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_arvalid;
    vlSelfRef.top__DOT__data_arvalid = vlSelfRef.top__DOT__u_cpu__DOT__data_arvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_awvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_awvalid;
    vlSelfRef.top__DOT__data_awvalid = vlSelfRef.top__DOT__u_cpu__DOT__data_awvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__data_wvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__mmio_wvalid;
    vlSelfRef.top__DOT__data_wvalid = vlSelfRef.top__DOT__u_cpu__DOT__data_wvalid;
    vlSelfRef.top__DOT__u_mem__DOT__data_arvalid = vlSelfRef.top__DOT__data_arvalid;
    vlSelfRef.top__DOT__u_mem__DOT__data_awvalid = vlSelfRef.top__DOT__data_awvalid;
    vlSelfRef.top__DOT__u_mem__DOT__data_wvalid = vlSelfRef.top__DOT__data_wvalid;
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_arvalid = 
        ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_arvalid) 
         & (1U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel)));
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_arvalid = 
        ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_arvalid) 
         & (2U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel)));
    vlSelfRef.top__DOT__u_mem__DOT__ddt_arvalid = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_arvalid) 
                                                   & ((1U 
                                                       != (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel)) 
                                                      & (2U 
                                                         != (IData)(vlSelfRef.top__DOT__u_mem__DOT__rd_sel))));
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_awvalid = 
        ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_awvalid) 
         & (1U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel)));
    vlSelfRef.top__DOT__u_mem__DOT__ddt_awvalid = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_awvalid) 
                                                   & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_3));
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_awvalid = 
        ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_awvalid) 
         & (2U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel)));
    vlSelfRef.top__DOT__u_mem__DOT__rom_d_wvalid = 
        ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_wvalid) 
         & (1U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel)));
    vlSelfRef.top__DOT__u_mem__DOT__ddt_wvalid = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_wvalid) 
                                                  & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_3));
    vlSelfRef.top__DOT__u_mem__DOT__ram_d_wvalid = 
        ((IData)(vlSelfRef.top__DOT__u_mem__DOT__data_wvalid) 
         & (2U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__wr_sel)));
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_arvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__rom_d_arvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_arvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__ram_d_arvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__arvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__ddt_arvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_awvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__rom_d_awvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__awvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__ddt_awvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_awvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__ram_d_awvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__data_wvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__rom_d_wvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_data__DOT__wvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__ddt_wvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_wvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__ram_d_wvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__b_write 
        = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_awvalid) 
           & (IData)(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_wvalid));
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__b_idx 
        = (0x00007fffU & ((IData)(vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__b_write)
                           ? (vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_awaddr 
                              >> 2U) : (vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__data_araddr 
                                        >> 2U)));
}

void Vtop___024root___nba_comb__TOP__12(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__12\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rdata 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_sel_q)
            ? vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rdata
            : vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rdata);
    vlSelfRef.top__DOT__u_cpu__DOT__data_rdata_in = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rdata;
}

void Vtop___024root___nba_comb__TOP__13(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__13\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_bvalid 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__wr_sel_q)
            ? (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_bvalid)
            : (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_bvalid));
    vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rvalid 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__rd_sel_q)
            ? (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__mmio_rvalid)
            : (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__ext_rvalid));
    vlSelfRef.top__DOT__u_cpu__DOT__data_bvalid_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_bvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__data_rvalid_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_data_decoder__DOT__m_rvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_bvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_bvalid_in;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_rvalid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_rvalid_in;
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__b_hs 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_bvalid;
}

void Vtop___024root___nba_comb__TOP__14(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__14\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__wb_rresp = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_valid)
                                                 ? (IData)(vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_resp)
                                                 : (IData)(vlSelfRef.top__DOT__u_cpu__DOT__data_rresp_in));
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__data_rresp 
        = vlSelfRef.top__DOT__u_cpu__DOT__wb_rresp;
}

void Vtop___024root___nba_comb__TOP__15(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__15\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_val = 0U;
    if (((((((((0U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word) 
               | (4U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
              | (8U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
             | (0x00001000U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
            | (0x00001004U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
           | (0x00001008U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
          | (0x0000100cU == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)) 
         | (0x00001010U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word))) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_val 
            = ((0U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)
                ? (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_uart_status)
                : ((4U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)
                    ? (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__uart_rx_data)
                    : ((8U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)
                        ? 0U : ((0x00001000U == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)
                                 ? ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__p_meta_control) 
                                    << 8U) : ((0x00001004U 
                                               == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)
                                               ? vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_instr_count
                                               : ((0x00001008U 
                                                   == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)
                                                   ? vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_stall_count
                                                   : 
                                                  ((0x0000100cU 
                                                    == vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__rd_word)
                                                    ? vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_l_use_count
                                                    : vlSelfRef.top__DOT__u_cpu__DOT__u_mmio_interface__DOT__meta_br_flush_count)))))));
    }
}

void Vtop___024root___nba_comb__TOP__16(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__16\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__wb_rdata = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_valid)
                                                 ? vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_data
                                                 : vlSelfRef.top__DOT__u_cpu__DOT__data_rdata_in);
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__data_rdata 
        = vlSelfRef.top__DOT__u_cpu__DOT__wb_rdata;
}

void Vtop___024root___nba_comb__TOP__17(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__17\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__wb_data_wait = 
        ((~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__wb_cap_valid) 
             | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__data_rvalid_in))) 
         & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_mem_to_reg));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__wb_data_wait 
        = vlSelfRef.top__DOT__u_cpu__DOT__wb_data_wait;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__wb_data_wait 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__wb_data_wait;
}

void Vtop___024root___nba_comb__TOP__18(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__18\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_fault 
        = (((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__freeze)) 
            & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__pre_fault)) 
           | (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_rvalid) 
               & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_rresp) 
                  >> 1U)) | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__b_hs) 
                             & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_bresp) 
                                >> 1U))));
    vlSelfRef.top__DOT__u_cpu__DOT__lsu_data_fault 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__data_fault;
}

void Vtop___024root___nba_comb__TOP__19(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__19\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__b_out_next 
        = (3U & (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__b_out) 
                  + (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_acc_now)) 
                 - (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__b_hs)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__store_done 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__wr_accepted) 
           & ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__is_mmio)) 
              | (0U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__b_out_next))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__mem_stage_busy 
        = (((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__store_done)) 
            & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__store_req)) 
           | ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__ar_done)) 
              & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__load_req)));
    vlSelfRef.top__DOT__u_cpu__DOT__mem_stage_busy 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__mem_stage_busy;
    vlSelfRef.top__DOT__u_cpu__DOT__data_fetch_valid 
        = (1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_stage_busy)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__data_fetch_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__data_fetch_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__data_fetch_valid 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__data_fetch_valid;
}

void Vtop___024root___nba_comb__TOP__20(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__20\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__load_fault 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__mem_to_reg) 
           & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__data_rresp) 
              >> 1U));
    vlSelfRef.top__DOT__u_cpu__DOT__load_fault = vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__load_fault;
}

void Vtop___024root___nba_comb__TOP__21(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__21\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted 
        = (vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__data_rdata 
           >> ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__addr_lo) 
               << 3U));
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__load_val 
        = ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__funct3))
            ? ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__funct3))
                ? vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted
                : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__funct3))
                    ? (0x0000ffffU & vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted)
                    : (0x000000ffU & vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted)))
            : ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__funct3))
                ? vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted
                : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__funct3))
                    ? (((- (IData)((1U & (vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted 
                                          >> 0x0fU)))) 
                        << 0x00000010U) | (0x0000ffffU 
                                           & vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted))
                    : (((- (IData)((1U & (vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted 
                                          >> 7U)))) 
                        << 8U) | (0x000000ffU & vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__shifted)))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__rd_data 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__mem_to_reg)
            ? vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__load_val
            : vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__result);
    vlSelfRef.top__DOT__u_cpu__DOT__wb_rd_data = vlSelfRef.top__DOT__u_cpu__DOT__u_write_back__DOT__rd_data;
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__wb_rd_data;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__mem_wb_rd_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__wb_rd_data;
}

void Vtop___024root___nba_comb__TOP__22(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__22\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_enable = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__mem_wb_enable = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__ex_mem_enable = 1U;
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__freeze) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__mem_wb_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__ex_mem_enable = 0U;
    } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__wb_data_wait) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__mem_wb_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__ex_mem_enable = 0U;
    } else if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__data_fetch_valid)))) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__mem_wb_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__ex_mem_enable = 0U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__mem_wb_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__ex_mem_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__ex_mem_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_id_ex_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_mem_wb_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__mem_wb_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_ex_mem_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__ex_mem_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__stall 
        = (1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__hz_id_ex_enable)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_mem_wb__DOT__stall 
        = (1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__hz_mem_wb_enable)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__stall 
        = (1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__hz_ex_mem_enable)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_lsu__DOT__mem_advance 
        = vlSelfRef.top__DOT__u_cpu__DOT__hz_ex_mem_enable;
}

void Vtop___024root___nba_comb__TOP__23(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__23\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_enable 
        = ((~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__wb_data_wait) 
               | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__load_fault))) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__mem_wb_reg_write));
}

void Vtop___024root___nba_comb__TOP__24(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__24\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*3:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__fwd_store_data 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in2_ex_mem)
            ? vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result
            : ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in2_mem_wb)
                ? vlSelfRef.top__DOT__u_cpu__DOT__wb_rd_data
                : vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs2_data));
    vlSelfRef.top__DOT__u_cpu__DOT__fwd_jalr_rs1 = 
        ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in1_ex_mem)
          ? vlSelfRef.top__DOT__u_cpu__DOT__ex_mem_result
          : ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__fwd_alu_in1_mem_wb)
              ? vlSelfRef.top__DOT__u_cpu__DOT__wb_rd_data
              : vlSelfRef.top__DOT__u_cpu__DOT__id_ex_rs1_data));
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2 = 0U;
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_bypass) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_out = 0U;
    } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__imm_to_reg) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_out 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__imm;
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
            = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__use_pc)
                ? vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__pc
                : ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in1_ex_mem)
                    ? vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__ex_mem_rd_data
                    : ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in1_mem_wb)
                        ? vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__mem_wb_rd_data
                        : vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__r_data1)));
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2 
            = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__use_imm)
                ? vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__imm
                : ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in2_ex_mem)
                    ? vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__ex_mem_rd_data
                    : ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__fwd_alu_in2_mem_wb)
                        ? vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__mem_wb_rd_data
                        : vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__r_data2)));
        vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_out 
            = ((8U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                ? ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                    ? ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                        ? 0U : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                                 ? (VL_LTS_III(32, vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1, vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)
                                     ? 1U : 0U) : (
                                                   (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                                    < vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)
                                                    ? 1U
                                                    : 0U)))
                    : ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                        ? ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                            ? VL_SHIFTRS_III(32,32,5, vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1, 
                                             (0x0000001fU 
                                              & vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2))
                            : (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                               >> (0x0000001fU & vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)))
                        : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                            ? 0U : (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                    << (0x0000001fU 
                                        & vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)))))
                : ((4U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                    ? ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                        ? ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                            ? 0U : (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                    & vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2))
                        : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                            ? (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                               | vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)
                            : (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                               ^ vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)))
                    : ((2U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                        ? 0U : ((1U & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_op))
                                 ? (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                    - vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)
                                 : (vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data1 
                                    + vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__data2)))));
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_rs2_val 
        = vlSelfRef.top__DOT__u_cpu__DOT__fwd_store_data;
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__rs1_in 
        = vlSelfRef.top__DOT__u_cpu__DOT__fwd_jalr_rs1;
    vlSelfRef.top__DOT__u_cpu__DOT__alu_out = vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_out;
    vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__out_zero 
        = (0U == vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__alu_out);
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in1 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pcinc_in1_pcor)
            ? vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__rs1_in
            : vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pc_in);
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in2 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__imm_in;
    vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pc_target 
        = (0xfffffffeU & (vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in1 
                          + vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__unnamedblk1__DOT__in2));
    vlSelfRef.top__DOT__u_cpu__DOT__ex_result = (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_jal) 
                                                  | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__id_ex_is_jalr))
                                                  ? vlSelfRef.top__DOT__u_cpu__DOT__pc_plus4
                                                  : vlSelfRef.top__DOT__u_cpu__DOT__alu_out);
    vlSelfRef.top__DOT__u_cpu__DOT__alu_zero = vlSelfRef.top__DOT__u_cpu__DOT__u_alu__DOT__out_zero;
    vlSelfRef.top__DOT__u_cpu__DOT__pc_target = vlSelfRef.top__DOT__u_cpu__DOT__u_pc__DOT__pc_target;
    vlSelfRef.top__DOT__u_cpu__DOT__u_ex_mem__DOT__i_result 
        = vlSelfRef.top__DOT__u_cpu__DOT__ex_result;
    vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__alu_zero 
        = vlSelfRef.top__DOT__u_cpu__DOT__alu_zero;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_pc 
        = vlSelfRef.top__DOT__u_cpu__DOT__pc_target;
    __Vtableidx2 = (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__alu_zero) 
                     << 3U) | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__id_ex_funct3));
    vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__branch_passed 
        = Vtop__ConstPool__TABLE_h50f0aed2_0[__Vtableidx2];
    vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__branch_taken 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__is_jal) 
           | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__is_jalr) 
              | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__is_branch) 
                 & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__branch_passed))));
    vlSelfRef.top__DOT__u_cpu__DOT__branch_taken = vlSelfRef.top__DOT__u_cpu__DOT__u_branch_unit__DOT__branch_taken;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect 
        = vlSelfRef.top__DOT__u_cpu__DOT__branch_taken;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__branch_taken 
        = vlSelfRef.top__DOT__u_cpu__DOT__branch_taken;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__branch_taken 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__branch_taken;
}

void Vtop___024root___nba_comb__TOP__25(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__25\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_data1 
        = ((((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_enable) 
             & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_addr) 
                == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr1)))
             ? vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_data
             : vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__registers
            [vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr1]) 
           & (- (IData)((0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr1)))));
    vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_data2 
        = ((((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_enable) 
             & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_addr) 
                == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr2)))
             ? vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__w_data
             : vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__registers
            [vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr2]) 
           & (- (IData)((0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_addr2)))));
    vlSelfRef.top__DOT__u_cpu__DOT__rs1_data = vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_data1;
    vlSelfRef.top__DOT__u_cpu__DOT__rs2_data = vlSelfRef.top__DOT__u_cpu__DOT__u_reg_file__DOT__r_data2;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs1_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__rs1_data;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__i_rs2_data 
        = vlSelfRef.top__DOT__u_cpu__DOT__rs2_data;
}

void Vtop___024root___nba_comb__TOP__26(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__26\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_clear = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_branch_flush = 0U;
    if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__freeze)))) {
        if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__wb_data_wait)))) {
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__data_fetch_valid) {
                if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__branch_taken) {
                    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_clear = 1U;
                    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_branch_flush = 1U;
                }
            }
        }
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_clear 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_branch_flush 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_branch_flush;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_if_id_clear 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_branch_flush 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_branch_flush;
    vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__clear 
        = vlSelfRef.top__DOT__u_cpu__DOT__hz_if_id_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__is_br_flush 
        = vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_branch_flush;
}

void Vtop___024root___nba_comb__TOP__27(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__27\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__pc_enable = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_enable = 1U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_clear = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_stall = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_l_use = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_instr = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__is_l_use_no_gap 
        = ((((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_mem_read) 
             & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_reg_write)) 
            & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_rd_not_x0)) 
           & (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_rs1_valid) 
               & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__dep_id_ex_rd_if_id_rs1)) 
              | ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_rs2_valid) 
                 & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__dep_id_ex_rd_if_id_rs2))));
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__freeze) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__pc_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_enable = 0U;
    } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__wb_data_wait) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__pc_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_stall = 1U;
    } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__data_fetch_valid) {
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__branch_taken) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_clear = 1U;
        } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__stop_in_flight) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_clear = 1U;
        } else if (vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__is_l_use_no_gap) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__pc_enable = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_enable = 0U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_clear = 1U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_stall = 1U;
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_l_use = 1U;
        } else {
            vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_instr = 1U;
        }
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__pc_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_enable = 0U;
        vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_stall = 1U;
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__pc_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__pc_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_clear 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__id_ex_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_is_stall 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_stall;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_is_l_use 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_l_use;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_is_instr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__meta_is_instr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__u_stall_unit__DOT__if_id_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_pc_enable = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__pc_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_id_ex_clear 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__id_ex_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_is_stall 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_is_stall;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_is_l_use 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_is_l_use;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_is_instr 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__meta_is_instr;
    vlSelfRef.top__DOT__u_cpu__DOT__hz_if_id_enable 
        = vlSelfRef.top__DOT__u_cpu__DOT__u_hazard_unit__DOT__if_id_enable;
    vlSelfRef.top__DOT__u_cpu__DOT__u_id_ex__DOT__clear 
        = vlSelfRef.top__DOT__u_cpu__DOT__hz_id_ex_clear;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__is_stall 
        = vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_is_stall;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__is_l_use 
        = vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_is_l_use;
    vlSelfRef.top__DOT__u_cpu__DOT__u_meta__DOT__is_instr 
        = vlSelfRef.top__DOT__u_cpu__DOT__hz_meta_is_instr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__stall 
        = (1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__hz_if_id_enable)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__stall 
        = (1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__hz_if_id_enable)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__stall)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect));
}

void Vtop___024root___nba_comb__TOP__28(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__28\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_redirect = 0U;
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_pend = 0U;
    if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid)))) {
        if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_redirect = 1U;
        }
        if ((1U & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff)))) {
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pend_valid) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_pend = 1U;
            }
        }
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__push_stale 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_from_hold) 
           & ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff) 
              | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_stale)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_arvalid 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid) 
           || ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff)
                ? VL_GTS_III(32, 2U, (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__inflight))
                : (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__space)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_araddr 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_valid)
            ? vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__hold_addr
            : ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff)
                ? vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_pc
                : ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pend_valid)
                    ? vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pend_pc
                    : vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__req_pc)));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_cb = 0U;
    if ((1U & ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff)) 
               & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__stall))))) {
        if ((0U != (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cap_cnt))) {
            vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_cb = 1U;
        }
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__ar_hs 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_arvalid) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_arready));
    vlSelfRef.top__DOT__u_cpu__DOT__if_arvalid = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_arvalid;
    vlSelfRef.top__DOT__u_cpu__DOT__if_araddr = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_araddr;
    vlSelfRef.top__DOT__if_arvalid = vlSelfRef.top__DOT__u_cpu__DOT__if_arvalid;
    vlSelfRef.top__DOT__if_araddr = vlSelfRef.top__DOT__u_cpu__DOT__if_araddr;
    vlSelfRef.top__DOT__u_mem__DOT__if_arvalid = vlSelfRef.top__DOT__if_arvalid;
    vlSelfRef.top__DOT__u_mem__DOT__if_araddr = vlSelfRef.top__DOT__if_araddr;
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_araddr 
        = vlSelfRef.top__DOT__u_mem__DOT__if_araddr;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_araddr 
        = (vlSelfRef.top__DOT__u_mem__DOT__if_araddr 
           - (IData)(0x00002000U));
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__araddr 
        = vlSelfRef.top__DOT__u_mem__DOT__if_araddr;
    vlSelfRef.top__DOT__u_mem__DOT__if_sel = (3U & 
                                              (((0x00002000U 
                                                 > vlSelfRef.top__DOT__u_mem__DOT__if_araddr)
                                                 ? 1U
                                                 : 
                                                (2U 
                                                 & (- (IData)(
                                                              (0x00022000U 
                                                               > vlSelfRef.top__DOT__u_mem__DOT__if_araddr))))) 
                                               | (- (IData)(
                                                            (vlSelfRef.top__DOT__u_mem__DOT__if_araddr 
                                                             >> 0x0000001fU)))));
    vlSelfRef.top__DOT__u_mem__DOT__rom_if_arvalid 
        = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__if_arvalid) 
           & (1U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel)));
    vlSelfRef.top__DOT__u_mem__DOT__ram_if_arvalid 
        = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__if_arvalid) 
           & (2U == (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel)));
    vlSelfRef.top__DOT__u_mem__DOT__dif_arvalid = ((IData)(vlSelfRef.top__DOT__u_mem__DOT__if_arvalid) 
                                                   & ((1U 
                                                       != (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel)) 
                                                      & (2U 
                                                         != (IData)(vlSelfRef.top__DOT__u_mem__DOT__if_sel))));
    vlSelfRef.top__DOT__u_mem__DOT__u_boot_rom__DOT__if_arvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__rom_if_arvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_ram__DOT__if_arvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__ram_if_arvalid;
    vlSelfRef.top__DOT__u_mem__DOT__u_default_if__DOT__arvalid 
        = vlSelfRef.top__DOT__u_mem__DOT__dif_arvalid;
}

void Vtop___024root___nba_comb__TOP__29(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_comb__TOP__29\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__r_good 
        = ((~ ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff) 
               | vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_stale
               [vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_head])) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__r_hs));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_r = 0U;
    if ((1U & ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__redirect_eff)) 
               & (~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__stall))))) {
        if ((0U == (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cap_cnt))) {
            if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__r_good) {
                vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_r = 1U;
            }
        }
    }
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_push 
        = ((~ (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_r)) 
           & (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__r_good));
    vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__fetch_valid 
        = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_cb) 
           | (IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_r));
    if (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_cb) {
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__instr_out 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_instr
            [vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head];
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pc_out 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_pc
            [vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head];
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__mem_fault 
            = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_fault
            [vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__cb_head];
    } else {
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__instr_out 
            = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_r)
                ? vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_rdata
                : 0x00000013U);
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pc_out 
            = (vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_pc
               [vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_head] 
               & (- (IData)((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_r))));
        vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__mem_fault 
            = ((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__deliver_from_r) 
               & (((IData)(vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__if_rresp) 
                   >> 1U) | vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_mis
                  [vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__af_head]));
    }
    vlSelfRef.top__DOT__u_cpu__DOT__fetch_valid = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__fetch_valid;
    vlSelfRef.top__DOT__u_cpu__DOT__instr = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__instr_out;
    vlSelfRef.top__DOT__u_cpu__DOT__fetch_pc = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__pc_out;
    vlSelfRef.top__DOT__u_cpu__DOT__if_fault_out = vlSelfRef.top__DOT__u_cpu__DOT__u_fetch__DOT__mem_fault;
    vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__i_instr 
        = vlSelfRef.top__DOT__u_cpu__DOT__instr;
    vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__i_pc 
        = vlSelfRef.top__DOT__u_cpu__DOT__fetch_pc;
    vlSelfRef.top__DOT__u_cpu__DOT__u_if_id__DOT__i_fault 
        = vlSelfRef.top__DOT__u_cpu__DOT__if_fault_out;
}

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((0x0000000003000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((0x000000000c000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((0x0000000000c00000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__2(vlSelf);
    }
    if ((0x00000000000c0000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__3(vlSelf);
    }
    if ((0x0000000030000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__4(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__5(vlSelf);
    }
    if ((0x00000000000000c0ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__6(vlSelf);
    }
    if ((0x000000000000000cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__7(vlSelf);
    }
    if ((0x0000003000000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__8(vlSelf);
    }
    if ((0x0000000000000300ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__9(vlSelf);
    }
    if ((0x0000000400000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__10(vlSelf);
    }
    if ((0x0000000000003000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__11(vlSelf);
    }
    if ((0x0000000100000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__12(vlSelf);
    }
    if ((0x0000000000000030ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__13(vlSelf);
    }
    if ((0x0000000000000c00ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__14(vlSelf);
    }
    if ((0x0000000300000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__15(vlSelf);
    }
    if ((0x0000000c00000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__16(vlSelf);
    }
    if ((0x00000000c0000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__17(vlSelf);
    }
    if ((0x0000000000300000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__18(vlSelf);
    }
    if ((0x000000c000000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__19(vlSelf);
    }
    if ((0x000000000000c000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__20(vlSelf);
    }
    if ((0x0000000000030000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__21(vlSelf);
    }
    if ((0x0000000003000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__22(vlSelf);
    }
    if ((0x000000000c000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__23(vlSelf);
    }
    if ((0x00000000000c0000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__24(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__25(vlSelf);
    }
    if ((0x000000000000300cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__0(vlSelf);
    }
    if ((0x0000000000003000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__26(vlSelf);
    }
    if ((0x0000000000000300ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__27(vlSelf);
    }
    if ((0x0000000000000f00ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__1(vlSelf);
    }
    if ((0x0000000000003c00ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__2(vlSelf);
    }
    if ((0x00000005c0000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__3(vlSelf);
    }
    if ((0x0000003fc0000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__4(vlSelf);
    }
    if ((0x0000000000303c00ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__5(vlSelf);
    }
    if ((0x0000000000300c00ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__6(vlSelf);
    }
    if ((0x000000cfc0000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__7(vlSelf);
    }
    if ((0x00000000c00f0000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__8(vlSelf);
    }
    if ((0x000000000f000000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__9(vlSelf);
    }
    if ((0x000000003c0c0000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__10(vlSelf);
    }
    if ((0x000000000000f00cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__11(vlSelf);
    }
    if ((0x00000005c00f0000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__12(vlSelf);
    }
    if ((0x000000cfc00f0000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__13(vlSelf);
    }
    if ((0x00000000c00f000cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__14(vlSelf);
    }
    if ((0x000000003ccc3000ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__15(vlSelf);
    }
    if ((0x00000005c00f000cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__16(vlSelf);
    }
    if ((0x000000cfc03f000cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__17(vlSelf);
    }
    if ((0x000000cfc00f300cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__18(vlSelf);
    }
    if ((0x000000cfc00ff00cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__19(vlSelf);
    }
    if ((0x00000000c03f000cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__20(vlSelf);
    }
    if ((0x00000005c03f000cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__21(vlSelf);
    }
    if ((0x000000cfc03ff00cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__22(vlSelf);
    }
    if ((0x000000cfc03f000cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__23(vlSelf);
    }
    if ((0x00000005c03f3c0cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__24(vlSelf);
    }
    if ((0x000000cfc03f033cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__25(vlSelf);
    }
    if ((0x000000cfc03ffc0cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__26(vlSelf);
    }
    if ((0x000000cfc03fff0cULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__27(vlSelf);
    }
    if ((0x000000cfc03fffccULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__28(vlSelf);
    }
    if ((0x000000ffc03fffccULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_comb__TOP__29(vlSelf);
    }
}

void Vtop___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtop___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vtop___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtop___024root___eval_phase__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtop___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtop___024root___eval_nba(vlSelf);
        Vtop___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("src/design\\top.sv", 5, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 10000 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = Vtop___024root___eval_phase__ico(vlSelf);
        vlSelfRef.__VicoFirstIteration = 0U;
    } while (vlSelfRef.__VicoPhaseResult);
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("src/design\\top.sv", 5, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("src/design\\top.sv", 5, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vtop___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtop___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst_n & 0xfeU)))) {
        Verilated::overWidthError("rst_n");
    }
    if (VL_UNLIKELY(((vlSelfRef.i_rx & 0xfeU)))) {
        Verilated::overWidthError("i_rx");
    }
}
#endif  // VL_DEBUG
