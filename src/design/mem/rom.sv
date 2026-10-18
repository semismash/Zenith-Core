import rv32i::*;

module rom #(   // currently houses only the bootloader
    parameter ROM_SIZE_BYTES = 8192   // 8 KiB, size of ROM
) (
    input  logic clk,
    input  logic rst_n,
    input  Word  instr_addr,        // 0-based, relative to ROM's own start
    output Word  instr_out,         // mem not busy (not fetching something rn)
    output logic instr_valid,       // signal to send back for instruction fetch
    output logic instr_not_found,   // instructions not found (faults to be dealt with differently soon, after planned AXI4Lite protocol is implemented)

    input  Word     data_addr,
    input  ReqBytes req_bytes,
    input  logic    write_enable,   // store to ROM is rejected with data_not_found
    input  logic    data_req_start, // only pulsed by mem.sv when the address is inside the ROM
    output Word     data_out,
    output logic    data_valid,     // one cycle after data_req_start
    output logic    data_not_found 
);

    localparam INST_SIZE_BYTES = DATA_WIDTH >> 3;

    Byte container [ROM_SIZE_BYTES - 1:0];
    initial begin
        $readmemh("bios.hex", container);    // PLACEHOLDER PATH to BIOS binary
    end

    logic fault_reg;

    always_ff @(posedge clk) begin
        if (instr_addr > (ROM_SIZE_BYTES - INST_SIZE_BYTES)) begin
            fault_reg <= 1'b1;
            instr_out <= '0;
        end else begin
            fault_reg <= 1'b0;
            instr_out <= {
                container[instr_addr + 3],
                container[instr_addr + 2],
                container[instr_addr + 1],
                container[instr_addr]
            };
        end
    end
    assign instr_not_found = fault_reg;

    //  tie to high as answers in one cycle (PC address fetches are never misses, always happens in any cycle)
    logic instr_valid_q;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) instr_valid_q <= 1'b0;
        else        instr_valid_q <= 1'b1;
    end
    assign instr_valid = instr_valid_q;

    logic data_fault_reg;                                                           
    logic is_data_addr_invalid;                                                     
    assign is_data_addr_invalid = ((data_addr + req_bytes) > ROM_SIZE_BYTES);        // access must end inside the ROM

    always_ff @(posedge clk) begin                                                  
        if (data_req_start) begin                                                   
            data_fault_reg <= 1'b0;                                                 
            if (req_bytes == ZERO) begin                                            
                data_out <= '0;                                                     
            end else if (write_enable || is_data_addr_invalid) begin                 // ROM is write protected; reads past its end fault
                data_fault_reg <= 1'b1;                                             
                data_out       <= '0;                                               
            end else begin                                                          
                case (req_bytes)                                                     // zero-extended, little endian (LSU does the sign extension)
                    ONE:  data_out <= {{(DATA_WIDTH - 8){1'b0}}, container[data_addr]};                                                   
                    TWO:  data_out <= {{(DATA_WIDTH - 16){1'b0}}, container[data_addr + 1], container[data_addr]};                        
                    FOUR: data_out <= {container[data_addr + 3], container[data_addr + 2], container[data_addr + 1], container[data_addr]}; 
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