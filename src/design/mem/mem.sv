import rv32i::*;

// NOTE: The RTL in this file was re-written and optimized with the help of AI using logic dictated by the programmer, and was then human reviewed and tested.

module mem #(
    parameter ROM_SIZE_BYTES = 8192,
    parameter RAM_SIZE_BYTES = 131072
) (
    input logic clk,
    input logic rst_n,

    // instruction fetch: absolute address, full memory map; AXI4-Lite read-only slave port (instruction side)
    input  Word  if_araddr,         
    input  logic if_arvalid,        
    output logic if_arready,        
    output Word  if_rdata,          
    output logic if_rvalid,         
    input  logic if_rready,         
    output Resp  if_rresp,          

    // data access: absolute address, full memory map; AXI4-Lite read / write slave port (data side)
    // ROM is protected: reads are allowed, writes are disallowed;  a write to ROM is answered SLVERR
    // MMIO starts from address 0x80000000, handled by LSU itself(split off into data_decoder.sv)
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

    // LEGEND
    // --------------------------------------------------------------------------------------------
    // slave-side wires (rom_*, ram_*, dif_* = default slave instruction side, ddt_* = default slave data side)
    // --------------------------------------------------------------------------------------------

    logic rom_if_arvalid, rom_if_arready, rom_if_rvalid;    Word rom_if_rdata;  Resp rom_if_rresp;    
    logic ram_if_arvalid, ram_if_arready, ram_if_rvalid;    Word ram_if_rdata;  Resp ram_if_rresp;    
    logic dif_arvalid,    dif_arready,    dif_rvalid;       Word dif_rdata;     Resp dif_rresp;       
    logic dif_awready, dif_wready, dif_bvalid;              Resp dif_bresp;                           // unused

    logic rom_d_arvalid, rom_d_arready, rom_d_rvalid;       Word rom_d_rdata;   Resp rom_d_rresp;     
    logic ram_d_arvalid, ram_d_arready, ram_d_rvalid;       Word ram_d_rdata;   Resp ram_d_rresp;     
    logic ddt_arvalid,   ddt_arready,   ddt_rvalid;         Word ddt_rdata;     Resp ddt_rresp;       
    logic rom_d_awvalid, rom_d_wvalid, rom_d_awready, rom_d_wready, rom_d_bvalid;  Resp rom_d_bresp;  
    logic ram_d_awvalid, ram_d_wvalid, ram_d_awready, ram_d_wready, ram_d_bvalid;  Resp ram_d_bresp;  
    logic ddt_awvalid,   ddt_wvalid,   ddt_awready,   ddt_wready,   ddt_bvalid;    Resp ddt_bresp;    

    // instruction fetch; decoder ROM / RAM / default, select register steers the R response back
    Region if_sel;
    Region if_sel_q;
    assign if_sel = region_of(if_araddr);                           
    assign rom_if_arvalid = if_arvalid && (if_sel == REGION_ROM);   // only the selected slave sees ARVALID
    assign ram_if_arvalid = if_arvalid && (if_sel == REGION_RAM);   
    assign dif_arvalid    = if_arvalid && (if_sel != REGION_ROM) && (if_sel != REGION_RAM);    // unmapped or MMIO fetch -> DECERR

    always_comb begin                                               
        case (if_sel)                                               
            REGION_ROM: if_arready = rom_if_arready;                
            REGION_RAM: if_arready = ram_if_arready;                
            default:    if_arready = dif_arready;                   
        endcase                                                     
        case (if_sel_q)                                             
            REGION_ROM: begin if_rvalid = rom_if_rvalid; if_rdata = rom_if_rdata; if_rresp = rom_if_rresp; end  
            REGION_RAM: begin if_rvalid = ram_if_rvalid; if_rdata = ram_if_rdata; if_rresp = ram_if_rresp; end  
            default:    begin if_rvalid = dif_rvalid;    if_rdata = dif_rdata;    if_rresp = dif_rresp;    end  
        endcase                                                     
    end                                                             

    // data access routing: ROM below RAM_BASE (read only), RAM from RAM_BASE up, neither for MMIO (handled by the LSU)  // same routing, now as two decoders (read and write)
    Region rd_sel, rd_sel_q;                                        // replaces data_sel_rom / data_sel_ram (reads)
    Region wr_sel, wr_sel_q;                                        // for writes lol
    assign rd_sel = region_of(data_araddr);                         
    assign wr_sel = region_of(data_awaddr);                         // W is steered with the AW address (sent in the same cycle)

    assign rom_d_arvalid = data_arvalid && (rd_sel == REGION_ROM);  
    assign ram_d_arvalid = data_arvalid && (rd_sel == REGION_RAM);  
    assign ddt_arvalid   = data_arvalid && (rd_sel != REGION_ROM) && (rd_sel != REGION_RAM);    
    assign rom_d_awvalid = data_awvalid && (wr_sel == REGION_ROM);  
    assign ram_d_awvalid = data_awvalid && (wr_sel == REGION_RAM);  
    assign ddt_awvalid   = data_awvalid && (wr_sel != REGION_ROM) && (wr_sel != REGION_RAM);    
    assign rom_d_wvalid  = data_wvalid  && (wr_sel == REGION_ROM);  
    assign ram_d_wvalid  = data_wvalid  && (wr_sel == REGION_RAM);  
    assign ddt_wvalid    = data_wvalid  && (wr_sel != REGION_ROM) && (wr_sel != REGION_RAM);    

    always_comb begin                                               
        case (rd_sel)                                               
            REGION_ROM: data_arready = rom_d_arready;               
            REGION_RAM: data_arready = ram_d_arready;               
            default:    data_arready = ddt_arready;                 
        endcase                                                     
        case (wr_sel)                                               
            REGION_ROM: begin data_awready = rom_d_awready; data_wready = rom_d_wready; end  
            REGION_RAM: begin data_awready = ram_d_awready; data_wready = ram_d_wready; end  
            default:    begin data_awready = ddt_awready;   data_wready = ddt_wready;   end  
        endcase                                                     
        case (rd_sel_q)                                             // R back from the slave that took the AR
            REGION_ROM: begin data_rvalid = rom_d_rvalid; data_rdata = rom_d_rdata; data_rresp = rom_d_rresp; end  
            REGION_RAM: begin data_rvalid = ram_d_rvalid; data_rdata = ram_d_rdata; data_rresp = ram_d_rresp; end  
            default:    begin data_rvalid = ddt_rvalid;   data_rdata = ddt_rdata;   data_rresp = ddt_rresp;   end  
        endcase                                                     
        case (wr_sel_q)                                             // B back from the slave that took the write
            REGION_ROM: begin data_bvalid = rom_d_bvalid; data_bresp = rom_d_bresp; end    
            REGION_RAM: begin data_bvalid = ram_d_bvalid; data_bresp = ram_d_bresp; end    
            default:    begin data_bvalid = ddt_bvalid;   data_bresp = ddt_bresp;   end    
        endcase                                                     
    end                                                             

    always_ff @(posedge clk or negedge rst_n) begin                 // one select register per direction (fixed latency slaves, a cache would need a FIFO of selects)
        if (!rst_n) begin                                           
            if_sel_q <= REGION_ROM;     // reset victor fetches from ROM first
            rd_sel_q <= REGION_NONE;                                
            wr_sel_q <= REGION_NONE;                                
        end else begin                                              
            if (if_arvalid   && if_arready)                   if_sel_q <= if_sel;  
            if (data_arvalid && data_arready)                 rd_sel_q <= rd_sel;  
            if (data_awvalid && data_wvalid && data_awready && data_wready) wr_sel_q <= wr_sel;  
        end                                                         
    end                                                             

    rom #(
        .ROM_SIZE_BYTES(ROM_SIZE_BYTES)
    ) u_boot_rom (
        .clk             (clk),
        .rst_n           (rst_n), 
        // port A (instruction), ROM starts at 0 (offset = 0)
        .if_araddr       (if_araddr - ROM_BASE),     
        .if_arvalid      (rom_if_arvalid),          
        .if_arready      (rom_if_arready),          
        .if_rdata        (rom_if_rdata),            
        .if_rvalid       (rom_if_rvalid),           
        .if_rready       (if_rready),               
        .if_rresp        (rom_if_rresp),            
        // port B (data), ROM rejects stores (SLVERR)
        .data_araddr     (data_araddr - ROM_BASE),   
        .data_arvalid    (rom_d_arvalid),           
        .data_arready    (rom_d_arready),           
        .data_rdata      (rom_d_rdata),             
        .data_rvalid     (rom_d_rvalid),            
        .data_rready     (data_rready),             
        .data_rresp      (rom_d_rresp),             
        .data_awaddr     (data_awaddr - ROM_BASE),   
        .data_awvalid    (rom_d_awvalid),           
        .data_awready    (rom_d_awready),           
        .data_wdata      (data_wdata),              
        .data_wstrb      (data_wstrb),              
        .data_wvalid     (rom_d_wvalid),            
        .data_wready     (rom_d_wready),            
        .data_bvalid     (rom_d_bvalid),            
        .data_bready     (data_bready),             
        .data_bresp      (rom_d_bresp)              
    );

    ram #(
        .RAM_SIZE_BYTES(RAM_SIZE_BYTES)
    ) u_ram (
        .clk             (clk),
        .rst_n           (rst_n),
        // port A (instruction), relative to RAM_BASE
        .if_araddr       (if_araddr - RAM_BASE),     
        .if_arvalid      (ram_if_arvalid),          
        .if_arready      (ram_if_arready),          
        .if_rdata        (ram_if_rdata),            
        .if_rvalid       (ram_if_rvalid),           
        .if_rready       (if_rready),               
        .if_rresp        (ram_if_rresp),            
        // port B (data)
        .data_araddr     (data_araddr - RAM_BASE),   
        .data_arvalid    (ram_d_arvalid),           
        .data_arready    (ram_d_arready),           
        .data_rdata      (ram_d_rdata),             
        .data_rvalid     (ram_d_rvalid),            
        .data_rready     (data_rready),             
        .data_rresp      (ram_d_rresp),             
        .data_awaddr     (data_awaddr - RAM_BASE),   
        .data_awvalid    (ram_d_awvalid),           
        .data_awready    (ram_d_awready),           
        .data_wdata      (data_wdata),              
        .data_wstrb      (data_wstrb),              
        .data_wvalid     (ram_d_wvalid),            
        .data_wready     (ram_d_wready),            
        .data_bvalid     (ram_d_bvalid),            
        .data_bready     (data_bready),             
        .data_bresp      (ram_d_bresp)              
    );

    default_slave u_default_if (    // unmapped / MMIO instruction fetches
        .clk     (clk),             
        .rst_n   (rst_n),           
        .araddr  (if_araddr),       
        .arvalid (dif_arvalid),     
        .arready (dif_arready),     
        .rdata   (dif_rdata),       
        .rvalid  (dif_rvalid),      
        .rready  (if_rready),       
        .rresp   (dif_rresp),       
        .awaddr  ('0),              // instruction side has no write channels
        .awvalid (1'b0),            
        .awready (dif_awready),     
        .wdata   ('0),              
        .wstrb   ('0),              
        .wvalid  (1'b0),            
        .wready  (dif_wready),      
        .bvalid  (dif_bvalid),      
        .bready  (1'b1),            
        .bresp   (dif_bresp)        
    );

    default_slave u_default_data (  // Nunmapped data accesses
        .clk     (clk),             
        .rst_n   (rst_n),           
        .araddr  (data_araddr),     
        .arvalid (ddt_arvalid),     
        .arready (ddt_arready),     
        .rdata   (ddt_rdata),       
        .rvalid  (ddt_rvalid),      
        .rready  (data_rready),     
        .rresp   (ddt_rresp),       
        .awaddr  (data_awaddr),     
        .awvalid (ddt_awvalid),     
        .awready (ddt_awready),     
        .wdata   (data_wdata),      
        .wstrb   (data_wstrb),      
        .wvalid  (ddt_wvalid),      
        .wready  (ddt_wready),      
        .bvalid  (ddt_bvalid),      
        .bready  (data_bready),     
        .bresp   (ddt_bresp)        
    );

endmodule