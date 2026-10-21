import rv32i::*;

module if_id (  // 65 bits
    input logic clk,
    input logic rst_n,  // asynchronous active low reset
    input logic stall,
    input logic clear,  // synchronous active high clear

    input Word i_pc,
    input Instruction i_instr,
    input logic i_fault,

    output Word o_pc,
    output Instruction o_instr,
    output logic o_fault
);

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin       // async reset split from the synchronous clear (was `!rst_n || clear`, a sim/synthesis mismatch)
            o_pc <= '0;
            o_instr <= NOP_INSTR;
            o_fault <= 1'b0;
        end else if (clear) begin
            o_pc    <= '0;
            o_instr <= NOP_INSTR;
            o_fault <= 1'b0;
        end else if (!stall) begin  // do normal logic if NOT a stall
            o_pc    <= i_pc;
            o_instr <= i_instr;
            o_fault <= i_fault;
        end
    end

endmodule