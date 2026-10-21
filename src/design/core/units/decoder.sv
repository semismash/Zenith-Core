import rv32i::*;

module decoder #(
    parameter DATA_WIDTH = rv32i::DATA_WIDTH,
    parameter ADDR_WIDTH = rv32i::ADDR_WIDTH
) (
    input Instruction instr,    // instruction
    //input logic alu_zero,       // feedback from ALU to resolve branch conditions

    // ID/EX
    output RegAddr rs1_addr,
    output RegAddr rs2_addr,
    output RegAddr rd_addr,

    // branches
    output logic is_branch,
    output logic is_jal,
    output logic is_jalr,

    // ALU
    output AluOp alu_op,        // alu specific operation
    output logic alu_in1_ropc,  // picks between alu first input being reg(0) or pc(1)
    output logic alu_in2_roi,   // picks between alu second input being reg(0) or imm(1)
    output logic alu_bypass,

    // REG FILE
    output logic reg_write,     // if it writes back to a register

    // LSU
    output logic mem_read,      // mem read signal to lsu
    output logic mem_write,     // if writes to data memory (for OP_S)
    output logic mem_to_reg,    // chooses between routing alu output (0) and data mem output from load (1) to reg file
    output logic imm_to_reg,    // when high, write imm to reg directly, hence bypassing alu, used by lui

    // IMM GEN
    output Word imm_val,            // immediate value as output

    // PC
    output logic pcinc_in1_pcor,    // PC inc input 1, default PC (0) or rs1 (1)
    //output logic pcinc_in2_doi,     // PC inc input 2, default 4 (0) or IMM (1); PC = in1 + in2

    // funct3
    output logic [2:0] funct3,

    // panic
    output logic illegal_instr,     // detects illegal instr, panics respectively
    output logic stop               // stop, but propagates through pipeline without emergency halt
);

    import rv32i::*;

    OpCode opcode;
    ImmPackFmt imm_type;

    assign rs1_addr = RegAddr'(instr[19:15]);
    assign rs2_addr = RegAddr'(instr[24:20]);
    assign rd_addr = RegAddr'(instr[11:7]);
    
    assign funct3 = instr[14:12];

    function automatic AluOp calc_alu_op(input logic is_r_type);
        AluOp return_op;
        return_op = ADD;
        case (funct3)
            3'b000: begin
                if (is_r_type && instr[30] == 1'b1) return_op = SUB;
                else return_op = ADD;
            end
            3'b100: return_op = XOR;
            3'b110: return_op = OR;
            3'b111: return_op = AND;
            3'b001: return_op = SLL;
            3'b101: begin  // SRLI/SRAI legitimately use instr[30] even for I-type
                if (instr[30] == 1'b0) return_op = SRL;
                else return_op = SRA;
            end
            3'b010: return_op = SLT;
            3'b011: return_op = SLTU;
            default: return_op = ADD;
        endcase
        return return_op;
    endfunction

    always_comb begin

        opcode = OpCode'(instr[6:0]);

        alu_in1_ropc = 1'b0;    // by default, take alu 1 from register
        alu_in2_roi  = 1'b1;    // by default, take alu 2 from imm gen
        alu_bypass   = 1'b0;

        reg_write    = 1'b0;    // by default, dont write back to reg file
        mem_write    = 1'b0;    // by default, don't write to mem
        mem_read     = 1'b0;    // by default, don't mem read

        alu_op = ADD;           // default op is add
        mem_to_reg   = 1'b0;    // by default, always take from alu output to reg file
        imm_to_reg   = 1'b0;    // only set by lui

        pcinc_in1_pcor   = 1'b0;    // by default, always increment pc instead of set
        //pcinc_in2_doi    = 1'b0;    // by default, pc always incremented by 4

        is_branch   = 1'b0;
        is_jal      = 1'b0;
        is_jalr     = 1'b0;

        imm_type = N;
        illegal_instr = 1'b0;
        stop = 1'b0;

        case (opcode)
            OP_R: begin
                reg_write = 1'b1;
                alu_op = calc_alu_op(1'b1);   // is_r_type = 1
                alu_in2_roi = 1'b0;
                if (!((instr[31:25] == 7'b0000000) || (instr[31:25] == 7'b0100000 && (funct3 == 3'b000 || funct3 == 3'b101)))) begin  // only funct7 0000000, or 0100000 for SUB/SRA, is RV32I (e.g. M-extension MUL used to silently decode as ADD)
                    illegal_instr = 1'b1;
                end
            end
            OP_I: begin
                reg_write = 1'b1;
                alu_op = calc_alu_op(1'b0);   // is_r_type = 0
                imm_type = I;
                if ((funct3 == 3'b001 && instr[31:25] != 7'b0000000) ||
                    (funct3 == 3'b101 && instr[31:25] != 7'b0000000 && instr[31:25] != 7'b0100000)) begin
                    illegal_instr = 1'b1;   // invalid shift encoding
                end
                if (instr == NOP_INSTR) reg_write = 1'b0;   // insert canonical NOP
            end
            OP_I_L: begin   // x
                reg_write = 1'b1; 
                mem_to_reg = 1'b1;  // route from data mem to reg file
                mem_read = 1'b1;
                imm_type = I;
                if (funct3 == 3'b011 || funct3 == 3'b110 || funct3 == 3'b111) illegal_instr = 1'b1;
            end
            OP_I_E: begin   
                alu_bypass = 1'b1;  // don't write to reg, so garbage ALU inputs are harmless here
                imm_type = I;
                stop = 1'b1;        // ecall and ebreak will stop the CPU for now
            end
            OP_S: begin 
                mem_write = 1'b1;
                imm_type = S;
                if (funct3 > 3'b010) illegal_instr = 1'b1;  // only SB/SH/SW exist
            end
            OP_B: begin
                alu_in2_roi = 1'b0;
                case (funct3)
                    3'b000:  begin alu_op = XOR;  end // BEQ: jump if A^B == 0
                    3'b001:  begin alu_op = XOR;  end // BNE: jump if A^B != 0
                    3'b100:  begin alu_op = SLT;  end // BLT: jump if SLT result != 0
                    3'b101:  begin alu_op = SLT;  end // BGE: jump if SLT result == 0
                    3'b110:  begin alu_op = SLTU; end // BLTU: same as above but unsigned
                    3'b111:  begin alu_op = SLTU; end // BGEU
                    default: begin alu_op = ADD; illegal_instr = 1'b1; end
                endcase
                imm_type = B;
                is_branch = 1'b1;
            end
            OP_J: begin
                reg_write = 1'b1; 
                alu_in1_ropc = 1'b1;    // input is PC instead
                //pcinc_in2_doi = 1'b1;
                imm_type = J;
                is_jal = 1'b1;
            end
            OP_I_J: begin
                reg_write = 1'b1; 
                alu_in1_ropc = 1'b1;
                pcinc_in1_pcor = 1'b1;
                //pcinc_in2_doi  = 1'b1;  // PC = rs1 + imm
                imm_type = I;
                is_jalr = 1'b1;
                if (funct3 != 3'b000) illegal_instr = 1'b1;
            end
            OP_LUI: begin
                reg_write = 1'b1; 
                imm_to_reg = 1'b1;   // route lui straight to reg file, remove alu bypass function
                imm_type = U;
            end
            OP_AUIPC: begin
                reg_write = 1'b1; 
                alu_in1_ropc = 1'b1;
                imm_type = U;
            end
            OP_FENCE: begin 
                if (funct3 != 3'b000) illegal_instr = 1'b1;
            end
            default: begin 
                illegal_instr = 1'b1;
            end
        endcase

    end

    imm_gen u_imm_gen(
        .instr          (instr),
        .imm_type       (imm_type),
        .imm_out        (imm_val)
    );
    
endmodule