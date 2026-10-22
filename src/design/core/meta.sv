// metadata unit (flip-flop) for debugging, and instruction counter too

import rv32i::*;

module meta (
    input logic clk,
    input logic rst_n,
    input logic is_instr,       // pulse from the hazard unit when the instruction in ID advances (replaces the pipelined valid_instr)
    // interfacing with meta unit
    input logic enable, // update only when enable
    input logic clear,  // syncrhonous clear
    // from hazard unit for telemetry data
    input logic is_stall,
    input logic is_l_use,
    input logic is_br_flush,
    // output
    output MetaCount meta_cycle_count,
    output MetaCount meta_instr_count,
    output MetaCount meta_stall_count,
    output MetaCount meta_l_use_count,
    output MetaCount meta_br_flush_count
);

    MetaCount cycle_count;   // upto 2^23 cycles tracking
    MetaCount instr_count;   // upto 2^32 instructions tracking
    MetaCount stall_count;
    MetaCount l_use_count;
    MetaCount br_flush_count;

    logic       post_flush;     // high in the cycle right after a branch flush, when ID can only hold a NOP bubble
    logic [1:0] boot_mask;      // the first 2 cycles after reset only have bubbles in ID (the first fetch response arrives a cycle later)

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin   // async reset split from the synchronous clear
            cycle_count     <= '0;
            instr_count     <= '0;
            stall_count     <= '0;
            l_use_count     <= '0;
            br_flush_count  <= '0;
            post_flush      <= 1'b0;    
            boot_mask       <= 2'd2;
        end else begin
            post_flush <= is_br_flush;                          // runs regardless of enable / clear, only the counters are gated
            if (boot_mask != 2'd0) boot_mask <= boot_mask - 1'b1;   
            if (clear) begin                                    // synchronous clear, now its own branch (counters only)
                cycle_count     <= '0;
                instr_count     <= '0;                          
                stall_count     <= '0;                          
                l_use_count     <= '0;                          
                br_flush_count  <= '0;                          
            end else if (enable) begin
                cycle_count     <= cycle_count + 1'b1;
                if (is_instr && !post_flush && boot_mask == 2'd0)   instr_count     <= instr_count + 1'b1;  // counted at ID when the instruction advances, bubbles masked
                if (is_stall)       stall_count     <= stall_count + 1'b1;
                if (is_l_use)       l_use_count     <= l_use_count + 1'b1;
                if (is_br_flush)    br_flush_count  <= br_flush_count + 2'd2;    // add 2 cycles here since flushes void 2 cycles worth of instructions
            end
        end
    end

    assign meta_cycle_count = cycle_count;
    assign meta_instr_count = instr_count;
    assign meta_stall_count = stall_count;
    assign meta_l_use_count = l_use_count;
    assign meta_br_flush_count = br_flush_count;

endmodule