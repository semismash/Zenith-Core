import rv32i::*;

module mem_wb ( // 45 bits
    input logic clk,
    input logic rst_n,  // asynchronous active low reset
    input logic stall,
    input logic clear,  // synchronous active high clear

    input RegAddr i_rd_addr,      // 5 bits
    input Word i_result,          // 32 bits 
    input logic i_reg_write,      // 1 bit
    input logic i_mem_to_reg,     // 1 bit; loads
    input logic [2:0] i_funct3,   // 3 bits; load_width
    input logic [1:0] i_addr_lo,  // 2 bits; byte offset inside the aligned word
    input logic i_is_stop,        // 1 bit

    output RegAddr o_rd_addr,
    output Word o_result,
    output logic o_reg_write,
    output logic o_mem_to_reg,    
    output logic [2:0] o_funct3,  
    output logic [1:0] o_addr_lo, 
    output logic o_is_stop
);

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            o_rd_addr       <= '0;
            o_result        <= '0;
            o_reg_write     <= '0;
            o_mem_to_reg    <= '0;  
            o_funct3        <= '0;  
            o_addr_lo       <= '0;  
            o_is_stop       <= '0;
        end else if (clear) begin   // synchronous clear (bubble while MEM waits), now its own branch
            o_rd_addr       <= '0;  
            o_result        <= '0;  
            o_reg_write     <= '0;  
            o_mem_to_reg    <= '0;  
            o_funct3        <= '0;  
            o_addr_lo       <= '0;  
            o_is_stop       <= '0;  
        end else if (!stall) begin  // do normal logic if NOT a stall
            o_rd_addr       <= i_rd_addr;
            o_result        <= i_result;
            o_reg_write     <= i_reg_write;
            o_mem_to_reg    <= i_mem_to_reg;    
            o_funct3        <= i_funct3;        
            o_addr_lo       <= i_addr_lo;       
            o_is_stop       <= i_is_stop;
        end
    end

endmodule