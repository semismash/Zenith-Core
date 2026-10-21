import rv32i::*;

module pc(
    
    input logic pcinc_in1_pcor, // choose whether in1 of alu inc is pc or rs1
    input Word rs1_in,      // take rs1 if req
    input Word pc_in,       // take pc value from pipeline register to accurate jump
    input Word imm_in,      // take imm_in if req

    output Word pc_target   // PC target out (based on branch instructions)
);

    // note: PC+4 has now been moved into fetch_sv as the +4 incrmeentation could be done to multiple sources (see fetch.sv)

    always_comb begin
        Word in1;
        Word in2;
        if (pcinc_in1_pcor == 1'b1) begin
            in1 = rs1_in;
        end else begin
            in1 = pc_in;
        end
        in2 = imm_in;
        pc_target = (in1 + in2) & ~Word'(32'b1);
    end

endmodule