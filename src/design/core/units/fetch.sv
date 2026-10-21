import rv32i::*;

// NOTE: The RTL in this file was re-written using AI using logic dictated by the programmer, and was then human reviewed and tested.

module fetch #(
    parameter DATA_WIDTH = rv32i::DATA_WIDTH,
    parameter int MAX_OUTSTANDING = 2   // 2 in-flight readsa allowed
) (
    // clock, reset, and stall
    input logic clk,
    input logic rst_n,
    input logic stall,
    // redirect from EX (taken branch / JAL / JALR)
    input logic redirect,
    input Word  redirect_pc,
    // AXI4-Lite read master (instruction port, read-only, no write channels)
    output Word  if_araddr,
    output logic if_arvalid,
    input  logic if_arready,
    input  logic if_rvalid,
    input  Word  if_rdata,
    input  Resp  if_rresp,
    output logic if_rready,
    // outputs
    output Word pc_out,         // this goes to IF/ID register
    output Word instr_out,      // output respective instruction to decoder
    output logic mem_fault,     // mem fault = rresp[1] | misaligned PC, carried through IF/ID
    output logic fetch_valid    // an instruction is delivered to IF/ID this cycle (was a passthrough of instr_valid)
);

    localparam int PTR_W = (MAX_OUTSTANDING > 1) ? $clog2(MAX_OUTSTANDING) : 1;         // FIFO pointer width
    localparam int CNT_W = $clog2(MAX_OUTSTANDING + 1);                                 // FIFO count width

    // request PC
    Word  req_pc;                   // next sequential fetch address
    logic pend_valid;               // a redirect that could not be issued yet
    Word  pend_pc;                  // its target
    logic hold_valid;               // an AR that saw ARREADY low, held stable until accepted (never used while ARREADY is constant 1)
    Word  hold_addr;                // addr for above
    logic hold_stale;               // the held AR became wrong-path because of a redirect

    // in-order FIFO of requests in flight, one entry per accepted AR
    Word  af_pc    [MAX_OUTSTANDING];   // PC of the request
    logic af_mis   [MAX_OUTSTANDING];   // misaligned PC (fault carried with the response)
    logic af_stale [MAX_OUTSTANDING];   // issued before a redirect -> response gets dropped (the "discard" bookkeeping)
    logic [PTR_W-1:0] af_head;
    logic [PTR_W-1:0] af_tail;
    logic [CNT_W-1:0] inflight;         // accepted ARs whose R has not arrived yet

    // capture buffer, holds responses that arrive while IF/ID is frozen (RREADY is always 1)
    Word  cb_instr [MAX_OUTSTANDING];
    Word  cb_pc    [MAX_OUTSTANDING];
    logic cb_fault [MAX_OUTSTANDING];
    logic [PTR_W-1:0] cb_head;
    logic [PTR_W-1:0] cb_tail;          
    logic [CNT_W-1:0] cap_cnt;          

    logic redirect_eff;                 // redirect only takes effect when the pipeline is not frozen
    logic space;                        // room for one more request
    logic req_from_hold;                // which source drives the AR this cycle
    logic req_from_redirect;            
    logic req_from_pend;                
    logic push_stale;                   // stale flag of the entry pushed this cycle
    logic ar_hs;                        // AR handshake
    logic r_hs;                         // R handshake
    logic r_good;                       // R handshake that is not dropped
    logic deliver_from_cb;              // IF/ID takes the capture buffer head
    logic deliver_from_r;               // IF/ID takes the arriving response directly
    logic cb_push;                      // arriving response goes into the capture buffer

    assign redirect_eff = redirect && !stall;                                           
    assign space        = (int'(inflight) + int'(cap_cnt)) < MAX_OUTSTANDING;           // registered state only, no path from RVALID to ARVALID


    function automatic logic [PTR_W-1:0] ptr_inc(input logic [PTR_W-1:0] p);            // wrap-around pointer increment
        return (int'(p) == MAX_OUTSTANDING - 1) ? '0 : p + 1'b1;                        // see above
    endfunction                                                                         // see above

    // request side
    always_comb begin                                                                   
        req_from_hold     = 1'b0;                                                       
        req_from_redirect = 1'b0;                                                       
        req_from_pend     = 1'b0;                                                       
        if (hold_valid) begin                                                           // VALID and payload stay stable until ARREADY
            if_araddr     = hold_addr;                                                  
            if_arvalid    = 1'b1;                                                       
            req_from_hold = 1'b1;                                                       
        end else if (redirect_eff) begin                                                // fetch the target in the same cycle (keeps the 2-cycle branch penalty)
            if_araddr         = redirect_pc;                                            
            if_arvalid        = (int'(inflight) < MAX_OUTSTANDING);                     // capture buffer is flushed this cycle, so only inflight counts
            req_from_redirect = 1'b1;                                                   
        end else if (pend_valid) begin                                                  // deferred redirect target
            if_araddr     = pend_pc;                                                    
            if_arvalid    = space;                                                      
            req_from_pend = 1'b1;                                                       
        end else begin                                                                  // sequential fetch
            if_araddr  = req_pc;                                                        
            if_arvalid = space;                                                         
        end                                                                             
    end                                                                                 

    assign ar_hs      = if_arvalid && if_arready;                                       
    assign push_stale = req_from_hold && (hold_stale || redirect_eff);                  // a held request older than the redirect is wrong-path

    // response side
    assign if_rready = 1'b1;                                                            
    assign r_hs      = if_rvalid && if_rready;                                          
    assign r_good    = r_hs && !redirect_eff && !af_stale[af_head];                     // R arriving in a redirect cycle, or issued before one, is dropped

    always_comb begin                                                                   // delivery to IF/ID
        deliver_from_cb = 1'b0;                                                         
        deliver_from_r  = 1'b0;                                                         
        if (!redirect_eff && !stall) begin                                              
            if (cap_cnt != '0) deliver_from_cb = 1'b1;                                  // older buffered instruction first
            else if (r_good)   deliver_from_r  = 1'b1;                                  // otherwise straight through
        end                                                                             
    end                                                                                 

    assign cb_push = r_good && !deliver_from_r;                                         // stalled, or buffer not empty

    assign fetch_valid = deliver_from_cb || deliver_from_r;                                                             
    assign instr_out   = deliver_from_cb ? cb_instr[cb_head] : (deliver_from_r ? if_rdata : NOP_INSTR);                 // nop bubble when nothing is delivered
    assign pc_out      = deliver_from_cb ? cb_pc[cb_head]    : (deliver_from_r ? af_pc[af_head] : '0);                  
    assign mem_fault   = deliver_from_cb ? cb_fault[cb_head] : (deliver_from_r ? (if_rresp[1] | af_mis[af_head]) : 1'b0);  // resp[1] HIGH = any error

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            req_pc     <= RESET_VECTOR;                                                 
            pend_valid <= 1'b0;                                                         
            pend_pc    <= '0;                                                           
            hold_valid <= 1'b0;                                                         
            hold_addr  <= '0;                                                           
            hold_stale <= 1'b0;                                                         
            af_head    <= '0;                                                           
            af_tail    <= '0;                                                           
            inflight   <= '0;                                                           
            cb_head    <= '0;                                                           
            cb_tail    <= '0;                                                           
            cap_cnt    <= '0;                                                           
            for (int i = 0; i < MAX_OUTSTANDING; i++) af_stale[i] <= 1'b0;              
        end else begin
            // in-flight FIFO
            if (redirect_eff) begin                                                     // everything already in flight is wrong-path now
                for (int i = 0; i < MAX_OUTSTANDING; i++) af_stale[i] <= 1'b1;          
            end                                                                         
            if (ar_hs) begin                                                            // push (after the line above so the new entry keeps its own flag)
                af_pc[af_tail]    <= if_araddr;                                         
                af_mis[af_tail]   <= (if_araddr[1:0] != 2'b00);                         // misaligned fetch is carried as a fault bit
                af_stale[af_tail] <= push_stale;                                        
                af_tail           <= ptr_inc(af_tail);                                  
            end                                                                         
            if (r_hs) af_head <= ptr_inc(af_head);                                      // pop
            inflight <= inflight + CNT_W'(ar_hs) - CNT_W'(r_hs);                        

            // AR hold (VALID stable until READY)
            if (if_arvalid && !if_arready) begin                                        
                if (!hold_valid) begin                                                  
                    hold_valid <= 1'b1;                                                 
                    hold_addr  <= if_araddr;                                            
                    hold_stale <= 1'b0;                                                 
                end else if (redirect_eff) begin                                        
                    hold_stale <= 1'b1;                                                 
                end                                                                     
            end else if (ar_hs && req_from_hold) begin                                  
                hold_valid <= 1'b0;                                                     
            end                                                                         

            if (redirect_eff) begin                                                     // redirect
                cb_head <= '0;                                                          // flush the capture buffer
                cb_tail <= '0;                                                          
                cap_cnt <= '0;                                                          
                if (ar_hs && req_from_redirect) begin                                   // target issued this cycle
                    req_pc     <= redirect_pc + 32'd4;                                  
                    pend_valid <= 1'b0;                                                 
                end else if (if_arvalid && req_from_redirect) begin                     // target is now held, req_pc advances when it is accepted
                    pend_valid <= 1'b0;                                                 
                end else begin                                                          // could not be issued (hold busy or no space), defer it
                    pend_valid <= 1'b1;                                                 
                    pend_pc    <= redirect_pc;                                          
                end                                                                     
            end else begin                                                              
                if (ar_hs) begin                                                        // advance the request PC
                    if (req_from_hold) begin                                            
                        if (!hold_stale) req_pc <= hold_addr + 32'd4;                   // a stale hold leaves req_pc alone (pend holds the target)
                    end else if (req_from_pend) begin                                   
                        req_pc     <= pend_pc + 32'd4;                                  
                        pend_valid <= 1'b0;                                             
                    end else begin                                                      
                        req_pc <= req_pc + 32'd4;                                       
                    end                                                                 
                end else if (if_arvalid && req_from_pend && !hold_valid) begin          // the pending target just moved into the hold
                    pend_valid <= 1'b0;                                                 
                end                                                                     

                // capture buffer
                if (deliver_from_cb) cb_head <= ptr_inc(cb_head);                       
                if (cb_push) begin                                                      
                    cb_instr[cb_tail] <= if_rdata;                                      
                    cb_pc[cb_tail]    <= af_pc[af_head];                                
                    cb_fault[cb_tail] <= if_rresp[1] | af_mis[af_head];                 
                    cb_tail           <= ptr_inc(cb_tail);                              
                end                                                                     
                cap_cnt <= cap_cnt + CNT_W'(cb_push) - CNT_W'(deliver_from_cb);         
            end                                                                         
        end
    end
    
endmodule