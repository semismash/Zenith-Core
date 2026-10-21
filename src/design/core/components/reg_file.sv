import rv32i::*;

module reg_file 
#(
    parameter DATA_WIDTH = rv32i::DATA_WIDTH,
    parameter ADDR_WIDTH = rv32i::ADDR_WIDTH    // five bits = 32 registers for RISC-V
)(
    input logic clk,            // CPU clock
    input logic rst_n,          // active low reset

    input logic w_enable,       // write enable
    input RegAddr w_addr,       // write address
    input Word w_data,          // write data

    input RegAddr r_addr1,      // read address 1
    input RegAddr r_addr2,      // read address 2

    output Word r_data1,        // address 1 data out
    output Word r_data2         // address 2 data out
);

    Word registers [2**ADDR_WIDTH - 1:0];

    //hardwire zero register r0 to 0
    //assign r_data1 = (r_addr1 == {ADDR_WIDTH{1'b0}}) ? {DATA_WIDTH{1'b0}} : registers[r_addr1];
    //assign r_data2 = (r_addr2 == {ADDR_WIDTH{1'b0}}) ? {DATA_WIDTH{1'b0}} : registers[r_addr2];
    assign r_data1 = (r_addr1 == {ADDR_WIDTH{1'b0}}) ? {DATA_WIDTH{1'b0}} : (w_enable && w_addr == r_addr1) ? w_data : registers[r_addr1];
    assign r_data2 = (r_addr2 == {ADDR_WIDTH{1'b0}}) ? {DATA_WIDTH{1'b0}} : (w_enable && w_addr == r_addr2) ? w_data : registers[r_addr2];

    integer i;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin   // if reset high, set all registers back to zero
            for (i = 0; i < 2**ADDR_WIDTH; i = i + 1) begin
                registers[i] <= '0;
            end
        end else if (w_enable && (w_addr != {ADDR_WIDTH{1'b0}})) begin  // write only if w_enable
            registers[w_addr] <= w_data;
        end
    end

endmodule