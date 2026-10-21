import rv32i::*;

// NOTE: The RTL in this file was re-written using AI using logic dictated by the programmer, and was then human reviewed and tested.

module write_back (
    // removed the placeholder "input rd_addr," port (trailing comma, no type)
    input  logic [2:0] funct3,      // load width / signedness, carried through MEM/WB
    input  logic [1:0] addr_lo,     // byte offset of the load inside the aligned word
    input  logic       mem_to_reg,  // 1 = load result, 0 = ALU / PC+4 result
    input  Word        result,      // ALU / PC+4 value carried through MEM/WB
    input  Word        data_rdata,  // aligned word straight from the data bus R channel
    input  Resp        data_rresp,  // R response of that word
    output Word        rd_data,     // value written to the register file (also the MEM/WB forwarding source)
    output logic       load_fault   // the load's R came back with an error, the core gates reg_write off
);

    // write back logic compressed into a single module

    Word shifted;                   // wanted byte / halfword moved down to lane 0
    Word load_val;

    always_comb begin                                                       
        shifted = data_rdata >> {addr_lo, 3'b000};                          // master picks the lane (slave always returns the aligned word)
        case (funct3)                                                       // moved here from the old LSU reg_data logic
            3'b000:  load_val = {{24{shifted[7]}},  shifted[7:0]};          // lb
            3'b001:  load_val = {{16{shifted[15]}}, shifted[15:0]};         // lh
            3'b100:  load_val = {24'b0, shifted[7:0]};                      // lbu
            3'b101:  load_val = {16'b0, shifted[15:0]};                     // lhu
            default: load_val = shifted;                                    // lw
        endcase                                                             
        rd_data = mem_to_reg ? load_val : result;                           // the mem_to_reg mux that used to be in the LSU
    end                                                                     

    assign load_fault = mem_to_reg && data_rresp[1];                        // RDATA is never used on an error

endmodule