import rv32i::*;

module ram #(
    parameter RAM_SIZE_BYTES = 131072    // 128 KiB BRAM
) (
    input logic clk,
    input logic rst_n,

    // PORT A: instruction mem; AXI4-Lite read-only slave, addresses arrive steered here and relative to RAM_BASE
    input  Word  if_araddr,
    input  logic if_arvalid,
    output logic if_arready,
    output Word  if_rdata,
    output logic if_rvalid,
    input  logic if_rready,
    output Resp  if_rresp,

    // PORT B: data mem; AXI4-Lite read / write slave
    input  Word  data_araddr,
    input  logic data_arvalid,
    output logic data_arready,
    output Word  data_rdata,
    output logic data_rvalid,
    input  logic data_rready,
    output Resp  data_rresp,
    input  Word  data_awaddr,
    input  logic data_awvalid,
    output logic data_awready,
    input  Word  data_wdata,
    input  logic [3:0] data_wstrb,
    input  logic data_wvalid,
    output logic data_wready,
    output logic data_bvalid,
    input  logic data_bready,
    output Resp  data_bresp
);

    localparam int RAM_WORDS = RAM_SIZE_BYTES / 4;      // word-wide storage with byte enables (block RAM friendly)
    localparam int RAM_AW    = $clog2(RAM_WORDS);       // word index width

    Word container [RAM_WORDS - 1:0];   // word array (for new word-wise addressign and safety)

    assign if_arready   = 1'b1;     // always accepts (single-cycle address handshake)
    assign data_arready = 1'b1;
    assign data_awready = 1'b1;     // no B response is ever left unaccepted (BREADY is constant 1)
    assign data_wready  = 1'b1;
    assign if_rresp     = RESP_OKAY;
    assign data_rresp   = RESP_OKAY;
    assign data_bresp   = RESP_OKAY;

    // PORT A:
    always_ff @(posedge clk) begin                                          // synchronous read, output register = RDATA
        if (if_arvalid) if_rdata <= container[if_araddr[RAM_AW+1:2]];       
    end                                                                     

    // PORT B:
    logic             b_write;                                              
    logic [RAM_AW-1:0] b_idx;                                               // one address per port so it maps to a true dual-port block RAM
    assign b_write = data_awvalid && data_wvalid;                           // the LSU sends AW and W together
    assign b_idx   = b_write ? data_awaddr[RAM_AW+1:2] : data_araddr[RAM_AW+1:2];  // a load and a store never share a cycle (one instruction in MEM)

    always_ff @(posedge clk) begin                                          
        if (b_write) begin                                                  // synchronous byte-enabled write, lands at the end of the accept cycle
            for (int i = 0; i < 4; i++) begin                               
                if (data_wstrb[i]) container[b_idx][8*i +: 8] <= data_wdata[8*i +: 8];  
            end                                                             
        end                                                                 
        if (data_arvalid) data_rdata <= container[b_idx];                   // synchronous read
    end                                                                     

    always_ff @(posedge clk or negedge rst_n) begin                         // RD_IDLE / RD_RESP and WR_IDLE / WR_RESP
        if (!rst_n) begin                                                   // goy
            if_rvalid   <= 1'b0;                                            
            data_rvalid <= 1'b0;                                            
            data_bvalid <= 1'b0;                                            
        end else begin                                                      
            if_rvalid   <= if_arvalid;                                      
            data_rvalid <= data_arvalid;                                    
            data_bvalid <= b_write;                                         
        end                                                                 
    end                                                                     

endmodule