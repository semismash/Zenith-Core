import rv32i::*;

// NOTE: The RTL in this file was re-written using AI using logic dictated by the programmer, and was then human reviewed and tested.

module lsu #(
    parameter DATA_WIDTH = rv32i::DATA_WIDTH
) (
    input logic clk,
    input logic rst_n,

    input logic [2:0] funct3,   // RV32I uses funct3 to differentiate between req_bytes for loads and stores
    input Word alu_res,         // ALU result to calculate load/store location
    input logic is_mem_read,    // if it is a mem read
    input logic is_mem_write,   // if write instruction to data memory
    input Word rs2_in,          // check rs2 if store

    // pipeline control
    input logic mem_advance,        // the MEM-stage instruction is replaced at the next clock edge (EX/MEM enable), clears the sent flags
    input logic freeze,             // CPU stopped or halted, no new requests are sent

    // AXI4-Lite master, read channels (data port)
    output Word  data_araddr,
    output logic data_arvalid,
    input  logic data_arready,
    input  logic data_rvalid,
    input  Resp  data_rresp,
    output logic data_rready,       // always held to 1 (optimization)
    // AXI4-Lite master, write channels
    output Word  data_awaddr,       // same ALU address, only the valid decides which channel is used
    output logic data_awvalid,      
    input  logic data_awready,      
    output Word  data_wdata,
    output logic [3:0] data_wstrb,
    output logic data_wvalid,       
    input  logic data_wready,       
    input  logic data_bvalid,
    input  Resp  data_bresp,        
    output logic data_bready,       // always held to 1 (optimization)

    // mem access validation for stalling during mem accesses
    output logic mem_stage_busy,    // high for as long as an access is still waiting to be completed
    output logic pre_fault,         // access rejected by the prechecks, no request sent (MEM/WB gates it into a bubble)
    output logic data_fault         // precheck fault | R with an error | B with an error
    // removed write_enable, reg_data, mem_valid, mem_req_start, mmio_data, mmio_access (MMIO now sits behind the data decoder)
);

    // check if instruction is a mem access
    logic is_access;
    assign is_access = is_mem_read || is_mem_write;

    // prechecks (alignment + memory map), done before any request is sent
    Region region;                                                  
    logic  misaligned;                                              
    assign region = region_of(alu_res);                             
    always_comb begin                                               
        case (funct3[1:0])                                          // 00 byte, 01 half, 10 word (11 is rejected by the decoder)
            2'b00:   misaligned = 1'b0;                             // bytes are always fine
            2'b01:   misaligned = (alu_res[1:0] == 2'b11);          // halfwords must stay inside one word
            default: misaligned = (alu_res[1:0] != 2'b00);          // words must be aligned
        endcase                                                     
    end                                                             
    // region overrun needs no separate check, an aligned access never crosses a word and every region is a multiple of 4 bytes
    assign pre_fault = is_access && (misaligned || (region == REGION_NONE) || (is_mem_write && region == REGION_ROM));  

    logic load_req;                                                 
    logic store_req;                                                
    logic is_mmio;                                                  
    assign load_req  = is_mem_read  && !pre_fault && !freeze;       // READY is constant 1, so gating VALID with freeze never drops a waiting request
    assign store_req = is_mem_write && !pre_fault && !freeze;       
    assign is_mmio   = (region == REGION_MMIO);                     

    // read channel
    logic ar_sent;                                                  // this MEM instruction's AR has been accepted
    logic ar_hs;                                                    
    logic ar_done;                                                  
    assign data_araddr  = alu_res;                                  // slave returns the aligned word, write_back.sv picks the lane
    assign data_arvalid = load_req && !ar_sent;                     // exactly one AR per load (keeps the UART RX pop single)
    assign data_rready  = 1'b1;                                     
    assign ar_hs        = data_arvalid && data_arready;             
    assign ar_done      = ar_sent || ar_hs;                         

    // write channels
    logic aw_sent;                                                  
    logic w_sent;                                                   
    logic wr_acc_q;                                                 // both AW and W accepted (registered)
    logic aw_hs;                                                    
    logic w_hs;                                                     
    logic wr_acc_now;                                               // the cycle the second of AW / W is accepted
    logic wr_accepted;                                              
    logic b_hs;                                                     
    logic [1:0] b_out;                                              // write responses still outstanding
    logic [1:0] b_out_next;                                         
    logic store_done;                                               
    logic [3:0] size_mask;                                          

    assign data_awaddr  = alu_res;                                  
    assign data_awvalid = store_req && !aw_sent;                    // each held until its own READY
    assign data_wvalid  = store_req && !w_sent;                     
    assign data_bready  = 1'b1;                                     
    assign aw_hs        = data_awvalid && data_awready;             
    assign w_hs         = data_wvalid && data_wready;               
    assign wr_acc_now   = store_req && !wr_acc_q && (aw_sent || aw_hs) && (w_sent || w_hs);    
    assign wr_accepted  = wr_acc_q || wr_acc_now;                   
    assign b_hs         = data_bvalid && data_bready;               
    assign b_out_next   = b_out + {1'b0, wr_acc_now} - {1'b0, b_hs};    
    assign store_done   = wr_accepted && (!is_mmio || (b_out_next == 2'd0));    
    // RAM store is posted (done once accepted), an MMIO store waits for ITS OWN B, i.e. every older posted B has come back too

    always_comb begin                                               // byte lane placement
        case (funct3[1:0])                                          
            2'b00:   size_mask = 4'b0001;                           // sb
            2'b01:   size_mask = 4'b0011;                           // sh
            default: size_mask = 4'b1111;                           // sw
        endcase                                                     
    end                                                             
    assign data_wstrb = size_mask << alu_res[1:0];                  
    assign data_wdata = rs2_in << {alu_res[1:0], 3'b000};           

    assign mem_stage_busy = (load_req && !ar_done) || (store_req && !store_done);

    assign data_fault = (pre_fault && !freeze) || (data_rvalid && data_rready && data_rresp[1]) || (b_hs && data_bresp[1]);   

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ar_sent  <= 1'b0;
            aw_sent  <= 1'b0;                                       
            w_sent   <= 1'b0;                                       
            wr_acc_q <= 1'b0;                                       
            b_out    <= '0;                                         
        end else begin
            b_out <= b_out_next;                                    
            if (mem_advance) begin                                  // next instruction enters MEM, start fresh
                ar_sent  <= 1'b0;                                   
                aw_sent  <= 1'b0;                                   
                w_sent   <= 1'b0;                                   
                wr_acc_q <= 1'b0;                                   
            end else begin                                          // MEM instruction held, remember what was already accepted
                if (ar_hs)      ar_sent  <= 1'b1;                   
                if (aw_hs)      aw_sent  <= 1'b1;                   
                if (w_hs)       w_sent   <= 1'b1;                   
                if (wr_acc_now) wr_acc_q <= 1'b1;                   
            end                                                     
        end
    end

endmodule