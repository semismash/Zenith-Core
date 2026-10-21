import rv32i::*;

module branch_unit (
    input logic is_branch,
    input logic is_jal,
    input logic is_jalr,
    input logic [2:0] id_ex_funct3,
    input logic alu_zero,
    
    output logic branch_taken
);

    logic branch_passed;

    always_comb begin
        case (id_ex_funct3)
            3'b000:  branch_passed = alu_zero;   // BEQ
            3'b001:  branch_passed = !alu_zero;  // BNE
            3'b100:  branch_passed = !alu_zero;  // BLT
            3'b101:  branch_passed = alu_zero;   // BGE
            3'b110:  branch_passed = !alu_zero;  // BLTU
            3'b111:  branch_passed = alu_zero;   // BGEU
            default: branch_passed = 1'b0;
        endcase
    end

    // do branch taken only if actually a branch instruction
    assign branch_taken = is_jal || is_jalr || (is_branch && branch_passed);

endmodule