import rv32i::*;

typedef enum Word {

    // UART
    UART_STATUS     = 32'h00000000,     // I; includes both rx_valid (LSB) + tx_busy (LSB + 1)
    UART_RX_DATA    = 32'h00000004,     // I
    UART_TX_DATA    = 32'h00000008,     // O

    // META
    META_CONTROL    = 32'h00001000,     // O; includes both meta_clear (LSB) + meta_enable (LSB + 1)
    META_CONTROL_RD = 32'h00001001,     // I; read only mirror of META_CONTROL
    META_INSTR_C_0  = 32'h00001004,     // I
    META_INSTR_C_1  = 32'h00001005,     // I
    META_INSTR_C_2  = 32'h00001006,     // I
    META_INSTR_C_3  = 32'h00001007,     // I
    META_STALL_C_0  = 32'h00001008,     // I
    META_STALL_C_1  = 32'h00001009,     // I
    META_STALL_C_2  = 32'h0000100A,     // I
    META_STALL_C_3  = 32'h0000100B,     // I
    META_L_USE_C_0  = 32'h0000100C,     // I
    META_L_USE_C_1  = 32'h0000100D,     // I
    META_L_USE_C_2  = 32'h0000100E,     // I
    META_L_USE_C_3  = 32'h0000100F,     // I
    META_FLUSH_C_0  = 32'h00001010,     // I
    META_FLUSH_C_1  = 32'h00001011,     // I
    META_FLUSH_C_2  = 32'h00001012,     // I
    META_FLUSH_C_3  = 32'h00001013      // I

} MMIOAddress;

// this module directly links the LSU to MMIO devices (for example, the UART controller)
module mmio_interface (
    input logic clk,
    input logic rst_n,

    input  Word mmio_data_addr,
    input  ReqBytes req_bytes,
    input  logic write_enable,
    input  Word mmio_data_in,
    input  logic mem_req_start,

    // to LSU
    output Word mmio_data_out,
    output logic mmio_data_ready,

    // TO I/O modules:
    // UART RX/TX
    input Byte uart_rx_data,
    input logic uart_rx_valid,
    output Byte uart_tx_data,
    output logic uart_tx_start,
    input logic uart_tx_busy,
    output logic uart_rx_ack,
    // TELEMTRY UNIT
    output logic meta_enable,
    output logic meta_clear,
    input MetaCount meta_instr_count,
    input MetaCount meta_stall_count,
    input MetaCount meta_l_use_count,
    input MetaCount meta_br_flush_count
);

    // no data fault raised, value simply discarded
    // MMIO is defined as everything after 0x80000000 (until 0xFFFFFFFF, 32-bit address space limit)
    // since we adjust mmio address, wrap-around condition due to 32-bit int limit is impossible

    Word mem_addr_0, mem_addr_1, mem_addr_2, mem_addr_3;
    Byte mem_data_write_0, mem_data_write_1, mem_data_write_2, mem_data_write_3; 

    MMIOAddress mmio_corrected_addr;
    assign mmio_corrected_addr = MMIOAddress'({1'b0, mmio_data_addr[30:0]});

    // DEVELOPERS NOTE: In this file, nomeclature wise, corrected addresses will be referred to by [square brackets]

    MMIOAddress mmioplus1, mmioplus2, mmioplus3;
    assign mmioplus1 = MMIOAddress'(mmio_corrected_addr + 1'd1);
    assign mmioplus2 = MMIOAddress'(mmio_corrected_addr + 2'd2);
    assign mmioplus3 = MMIOAddress'(mmio_corrected_addr + 2'd3);

    // if out of bounds, saturate to 0xFFFFFFFF [0x7FFFFFFF]; this address is guaranteed to be unused
    assign mem_addr_0 = mmio_corrected_addr;
    assign mem_addr_1 = (mmioplus1 < MMIO_SIZE_BYTES) ? Word'(mmioplus1) : 32'h7FFFFFFF;
    assign mem_addr_2 = (mmioplus2 < MMIO_SIZE_BYTES) ? Word'(mmioplus2) : 32'h7FFFFFFF;
    assign mem_addr_3 = (mmioplus3 < MMIO_SIZE_BYTES) ? Word'(mmioplus3) : 32'h7FFFFFFF;

    // ----- ADD NEW PORTS FROM HERE ----- 

    // I/O interfacing port addresses
    Byte p_uart_status;         // 0x80000000   [0x00000000] (I)
    Byte p_uart_rx_data;        // 0x80000004   [0x00000004] (I)
    Byte p_uart_tx_data;        // 0x80000008   [0x00000008] (O)
    Byte p_meta_control;        // 0x80001000   [0x00001000] (O)
    // 0x80001004   [0x00001004-1007] (I)
    Byte p_meta_instr_c_0, p_meta_instr_c_1, p_meta_instr_c_2, p_meta_instr_c_3;
    // 0x80001008   [0x00001008-100B] (I) 
    Byte p_meta_stall_c_0, p_meta_stall_c_1, p_meta_stall_c_2, p_meta_stall_c_3;
    // 0x8000100C   [0x0000100C-100F] (I)
    Byte p_meta_l_use_c_0, p_meta_l_use_c_1, p_meta_l_use_c_2, p_meta_l_use_c_3;
    // 0x80001010   [0x00001010-1014] (I)
    Byte p_meta_br_flush_c_0, p_meta_br_flush_c_1, p_meta_br_flush_c_2, p_meta_br_flush_c_3;

    // INPUTS
    assign p_uart_status  = {6'b0, uart_tx_busy, uart_rx_valid};
    assign p_uart_rx_data = uart_rx_data;

    assign p_meta_instr_c_0 = meta_instr_count[0];
    assign p_meta_instr_c_1 = meta_instr_count[1];
    assign p_meta_instr_c_2 = meta_instr_count[2];
    assign p_meta_instr_c_3 = meta_instr_count[3];

    assign p_meta_stall_c_0 = meta_stall_count[0];
    assign p_meta_stall_c_1 = meta_stall_count[1];
    assign p_meta_stall_c_2 = meta_stall_count[2];
    assign p_meta_stall_c_3 = meta_stall_count[3];

    assign p_meta_l_use_c_0 = meta_l_use_count[0];
    assign p_meta_l_use_c_1 = meta_l_use_count[1];
    assign p_meta_l_use_c_2 = meta_l_use_count[2];
    assign p_meta_l_use_c_3 = meta_l_use_count[3];

    assign p_meta_br_flush_c_0 = meta_br_flush_count[0];
    assign p_meta_br_flush_c_1 = meta_br_flush_count[1];
    assign p_meta_br_flush_c_2 = meta_br_flush_count[2];
    assign p_meta_br_flush_c_3 = meta_br_flush_count[3];
    
    // OUTPUTS
    assign uart_tx_data   = p_uart_tx_data;
    assign meta_clear     = p_meta_control[0];
    assign meta_enable    = p_meta_control[1];

    // ----- ADD INPUT (READ PORTS) HERE -----

    // unified function: use for all four read addresses to avoid redundancy
    function automatic Byte mmio_read_byte(input MMIOAddress addr);
        case (addr)
            UART_STATUS:        mmio_read_byte = p_uart_status;
            UART_RX_DATA:       mmio_read_byte = p_uart_rx_data;

            META_CONTROL_RD:    mmio_read_byte = p_meta_control;

            META_INSTR_C_0:     mmio_read_byte = p_meta_instr_c_0;
            META_INSTR_C_1:     mmio_read_byte = p_meta_instr_c_1;
            META_INSTR_C_2:     mmio_read_byte = p_meta_instr_c_2;
            META_INSTR_C_3:     mmio_read_byte = p_meta_instr_c_3;

            META_STALL_C_0:     mmio_read_byte = p_meta_stall_c_0;
            META_STALL_C_1:     mmio_read_byte = p_meta_stall_c_1;
            META_STALL_C_2:     mmio_read_byte = p_meta_stall_c_2;
            META_STALL_C_3:     mmio_read_byte = p_meta_stall_c_3;

            META_L_USE_C_0:     mmio_read_byte = p_meta_l_use_c_0;
            META_L_USE_C_1:     mmio_read_byte = p_meta_l_use_c_1;
            META_L_USE_C_2:     mmio_read_byte = p_meta_l_use_c_2;
            META_L_USE_C_3:     mmio_read_byte = p_meta_l_use_c_3;

            META_FLUSH_C_0:     mmio_read_byte = p_meta_br_flush_c_0;
            META_FLUSH_C_1:     mmio_read_byte = p_meta_br_flush_c_1;
            META_FLUSH_C_2:     mmio_read_byte = p_meta_br_flush_c_2;
            META_FLUSH_C_3:     mmio_read_byte = p_meta_br_flush_c_3;

            default:      mmio_read_byte = 8'h00;  // ports not covered are pulled down to 0
        endcase
    endfunction

    // -----------

    always_comb begin
        mem_data_write_0 = '0;
        mem_data_write_1 = '0;
        mem_data_write_2 = '0;
        mem_data_write_3 = '0;
        if (write_enable) begin
            case (req_bytes)
                ONE: begin
                    mem_data_write_0 = mmio_data_in[7:0];
                end
                TWO: begin
                    mem_data_write_0 = mmio_data_in[7:0];
                    mem_data_write_1 = mmio_data_in[15:8];
                end
                FOUR: begin
                    mem_data_write_0 = mmio_data_in[7:0];
                    mem_data_write_1 = mmio_data_in[15:8];
                    mem_data_write_2 = mmio_data_in[23:16];
                    mem_data_write_3 = mmio_data_in[31:24];
                end
                default: begin
                end
            endcase
        end
    end

    // finds whether this access is a non-write (read) that touches UART_RX_DATA in any lane
    // drives uart_rx_ack below so the UART receiver knows the byte was actually consumed
    logic rx_read_hit;
    always_comb begin
        rx_read_hit = !write_enable && mem_req_start &&
                      (mem_addr_0 == UART_RX_DATA ||                                                        // lanes beyond the access width are not read, so they must not ack
                       ((req_bytes == TWO || req_bytes == FOUR) && mem_addr_1 == UART_RX_DATA) ||
                       (req_bytes == FOUR && (mem_addr_2 == UART_RX_DATA || mem_addr_3 == UART_RX_DATA)));
    end

    // ----- ADD OUTPUT (WRITE PORTS) HERE -----

    // finds the lane which targetted TX_DATA
    logic tx_write_hit;
    Byte tx_write_byte;
    Byte meta_control_byte;
    logic meta_write_hit;   // set only when this write targets META_CONTROL
    always_comb begin
        tx_write_hit  = 1'b0;
        tx_write_byte = 8'h00;
        meta_control_byte = 8'h00;
        meta_write_hit    = 1'b0;

        if (mem_addr_0 == UART_TX_DATA) begin
            tx_write_hit  = 1'b1;
            tx_write_byte = mem_data_write_0;
        end else if (mem_addr_1 == UART_TX_DATA) begin
            tx_write_hit  = 1'b1;
            tx_write_byte = mem_data_write_1;
        end else if (mem_addr_2 == UART_TX_DATA) begin
            tx_write_hit  = 1'b1;
            tx_write_byte = mem_data_write_2;
        end else if (mem_addr_3 == UART_TX_DATA) begin
            tx_write_hit  = 1'b1;
            tx_write_byte = mem_data_write_3;
        end

        if (mem_addr_0 == META_CONTROL) begin
            meta_control_byte = mem_data_write_0;
            meta_write_hit    = 1'b1;
        end else if (mem_addr_1 == META_CONTROL && (req_bytes == TWO || req_bytes == FOUR)) begin  // only lanes inside the access width count
            meta_control_byte = mem_data_write_1;
            meta_write_hit    = 1'b1;
        end else if (mem_addr_2 == META_CONTROL && req_bytes == FOUR) begin
            meta_control_byte = mem_data_write_2;
            meta_write_hit    = 1'b1;
        end else if (mem_addr_3 == META_CONTROL && req_bytes == FOUR) begin
            meta_control_byte = mem_data_write_3;
            meta_write_hit    = 1'b1;
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin  // reset values on rst_n signal
        if (!rst_n) begin
            mmio_data_ready <= 1'b0;
            mmio_data_out   <= '0;

            uart_tx_start   <= 1'b0;
            p_meta_control  <= '0;
            uart_rx_ack     <= 1'b0;
        end else begin

            // initialization
            uart_tx_start   <= 1'b0;
            
            p_meta_control[0] <= 1'b0;            // only the clear bit self-clears (one-cycle pulse), meta_enable (bit 1) is held
            mmio_data_ready <= mem_req_start;     // set high when mem access data ready, LSU installs
            uart_rx_ack     <= rx_read_hit;       // pulse ack one cycle after seeing what triggered it

            if (write_enable) begin     // output function
                if (mem_req_start) begin
                    if (tx_write_hit) begin    // checks all 4 possible lanes (pulse once per instruction)
                        p_uart_tx_data <= tx_write_byte;
                        uart_tx_start  <= 1'b1;
                    end
                    if (meta_write_hit)                         // was unconditional: any MMIO write (e.g. a UART TX byte) zeroed META_CONTROL
                        p_meta_control <= meta_control_byte;    // (moved under the if)
                end
                mmio_data_out <= '0;
                // writes to invalid ports are discarded
            end else if (mem_req_start) begin              // input function
                mmio_data_out <= {
                    mmio_read_byte(mem_addr_3), 
                    mmio_read_byte(mem_addr_2), 
                    mmio_read_byte(mem_addr_1), 
                    mmio_read_byte(mem_addr_0)
                };
            end
        end
    end

endmodule