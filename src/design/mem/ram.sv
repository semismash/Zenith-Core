import rv32i::*;

module ram #(
    parameter RAM_SIZE_BYTES = 131072    // 128 KiB BRAM
) (
    input logic clk,
    input logic rst_n,

    // PORT A: instruction mem
    input  Word instr_addr,
    output Word instr_out,
    output logic instr_valid,           // tied high, port exists for compatability and consistency reasons
    output logic instr_not_found,

    // PORT B: data mem
    input  Word data_addr,
    input  ReqBytes req_bytes,
    input  logic write_enable,
    input  Word data_in,
    output Word data_out,

    input  logic data_req_start,    // pulse one cycle on mem access cycle (to cause stall)
    output logic data_valid,        // pulse to tell LSU that access has finished
    output logic data_not_found
);

    localparam INST_SIZE_BYTES = DATA_WIDTH >> 3;

    Byte container [RAM_SIZE_BYTES - 1: 0];
    initial begin
        $readmemh("bootloader.hex", container);
    end

    // PORT A:
    logic instr_fault_reg;

    always_ff @(posedge clk) begin
        // perform boundary check synchronously
        if (instr_addr > (RAM_SIZE_BYTES - INST_SIZE_BYTES)) begin
            instr_fault_reg <= 1'b1;
            instr_out       <= '0;
        end else begin
            instr_fault_reg <= 1'b0;
            instr_out       <= { 
                container[instr_addr + 3], // do INST_SIZE_BYTES times
                container[instr_addr + 2], 
                container[instr_addr + 1], 
                container[instr_addr] 
            };
        end
    end
    assign instr_not_found = instr_fault_reg;

    // never "busy" as always fetches in any cycle (so technically busy all the time, but hence never busy, syndrome ahh logic)
    logic instr_valid_q;    
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) instr_valid_q <= 1'b0;
        else        instr_valid_q <= 1'b1;
    end
    assign instr_valid = instr_valid_q;

    // PORT B:
    logic data_fault_reg;
    
    // boundary check must happen dynamically or be registered
    logic is_data_addr_invalid;
    assign is_data_addr_invalid = ((data_addr + req_bytes) > RAM_SIZE_BYTES);

    always_ff @(posedge clk) begin

        if (data_req_start) begin   // only if requested data (mem fetch)
            
            data_fault_reg <= 1'b0;
            if (req_bytes == ZERO) begin
                data_out <= '0;
            end else if (is_data_addr_invalid) begin
                data_fault_reg <= 1'b1;
                data_out       <= '0;
            end else begin
                // synchronous write
                if (write_enable) begin
                    case(req_bytes)
                        ONE: begin
                            container[data_addr]     <= data_in[7:0];
                        end
                        TWO: begin
                            container[data_addr]     <= data_in[7:0];
                            container[data_addr + 1] <= data_in[15:8];
                        end
                        FOUR: begin
                            container[data_addr]     <= data_in[7:0];
                            container[data_addr + 1] <= data_in[15:8];
                            container[data_addr + 2] <= data_in[23:16];
                            container[data_addr + 3] <= data_in[31:24];
                        end
                        default: data_fault_reg <= 1'b1;
                    endcase
                end

                // synchronous read
                case (req_bytes)
                    ONE:  data_out <= {{(DATA_WIDTH - 8){1'b0}}, container[data_addr]};
                    TWO:  data_out <= {{(DATA_WIDTH - 16){1'b0}}, container[data_addr + 1], container[data_addr]};
                    FOUR: data_out <= { container[data_addr + 3], container[data_addr + 2], container[data_addr + 1], container[data_addr] };
                    default: data_fault_reg <= 1'b1;
                endcase
            end
            
        end

    end
    assign data_not_found = data_fault_reg;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) data_valid <= 1'b0;
        else        data_valid <= data_req_start;
    end

endmodule
