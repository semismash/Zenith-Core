import rv32i::*;

module ex_mem ( // 77 bits
    input logic clk,
    input logic rst_n,  // asynchronous active low reset
    input logic stall,
    input logic clear,  // synchronous active high clear

    input Word i_rs2_val,         // 32 bits
    input RegAddr i_rd_addr,      // 5 bits
    input Word i_result,          // 32 bits
    input logic i_mem_read,       // 1 bit
    input logic i_mem_write,      // 1 bit
    input logic [2:0] i_funct3,   // 3 bits
    input logic i_reg_write,      // 1 bit
    input logic i_mem_to_reg,     // 1 bit
    input logic i_is_stop,        // 1 bit

    output Word o_rs2_val,
    output RegAddr o_rd_addr,
    output Word o_result,
    output logic o_mem_read,
    output logic o_mem_write,
    output logic [2:0] o_funct3,
    output logic o_reg_write,
    output logic o_mem_to_reg,
    output logic o_is_stop        // replaces o_valid_instr
);

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin   // async reset split from the synchronous clear (was `!rst_n || clear`, a sim/synthesis mismatch)
            o_rs2_val       <= '0;
            o_rd_addr       <= '0;
            o_result        <= '0;
            o_mem_read      <= '0;
            o_mem_write     <= '0;
            o_funct3        <= '0;
            o_reg_write     <= '0;
            o_mem_to_reg    <= '0;
            o_is_stop       <= '0;
        end else if (clear) begin   // synchronous clear, now its own branch
            o_rs2_val       <= '0;
            o_rd_addr       <= '0;
            o_result        <= '0;
            o_mem_read      <= '0;
            o_mem_write     <= '0;
            o_funct3        <= '0;
            o_reg_write     <= '0;
            o_mem_to_reg    <= '0;
            o_is_stop       <= '0;
        end else if (!stall) begin  // do normal logic if NOT a stall
            o_rs2_val       <= i_rs2_val;
            o_rd_addr       <= i_rd_addr;
            o_result        <= i_result;
            o_mem_read      <= i_mem_read;
            o_mem_write     <= i_mem_write;
            o_funct3        <= i_funct3;
            o_reg_write     <= i_reg_write;
            o_mem_to_reg    <= i_mem_to_reg;
            o_is_stop       <= i_is_stop;   // replaces o_valid_instr
        end
    end

endmodule