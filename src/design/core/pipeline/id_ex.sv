import rv32i::*;

module id_ex (  // 163 bits
    input logic clk,
    input logic rst_n,  // asynchronous active low reset
    input logic stall,
    input logic clear,  // synchronous active high clear

    input OpCode i_opcode,        // 7 bits
    input Word i_pc,              // 32 bits
    input RegAddr i_rs1_addr,     // 5 bits
    input RegAddr i_rs2_addr,     // 5 bits
    input RegAddr i_rd_addr,      // 5 bits
    input Word i_rs1_data,        // 32 bits
    input Word i_rs2_data,        // 32 bits
    input Word i_imm_val,         // 32 bits
    input logic i_alu_in1_ropc,   // 1 bit
    input logic i_alu_in2_roi,    // 1 bit
    input AluOp i_alu_op,         // 4 bits
    input logic i_alu_bypass,     // 1 bit
    input logic i_mem_read,       // 1 bit
    input logic i_mem_write,      // 1 bit
    input logic [2:0] i_funct3,   // 3 bits
    input logic i_pc_in1_sel,     // 1 bit
    input logic i_is_branch,      // 1 bit
    input logic i_is_jal,         // 1 bit
    input logic i_is_jalr,        // 1 bit
    input logic i_reg_write,      // 1 bit
    input logic i_imm_to_reg,     // 1 bit
    input logic i_mem_to_reg,     // 1 bit
    input logic i_is_stop,        // 1 bit
    input logic i_illegal,        // 1 bit
    input logic i_if_fault,       // 1 bit

    output OpCode o_opcode,
    output Word o_pc,
    output RegAddr o_rs1_addr,
    output RegAddr o_rs2_addr,
    output RegAddr o_rd_addr,
    output Word o_rs1_data,
    output Word o_rs2_data,
    output Word o_imm_val,
    output logic o_alu_in1_ropc,
    output logic o_alu_in2_roi,
    output AluOp o_alu_op,
    output logic o_alu_bypass,
    output logic o_mem_read,
    output logic o_mem_write,
    output logic [2:0] o_funct3,
    output logic o_pc_in1_sel,
    output logic o_is_branch,
    output logic o_is_jal,
    output logic o_is_jalr,
    output logic o_reg_write,
    output logic o_imm_to_reg,
    output logic o_mem_to_reg,
    output logic o_is_stop,       
    output logic o_illegal,
    output logic o_if_fault
);

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin   // async reset split from the synchronous clear
            o_opcode       <= OP_I;    // bubble opcode canonical NOP
            o_pc           <= '0;
            o_rs1_addr     <= '0;
            o_rs2_addr     <= '0;
            o_rd_addr      <= '0;
            o_rs1_data     <= '0;
            o_rs2_data     <= '0;
            o_imm_val      <= '0;
            o_alu_in1_ropc <= '0;
            o_alu_in2_roi  <= 1'b1;    // NOP takes ALU in2 from imm, same as the decoder's output for addi
            o_alu_op       <= ADD;    // add by default
            o_alu_bypass   <= '0;
            o_mem_read     <= '0;
            o_mem_write    <= '0;
            o_funct3       <= '0;
            o_pc_in1_sel   <= '0;
            o_is_branch    <= '0;
            o_is_jal       <= '0;
            o_is_jalr      <= '0;
            o_reg_write    <= '0;
            o_imm_to_reg   <= '0;
            o_mem_to_reg   <= '0;
            o_is_stop      <= '0;    
            o_illegal      <= '0;    
            o_if_fault     <= '0;    
        end else if (clear) begin   // synchronous clear (flush / load-use bubble / stop squash), now its own branch
            o_opcode       <= OP_I;   
            o_pc           <= '0;     
            o_rs1_addr     <= '0;     
            o_rs2_addr     <= '0;     
            o_rd_addr      <= '0;     
            o_rs1_data     <= '0;     
            o_rs2_data     <= '0;     
            o_imm_val      <= '0;     
            o_alu_in1_ropc <= '0;     
            o_alu_in2_roi  <= 1'b1;   
            o_alu_op       <= ADD;    
            o_alu_bypass   <= '0;     
            o_mem_read     <= '0;     
            o_mem_write    <= '0;     
            o_funct3       <= '0;     
            o_pc_in1_sel   <= '0;     
            o_is_branch    <= '0;     
            o_is_jal       <= '0;     
            o_is_jalr      <= '0;     
            o_reg_write    <= '0;     
            o_imm_to_reg   <= '0;     
            o_mem_to_reg   <= '0;     
            o_is_stop      <= '0;     
            o_illegal      <= '0;     
            o_if_fault     <= '0;     
        end else if (!stall) begin  // do normal logic if NOT a stall
            o_opcode       <= i_opcode;
            o_pc           <= i_pc;
            o_rs1_addr     <= i_rs1_addr;
            o_rs2_addr     <= i_rs2_addr;
            o_rd_addr      <= i_rd_addr;
            o_rs1_data     <= i_rs1_data;
            o_rs2_data     <= i_rs2_data;
            o_imm_val      <= i_imm_val;
            o_alu_in1_ropc <= i_alu_in1_ropc;
            o_alu_in2_roi  <= i_alu_in2_roi;
            o_alu_op       <= i_alu_op;
            o_alu_bypass   <= i_alu_bypass;
            o_mem_read     <= i_mem_read;
            o_mem_write    <= i_mem_write;
            o_funct3       <= i_funct3;
            o_pc_in1_sel   <= i_pc_in1_sel;
            o_is_branch    <= i_is_branch;
            o_is_jal       <= i_is_jal;
            o_is_jalr      <= i_is_jalr;
            o_reg_write    <= i_reg_write;
            o_imm_to_reg   <= i_imm_to_reg;
            o_mem_to_reg   <= i_mem_to_reg;
            o_is_stop      <= i_is_stop;
            o_illegal      <= i_illegal;
            o_if_fault     <= i_if_fault;
        end
    end

endmodule