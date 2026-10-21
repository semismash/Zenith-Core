import rv32i::*;

module default_slave (
    input  logic       clk,
    input  logic       rst_n,
    // read address / read data
    input  Word        araddr,      // unused, kept for a complete interface
    input  logic       arvalid,
    output logic       arready,
    output Word        rdata,
    output logic       rvalid,
    input  logic       rready,      // unused, masters keep RREADY at 1
    output Resp        rresp,
    // write address / write data / write response
    input  Word        awaddr,      // unused
    input  logic       awvalid,
    output logic       awready,
    input  Word        wdata,       // unused
    input  logic [3:0] wstrb,       // unused
    input  logic       wvalid,
    output logic       wready,
    output logic       bvalid,
    input  logic       bready,      // unused, masters keep BREADY at 1
    output Resp        bresp
);

    // AXI4-Lite default slave for unmapped addresses (one instance per side inside mem.sv)
    // always accepts, always answers DECERR one cycle later, so a request can never hang the bus

    assign arready = 1'b1;
    assign awready = 1'b1;
    assign wready  = 1'b1;
    assign rdata   = '0;
    assign rresp   = RESP_DECERR;
    assign bresp   = RESP_DECERR;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rvalid <= 1'b0;
            bvalid <= 1'b0;
        end else begin
            rvalid <= arvalid;              // RD_IDLE / RD_RESP
            bvalid <= awvalid && wvalid;    // WR_IDLE / WR_RESP (AW and W arrive together)
        end
    end

endmodule