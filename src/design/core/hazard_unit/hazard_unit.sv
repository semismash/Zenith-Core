import rv32i::*;

module hazard_unit (
    // IF/ID (incl. OpCode bits)
    input OpCode if_id_opcode,  // x
    input OpCode id_ex_opcode,  // x
    input RegAddr if_id_rs1,    // x
    input RegAddr if_id_rs2,    // x
    // ID/EX
    input RegAddr id_ex_rs1,    // x
    input RegAddr id_ex_rs2,    // x
    input RegAddr id_ex_rd,     // x
    // EX/MEM
    input RegAddr ex_mem_rd,    // x
    // MEM/WB
    input RegAddr mem_wb_rd,    // x
    // TO STALL UNIT DIRECTLY
    input logic id_ex_mem_read,     // if load (X)
    input logic id_ex_reg_write,    // if reg write (X)
    input logic branch_taken,       // check if a branch was taken, to stall control hazards for now (X)
    input logic data_fetch_valid,   // x
    input logic wb_data_wait,       // load in WB without its R (X)
    input logic freeze,             // sticky STOP / HALT (X)
    input logic stop_in_flight,     // ECALL / EBREAK in EX, MEM or WB (X)
    // TO FORWARDING UNIT DIRECTLY
    input logic ex_mem_reg_write,   // x
    input logic mem_wb_reg_write,   // x
    // OUTPUTS
    // STALLING
    output logic pc_enable,     // x
    output logic if_id_enable,  // x
    output logic id_ex_enable,  // x
    output logic ex_mem_enable, // x
    output logic mem_wb_enable, // x
    output logic if_id_clear,   // x
    output logic id_ex_clear,   // x
    // FORWARDING
    output logic fwd_alu_in1_ex_mem, // forward to alu in 1 from src res in ex mem (X)
    output logic fwd_alu_in2_ex_mem, // forward to alu in 2 from src res in ex mem (X)
    output logic fwd_alu_in1_mem_wb, // forward to alu in 1 from src res in ex mem (X)
    output logic fwd_alu_in2_mem_wb, // forward to alu in 2 from src res in ex mem (X)
    // METADATA
    output logic meta_branch_flush, // x
    output logic meta_is_stall,     // x
    output logic meta_is_l_use,     // x
    output logic meta_is_instr      // if decoded instruction advanced this cycle (X)
);

    // connecting ports between dep analyzer and fwd unit/stall unit
    logic dep_id_ex_rd_if_id_rs1;
    logic dep_id_ex_rd_if_id_rs2;
    logic dep_ex_mem_rd_id_ex_rs1;
    logic dep_ex_mem_rd_id_ex_rs2;
    logic dep_mem_wb_rd_id_ex_rs1;
    logic dep_mem_wb_rd_id_ex_rs2;

    logic id_ex_rs1_not_x0;
    logic id_ex_rs2_not_x0;
    logic id_ex_rd_not_x0;

    logic if_id_rs1_valid;
    logic if_id_rs2_valid;
    logic id_ex_rs1_valid;
    logic id_ex_rs2_valid;

    dep_analyzer u_dep_analyzer (
        // dependency analyzer
        // IF/ID (incl. OpCode bits)
        .if_id_opcode               (if_id_opcode),     // x
        .id_ex_opcode               (id_ex_opcode),     // x
        .if_id_rs1                  (if_id_rs1),        // x
        .if_id_rs2                  (if_id_rs2),        // x
        // ID/EX
        .id_ex_rs1                  (id_ex_rs1),        // x
        .id_ex_rs2                  (id_ex_rs2),        // x
        .id_ex_rd                   (id_ex_rd),  
        // EX/MEM
        .ex_mem_rd                  (ex_mem_rd),        // x
        // MEM/WB
        .mem_wb_rd                  (mem_wb_rd),        // x
        // outputs (naming scheme = dep_source_dest)
        // ID/EX
        .dep_id_ex_rd_if_id_rs1     (dep_id_ex_rd_if_id_rs1),   // x
        .dep_id_ex_rd_if_id_rs2     (dep_id_ex_rd_if_id_rs2),   // x
        // EX/MEM
        .dep_ex_mem_rd_id_ex_rs1    (dep_ex_mem_rd_id_ex_rs1),  // x
        .dep_ex_mem_rd_id_ex_rs2    (dep_ex_mem_rd_id_ex_rs2),  // x
        // MEM/WB
        .dep_mem_wb_rd_id_ex_rs1    (dep_mem_wb_rd_id_ex_rs1),  // x
        .dep_mem_wb_rd_id_ex_rs2    (dep_mem_wb_rd_id_ex_rs2),  // x
        // extra bits to check if its not zero regiter
        .id_ex_rs1_not_x0           (id_ex_rs1_not_x0), // x
        .id_ex_rs2_not_x0           (id_ex_rs2_not_x0), // x
        .id_ex_rd_not_x0            (id_ex_rd_not_x0),  // x
        // check if rs1 or rs2 usage is even valid
        // for stall unit (lcad use with no gap)
        .if_id_rs1_valid            (if_id_rs1_valid),  // x
        .if_id_rs2_valid            (if_id_rs2_valid),  // x
        // for forwardable hazards
        .id_ex_rs1_valid            (id_ex_rs1_valid),  // x
        .id_ex_rs2_valid            (id_ex_rs2_valid)   // x
    );

    stall_unit u_stall_unit (
        // ID/EX - IF/ID dependencies
        .dep_id_ex_rd_if_id_rs1    (dep_id_ex_rd_if_id_rs1),    // x
        .dep_id_ex_rd_if_id_rs2    (dep_id_ex_rd_if_id_rs2),    // x
        // non-zero bits to prevent accidental stalls if using locked zero register
        .id_ex_rd_not_x0           (id_ex_rd_not_x0),           // x
        // classification bits to check read and write to stall accordingly
        .id_ex_mem_read            (id_ex_mem_read), // if load (load-use)                                              // x
        .id_ex_reg_write           (id_ex_reg_write), // if writing to reg (mostly to disqualify non-load instructions) // x
        .branch_taken              (branch_taken), // check if a branch was taken, to stall control hazards for now     // x
        .data_fetch_valid          (data_fetch_valid),  // x
        .wb_data_wait              (wb_data_wait),      // x
        .freeze                    (freeze),            // x
        .stop_in_flight            (stop_in_flight),    // x
        // if read registers are even valid to begin with
        .if_id_rs1_valid           (if_id_rs1_valid),
        .if_id_rs2_valid           (if_id_rs2_valid),
        // OUTPUTS
        .pc_enable                 (pc_enable),     // x
        .if_id_enable              (if_id_enable),  // x
        .id_ex_enable              (id_ex_enable),  // x
        .ex_mem_enable             (ex_mem_enable), // x
        .mem_wb_enable             (mem_wb_enable), // x
        .if_id_clear               (if_id_clear),   // x
        .id_ex_clear               (id_ex_clear),   // x
        // METADATA
        .meta_branch_flush         (meta_branch_flush), // x
        .meta_is_stall             (meta_is_stall),     // x
        .meta_is_l_use             (meta_is_l_use),     // x
        .meta_is_instr             (meta_is_instr)      // x
    );

    fwd_unit u_fwd_unit (
        // Dependencies
        // ID/EX
        .dep_id_ex_rd_if_id_rs1     (dep_id_ex_rd_if_id_rs1),   // x
        .dep_id_ex_rd_if_id_rs2     (dep_id_ex_rd_if_id_rs2),   // x
        // EX/MEM
        .dep_ex_mem_rd_id_ex_rs1    (dep_ex_mem_rd_id_ex_rs1),  // x
        .dep_ex_mem_rd_id_ex_rs2    (dep_ex_mem_rd_id_ex_rs2),  // x
        // MEM/WB
        .dep_mem_wb_rd_id_ex_rs1    (dep_mem_wb_rd_id_ex_rs1),  // x
        .dep_mem_wb_rd_id_ex_rs2    (dep_mem_wb_rd_id_ex_rs2),  // x
        // non-zero bits to prevent accidental stalls if using locked zero register
        .id_ex_rs1_not_x0           (id_ex_rs1_not_x0),     // x
        .id_ex_rs2_not_x0           (id_ex_rs2_not_x0),     // x
        // if read registers are even valid to begin with
        .id_ex_rs1_valid            (id_ex_rs1_valid),      // x
        .id_ex_rs2_valid            (id_ex_rs2_valid),      // x
        // write signal from registers
        .ex_mem_reg_write           (ex_mem_reg_write),     // x
        .mem_wb_reg_write           (mem_wb_reg_write),     // x
        // OUTPUT
        .fwd_alu_in1_ex_mem         (fwd_alu_in1_ex_mem), // forward to alu in 1 from src res in ex mem (X)
        .fwd_alu_in2_ex_mem         (fwd_alu_in2_ex_mem), // forward to alu in 2 from src res in ex mem (X)
        .fwd_alu_in1_mem_wb         (fwd_alu_in1_mem_wb), // forward to alu in 1 from src res in ex mem (X)
        .fwd_alu_in2_mem_wb         (fwd_alu_in2_mem_wb)  // forward to alu in 2 from src res in ex mem (X)
    );

endmodule