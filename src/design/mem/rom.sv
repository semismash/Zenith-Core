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
`ifdef VERILATOR
        // simulation: the testbench passes the program with +ROM_HEX=<path> (one 32-bit hex word per line)
        string hex_file;
        if (!$value$plusargs("ROM_HEX=%s", hex_file)) hex_file = "bios.hex";
        $readmemh(hex_file, container);
`else
        // synthesis: src/fpga/build.tcl writes rom_init_path.vh (`define ROM_INIT_FILE "<absolute path of bios.hex>") and
        // adds its folder to the include path. An absolute path is always found, and if the file is missing the
        // build stops instead of silently leaving the ROM empty
        `include "rom_init_path.vh"
        $readmemh(`ROM_INIT_FILE, container);
`endif
    end

    assign if_arready   = 1'b1;     // always accepts (single-cycle address handshake)
    assign data_arready = 1'b1;     
    assign data_awready = 1'b1;     
    assign data_wready  = 1'b1;     
    assign if_rresp     = RESP_OKAY;    
    assign data_rresp   = RESP_OKAY;    
    assign data_bresp   = RESP_SLVERR;  // ROM is write protected

    // Two synchronous read ports (dual-port ROM), written with EXPLICIT 1024-word banks (one 36 Kbit block RAM each).
    // Every bank is read on every access into its own output register, and the bank select is a register loaded under the
    // same enable as the data. The mux after the registers therefore always uses the select that belongs to the data it
    // picks, whatever the synthesis tool decides about splitting a deep memory over several block RAMs. (A bank boundary
    // crossed by straight-line code worked in simulation but broke on the board.)
    localparam int BANK_AW    = 10;                                            // 1024 words per bank
    localparam int BANK_WORDS = 1 << BANK_AW;
    localparam int NUM_BANKS  = (ROM_WORDS + BANK_WORDS - 1) / BANK_WORDS;     // 2 for the 8 KiB ROM
    localparam int SEL_W      = (NUM_BANKS > 1) ? $clog2(NUM_BANKS) : 1;

    Word              if_bank   [NUM_BANKS-1:0];
    Word              data_bank [NUM_BANKS-1:0];
    logic [SEL_W-1:0] if_sel;
    logic [SEL_W-1:0] data_sel;

    always_ff @(posedge clk) begin
        for (int b = 0; b < NUM_BANKS; b++) begin
            if (if_arvalid)   if_bank[b]   <= container[b * BANK_WORDS + int'(if_araddr[BANK_AW+1:2])];
            if (data_arvalid) data_bank[b] <= container[b * BANK_WORDS + int'(data_araddr[BANK_AW+1:2])];
        end
        if (if_arvalid)   if_sel   <= SEL_W'(if_araddr   >> (BANK_AW + 2));
        if (data_arvalid) data_sel <= SEL_W'(data_araddr >> (BANK_AW + 2));
    end

    assign if_rdata   = if_bank[if_sel];
    assign data_rdata = data_bank[data_sel];

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