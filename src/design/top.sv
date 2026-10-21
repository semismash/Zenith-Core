import rv32i::*;

// NOTE: The RTL in this file was rewritten with the help of AI using logic dictated by the programmer, and was then human reviewed and tested.

module top(
    input logic clk,    // clock; 100 MHz board oscillator (E3), the core runs on the 10 MHz MMCM output
    input logic rst_n,  // active low reset; reset button (C2), synchronized below before it reaches the core

    // debugging
    output logic [3:0] led,     // [0] stop, [1] instruction fault, [2] data fault, [3] illegal instruction (all sticky until reset)
    // CPU I/O
    input logic i_rx,       // usb_uart_rxd (A9)
    output logic o_tx       // usb_uart_txd (D10)

    // telemetry data
    // output MetaCount meta_instr_count,
    // output MetaCount meta_stall_count,
    // output MetaCount meta_l_use_count,
    // output MetaCount meta_br_flush_count
);

    // ------------------------------------------------------------------------------------------
    // clock: 100 MHz -> 10 MHz (MMCM: VCO = 100 MHz x 10 = 1000 MHz, CLKOUT0 = 1000 / 100 = 10 MHz)
    // Xilinx primitives don't exist in Verilator, so in simulation the input clock drives the core directly
    // ------------------------------------------------------------------------------------------
    logic cpu_clk;          // core clock
    logic mmcm_locked;

`ifndef VERILATOR
    logic clkfb;            // MMCM feedback
    logic clkfb_buf;
    logic clk_10m;          // unbuffered MMCM output

    MMCME2_BASE #(                          
        .BANDWIDTH          ("OPTIMIZED"),  
        .CLKIN1_PERIOD      (10.0),         // 100 MHz in
        .DIVCLK_DIVIDE      (1),            
        .CLKFBOUT_MULT_F    (10.0),         // VCO 1000 MHz (Artix-7 -1 range 600 - 1200 MHz)
        .CLKOUT0_DIVIDE_F   (100.0),        // 10 MHz
        .CLKOUT0_DUTY_CYCLE (0.5),          
        .CLKOUT0_PHASE      (0.0),          
        .STARTUP_WAIT       ("FALSE")       
    ) u_mmcm (                              
        .CLKIN1    (clk),                   
        .CLKFBIN   (clkfb_buf),             
        .CLKFBOUT  (clkfb),                 
        .CLKFBOUTB (),                      
        .CLKOUT0   (clk_10m),               
        .CLKOUT0B  (),                      
        .CLKOUT1   (),                      
        .CLKOUT1B  (),                      
        .CLKOUT2   (),                      
        .CLKOUT2B  (),                      
        .CLKOUT3   (),                      
        .CLKOUT3B  (),                      
        .CLKOUT4   (),                      
        .CLKOUT5   (),                      
        .CLKOUT6   (),                      
        .LOCKED    (mmcm_locked),           
        .PWRDWN    (1'b0),                  
        .RST       (1'b0)                   
    );                                      

    BUFG u_bufg_fb  (.I(clkfb),   .O(clkfb_buf));   
    BUFG u_bufg_clk (.I(clk_10m), .O(cpu_clk));     
`else
    assign cpu_clk     = clk;               // simulation, no MMCM
    assign mmcm_locked = 1'b1;              
`endif

    // reset: asynchronous assert, synchronous release (2 flops on the core clock), held until the MMCM locks
    logic [1:0] rst_sync;                   
    logic       core_rst_n;                 
    always_ff @(posedge cpu_clk or negedge rst_n) begin     
        if (!rst_n)            rst_sync <= 2'b00;           
        else if (!mmcm_locked) rst_sync <= 2'b00;           
        else                   rst_sync <= {rst_sync[0], 1'b1};    
    end                                                     
    assign core_rst_n = rst_sync[1];                        

    // from CPU
    // NOTE: sim_main.cpp reads some of these through Verilator, it needs updating for the new names below
    Word  if_araddr         /* verilator public_flat_rw */;    // instruction port
    logic if_arvalid        /* verilator public_flat_rw */;    
    logic if_arready;                                       
    logic if_rvalid         /* verilator public_flat_rw */;    
    logic if_rready;                                        
    Word  if_rdata          /* verilator public_flat_rw */;    
    Resp  if_rresp;                                         

    Word  data_awaddr       /* verilator public_flat_rw */;    // data port (RAM / ROM traffic, MMIO stays inside the core)
    logic data_awvalid      /* verilator public_flat_rw */;    
    logic data_awready;                                     
    Word  data_wdata        /* verilator public_flat_rw */;    
    logic [3:0] data_wstrb  /* verilator public_flat_rw */; 
    logic data_wvalid;                                      
    logic data_wready;                                      
    logic data_bvalid;                                      
    logic data_bready;                                      
    Resp  data_bresp;                                       
    Word  data_araddr       /* verilator public_flat_rw */;    
    logic data_arvalid      /* verilator public_flat_rw */;    
    logic data_arready;                                     
    Word  data_rdata        /* verilator public_flat_rw */;    
    logic data_rvalid;                                      
    logic data_rready;                                      
    Resp  data_rresp;                                       

    logic halt              /* verilator public_flat_rw */;
    logic instr_fault;                                      
    logic data_fault;                                       
    logic illegal_instr;                                    
    logic stop              /* verilator public_flat_rw */;    

    assign led = {illegal_instr, data_fault, instr_fault, stop};   // LD7..LD4 order is set in the .xdc

    rv32i_core u_cpu (
        // clock and reset
        .clk (cpu_clk),                     // 10 MHz core clock
        .rst_n (core_rst_n),                // synchronized reset
        // AXI4-Lite instruction port
        .if_araddr      (if_araddr),        
        .if_arvalid     (if_arvalid),       
        .if_arready     (if_arready),       
        .if_rvalid      (if_rvalid),        
        .if_rready      (if_rready),        
        .if_rdata       (if_rdata),         
        .if_rresp       (if_rresp),         
        // AXI4-Lite data port
        .data_awaddr    (data_awaddr),      
        .data_awvalid   (data_awvalid),     
        .data_awready   (data_awready),     
        .data_wdata     (data_wdata),       
        .data_wstrb     (data_wstrb),       
        .data_wvalid    (data_wvalid),      
        .data_wready    (data_wready),      
        .data_bvalid    (data_bvalid),      
        .data_bready    (data_bready),      
        .data_bresp     (data_bresp),       
        .data_araddr    (data_araddr),      
        .data_arvalid   (data_arvalid),     
        .data_arready   (data_arready),     
        .data_rdata     (data_rdata),       
        .data_rvalid    (data_rvalid),      
        .data_rready    (data_rready),      
        .data_rresp     (data_rresp),       
        // HALT
        .halt (halt),   // x
        .instr_fault_out    (instr_fault),  // x
        .data_fault_out     (data_fault),   // x
        .illegal_instr_out  (illegal_instr),  // x
        .stop (stop),   // x
        // UART
        .i_rx (i_rx),
        .o_tx (o_tx)
        // TELEMETRY
        // .meta_instr_count (meta_instr_count),       // x
        // .meta_stall_count (meta_stall_count),       // x
        // .meta_l_use_count (meta_l_use_count),       // x
        // .meta_br_flush_count (meta_br_flush_count)  // x
    );


    mem #(
        .ROM_SIZE_BYTES     (ROM_SIZE_BYTES),   // x
        .RAM_SIZE_BYTES     (RAM_SIZE_BYTES)    // x
    ) u_mem (
        .clk                (cpu_clk),          // 10 MHz core clock
        .rst_n              (core_rst_n),       // synchronized reset
        // instruction fetch; AXI4-Lite slave port
        .if_araddr          (if_araddr),        
        .if_arvalid         (if_arvalid),       
        .if_arready         (if_arready),       
        .if_rdata           (if_rdata),         
        .if_rvalid          (if_rvalid),        
        .if_rready          (if_rready),        
        .if_rresp           (if_rresp),         
        // data access; AXI4-Lite slave port
        .data_araddr        (data_araddr),      
        .data_arvalid       (data_arvalid),     
        .data_arready       (data_arready),     
        .data_rdata         (data_rdata),       
        .data_rvalid        (data_rvalid),      
        .data_rready        (data_rready),      
        .data_rresp         (data_rresp),       
        .data_awaddr        (data_awaddr),      
        .data_awvalid       (data_awvalid),     
        .data_awready       (data_awready),     
        .data_wdata         (data_wdata),       
        .data_wstrb         (data_wstrb),       
        .data_wvalid        (data_wvalid),      
        .data_wready        (data_wready),      
        .data_bvalid        (data_bvalid),      
        .data_bready        (data_bready),      
        .data_bresp         (data_bresp)        
    );
    
endmodule