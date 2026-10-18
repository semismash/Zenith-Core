import rv32i::*;

module mem #(
    parameter ROM_SIZE_BYTES = 8192,
    parameter RAM_SIZE_BYTES = 131072
) (
    input logic clk,
    input logic rst_n,

    // instruction fetch: absolute address, full memory map
    input  Word  instr_addr,
    output Word  instr_out,
    output logic instr_valid,
    output logic instr_not_found,

    // data access: absolute address, full memory map
    // ROM is protected: reads are allowed, writes are disallowed
    // MMIO starts from address 0x80000000, handled by LSU itself
    input  Word data_addr,
    input  ReqBytes req_bytes,
    input  logic write_enable,
    input  Word data_in,
    input  logic data_req_start,
    output Word data_out,
    output logic data_valid,
    output logic data_not_found
);

    localparam Word RAM_BASE = ROM_SIZE_BYTES;

    // instruction fetch
    logic sel_rom;
    assign sel_rom = (instr_addr < RAM_BASE);

    logic sel_rom_q;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) sel_rom_q <= 1'b1;   // reset vector fetches from ROM first
        else        sel_rom_q <= sel_rom;
    end

    Word  rom_instr_out, ram_instr_out;
    logic rom_instr_valid, ram_instr_valid;
    logic rom_instr_fault, ram_instr_fault;

    // data access routing: ROM below RAM_BASE (read only), RAM from RAM_BASE up, neither for MMIO (handled by the LSU)
    Word  rom_data_out, ram_data_out;
    logic rom_data_valid, ram_data_valid;
    logic rom_data_fault, ram_data_fault;
    logic data_sel_rom, data_sel_ram;
    assign data_sel_rom = !data_addr[DATA_WIDTH-1] && (data_addr <  RAM_BASE);  // bit 31 = MMIO, same test as the LSU
    assign data_sel_ram = !data_addr[DATA_WIDTH-1] && (data_addr >= RAM_BASE);

    logic data_sel_rom_q, data_sel_ram_q;           // which device answers the access in flight
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            data_sel_rom_q <= 1'b0;
            data_sel_ram_q <= 1'b0;
        end else if (data_req_start) begin          // captured with the request, like sel_rom_q for fetches
            data_sel_rom_q <= data_sel_rom;
            data_sel_ram_q <= data_sel_ram;
        end
    end

    rom #(
        .ROM_SIZE_BYTES(ROM_SIZE_BYTES)
    ) u_boot_rom (
        .clk             (clk),
        .rst_n           (rst_n), 
        .instr_addr      (instr_addr),           // rom's own bounds check rejects ram-range addresses
        .instr_out       (rom_instr_out),
        .instr_valid     (rom_instr_valid),
        .instr_not_found (rom_instr_fault),

        .data_addr       (data_addr),           // ROM starts at 0, so no offset
        .req_bytes       (req_bytes),
        .write_enable    (write_enable),        // ROM rejects stores (data_not_found)
        .data_req_start  (data_req_start && data_sel_rom),
        .data_out        (rom_data_out),
        .data_valid      (rom_data_valid),
        .data_not_found  (rom_data_fault)
    );

    ram #(
        .RAM_SIZE_BYTES(RAM_SIZE_BYTES)
    ) u_ram (
        .clk             (clk),
        .rst_n           (rst_n),
        .instr_addr      (instr_addr - RAM_BASE),
        .instr_out       (ram_instr_out),
        .instr_valid     (ram_instr_valid),
        .instr_not_found (ram_instr_fault),

        .data_addr       (data_addr - RAM_BASE),
        .req_bytes       (req_bytes),
        .write_enable    (write_enable),
        .data_in         (data_in),
        .data_req_start  (data_req_start && data_sel_ram),  // only for RAM addresses (MMIO and ROM no longer reach the RAM)
        .data_out        (ram_data_out),
        .data_valid      (ram_data_valid),
        .data_not_found  (ram_data_fault)
    );

    assign instr_out = sel_rom_q ? rom_instr_out : ram_instr_out;
    assign instr_valid = sel_rom_q ? rom_instr_valid : ram_instr_valid;
    assign instr_not_found = sel_rom_q ? rom_instr_fault : ram_instr_fault;

    assign data_out       = data_sel_rom_q ? rom_data_out : ram_data_out;
    assign data_valid     = rom_data_valid | ram_data_valid;                                             // only the addressed device was started
    assign data_not_found = (data_sel_rom_q && rom_data_fault) || (data_sel_ram_q && ram_data_fault);    // MMIO accesses never fault here

endmodule
