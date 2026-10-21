// NOTE: The RTL in this file was optimized with the help of AI using logic dictated by the programmer, and was then human reviewed and tested.

module stall_unit(
    // ID/EX - IF/ID dependencies
    input logic dep_id_ex_rd_if_id_rs1,
    input logic dep_id_ex_rd_if_id_rs2,
    // non-zero bits to prevent accidental stalls if using locked zero register
    input logic id_ex_rd_not_x0,
    // classification bits to check read and write to stall accordingly
    input logic id_ex_mem_read,     // if load (load-use)
    input logic id_ex_reg_write,    // if writing to reg (mostly to disqualify non-load instructions)
    input logic branch_taken,       // check if a branch was taken, to stall control hazards for now
    input logic data_fetch_valid,   // for load-store unit = !mem_stage_busy (request not accepted yet, or MMIO store waiting for its B)
    input logic wb_data_wait,       // load in WB and its R has not arrived -> freeze every stage
    input logic freeze,             // sticky STOP or HALT -> CPU frozen until reset
    input logic stop_in_flight,     // ECALL / EBREAK in EX, MEM or WB, so anything in ID is younger than it
    // if read registers are even valid to begin with
    input logic if_id_rs1_valid,
    input logic if_id_rs2_valid,
    // OUTPUTS
    output logic if_id_clear,
    output logic id_ex_clear,
    output logic pc_enable,
    output logic if_id_enable,
    output logic id_ex_enable,
    output logic ex_mem_enable,
    output logic mem_wb_enable,
    // METADATA
    output logic meta_branch_flush,
    output logic meta_is_stall,
    output logic meta_is_l_use,
    output logic meta_is_instr
);

    // stall unit currently handles two things -
    // 1. load-use hazards with 0 instruction gap (to be kept with this use for the forseeable future)
    // 2. control hazards (to create bubbles, to be shifted out soon with branch prediction implementation)

    logic is_l_use_no_gap;

    always_comb begin

        pc_enable       = 1'b1;
        if_id_enable    = 1'b1;
        id_ex_enable    = 1'b1;
        ex_mem_enable   = 1'b1;
        mem_wb_enable   = 1'b1;
        if_id_clear     = 1'b0;
        id_ex_clear     = 1'b0;

        meta_is_stall       = 1'b0;
        meta_is_l_use       = 1'b0;
        meta_branch_flush   = 1'b0;
        meta_is_instr       = 1'b0;

        is_l_use_no_gap = id_ex_mem_read && id_ex_reg_write && id_ex_rd_not_x0 &&
            ((if_id_rs1_valid && dep_id_ex_rd_if_id_rs1) || (if_id_rs2_valid && dep_id_ex_rd_if_id_rs2));

        if (freeze) begin                       // STOP / HALT, hold every stage, nothing is counted
            pc_enable       = 1'b0;             
            if_id_enable    = 1'b0;             
            id_ex_enable    = 1'b0;             
            ex_mem_enable   = 1'b0;             
            mem_wb_enable   = 1'b0;             
        end else if (wb_data_wait) begin        // late load response, hold every stage (RREADY is 1, so WB must still be there when it arrives)
            pc_enable       = 1'b0;             
            if_id_enable    = 1'b0;             
            id_ex_enable    = 1'b0;             
            ex_mem_enable   = 1'b0;             
            mem_wb_enable   = 1'b0;             
            meta_is_stall   = 1'b1;             
        end else if (!data_fetch_valid) begin   // request not accepted yet or MMIO store waiting for its B, still freezes every stage (keeps forwarding sources stable)
            pc_enable       = 1'b0;
            if_id_enable    = 1'b0;
            id_ex_enable    = 1'b0;
            ex_mem_enable   = 1'b0;
            mem_wb_enable   = 1'b0;
            meta_is_stall   = 1'b1;
        end else if (branch_taken) begin  // prioritize control hazards
            if_id_clear         = 1'b1;
            id_ex_clear         = 1'b1;
            meta_branch_flush   = 1'b1;
        end else if (stop_in_flight) begin
            id_ex_clear     = 1'b1;         // ID instruction becomes a NOP bubble in ID/EX
        end else if (is_l_use_no_gap) begin // stall for load-use no gap hazard
            pc_enable       = 1'b0;
            if_id_enable    = 1'b0;
            id_ex_clear     = 1'b1;
            meta_is_stall   = 1'b1;
            meta_is_l_use   = 1'b1;
        end else begin
            meta_is_instr   = 1'b1;
        end

    end

endmodule