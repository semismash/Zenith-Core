import rv32i::*;

module rom #(   // currently houses only the bootloader
    parameter ROM_SIZE_BYTES = 8192   // 8 KiB, size of ROM
) (
    input  logic clk,
    input  logic rst_n,

    // port A, instruction fetch (read only); addresses arrive already steered here and relative to the ROM base
    input  Word  if_araddr,         
    input  logic if_arvalid,        
    output logic if_arready,        // constant 1
    output Word  if_rdata,          // block RAM output register
    output logic if_rvalid,         // one cycle after the AR handshake
    input  logic if_rready,         // unused, masters keep RREADY at 1
    output Resp  if_rresp,          

    // port B, data (read only, every write is answered SLVERR and nothing is written)
    input  Word  data_araddr,       
    input  logic data_arvalid,      
    output logic data_arready,      
    output Word  data_rdata,        
    output logic data_rvalid,       
    input  logic data_rready,       // unused
    output Resp  data_rresp,        
    input  Word  data_awaddr,       // unused (ROM is write protected)
    input  logic data_awvalid,      
    output logic data_awready,      
    input  Word  data_wdata,        // unused
    input  logic [3:0] data_wstrb,  // unused
    input  logic data_wvalid,       
    output logic data_wready,       
    output logic data_bvalid,       
    input  logic data_bready,       // unused
    output Resp  data_bresp         
);

    localparam int ROM_WORDS = ROM_SIZE_BYTES / 4;      // word-wide storage so Vivado can map it to block RAM
    localparam int ROM_AW    = $clog2(ROM_WORDS);       // word index width

    // bounds are decoded in mem.sv, unmapped goes to the default slave

    Word container [ROM_WORDS - 1:0];
    initial begin
        $readmemh("bios.hex", container);    // PLACEHOLDER PATH TO BIOS BINARY
    end

    assign if_arready   = 1'b1;     // always accepts (single-cycle address handshake)
    assign data_arready = 1'b1;     
    assign data_awready = 1'b1;     
    assign data_wready  = 1'b1;     
    assign if_rresp     = RESP_OKAY;    
    assign data_rresp   = RESP_OKAY;    
    assign data_bresp   = RESP_SLVERR;  // ROM is write protected

    always_ff @(posedge clk) begin                                          // two synchronous read ports (dual-port ROM)
        if (if_arvalid)   if_rdata   <= container[if_araddr[ROM_AW+1:2]];   
        if (data_arvalid) data_rdata <= container[data_araddr[ROM_AW+1:2]]; 
    end                                                                     

    always_ff @(posedge clk or negedge rst_n) begin                         // RD_IDLE / RD_RESP and WR_IDLE / WR_RESP
        if (!rst_n) begin                                                   
            if_rvalid   <= 1'b0;                                            
            data_rvalid <= 1'b0;                                            
            data_bvalid <= 1'b0;                                            
        end else begin                                                      
            if_rvalid   <= if_arvalid;                                      
            data_rvalid <= data_arvalid;                                    
            data_bvalid <= data_awvalid && data_wvalid;                     // write accepted (and ignored), answer SLVERR
        end                                                                 
    end                                                                     

endmodule