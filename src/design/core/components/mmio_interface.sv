import rv32i::*;

// NOTE: The RTL in this file was optimized with the help of AI using logic dictated by the programmer, and was then human reviewed and tested.

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

// this module directly links the LSU to MMIO devices (for example, the UART controller), now an AXI4-Lite slave behind data_decoder.sv, fixed lowest-latency accesses
// registers keep their byte addresses above, but every read returns the full aligned word with each register in its own byte lane
// (e.g. META_CONTROL_RD at 0x1001 is lane 1 of word 0x1000, each counter is the whole word at 0x1004 / 0x1008 / 0x100C / 0x1010)
module mmio_interface (
    input logic clk,
    input logic rst_n,

    // AXI4-Lite slave, read channels
    input  Word  data_araddr,       
    input  logic data_arvalid,      
    output logic data_arready,      // constant 1
    output Word  data_rdata,        // registered at the AR handshake
    output logic data_rvalid,       // one cycle after the AR handshake
    input  logic data_rready,       // unused, masters keep RREADY at 1
    output Resp  data_rresp,        // SLVERR for an unmapped MMIO word
    // AXI4-Lite slave, write channels
    input  Word  data_awaddr,       
    input  logic data_awvalid,      
    output logic data_awready,      // constant 1
    input  Word  data_wdata,        
    input  logic [3:0] data_wstrb,  
    input  logic data_wvalid,       
    output logic data_wready,       // constant 1
    output logic data_bvalid,       // one cycle after the AW + W handshake
    input  logic data_bready,       // unused, masters keep BREADY at 1
    output Resp  data_bresp,        // SLVERR for a read-only or unmapped word

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

    Word rd_word;                   // word offset of the read inside the MMIO region (bit 31 and addr[1:0] dropped)
    Word wr_word;                   // ditto for the write
    assign rd_word = {1'b0, data_araddr[30:2], 2'b00};
    assign wr_word = {1'b0, data_awaddr[30:2], 2'b00};

    // I/O interfacing port addresses
    Byte p_uart_status;         // 0x80000000   [0x00000000] (I)
    Byte p_uart_tx_data;        // 0x80000008   [0x00000008] (O)
    Byte p_meta_control;        // 0x80001000   [0x00001000] (O)

    // INPUTS
    assign p_uart_status  = {6'b0, uart_tx_busy | uart_tx_start, uart_rx_valid & ~uart_rx_ack};    // busy shows from the cycle after the TX write, rx_valid hides while the pop is in flight

    // OUTPUTS
    assign uart_tx_data   = p_uart_tx_data;
    assign meta_clear     = p_meta_control[0];
    assign meta_enable    = p_meta_control[1];

    assign data_arready = 1'b1;     
    assign data_awready = 1'b1;     
    assign data_wready  = 1'b1;     

    // ----- ADD INPUT (READ PORTS) HERE -----

    Word rd_val;                    
    Resp rd_resp;                   
    always_comb begin                                                               
        rd_val  = '0;                                                               
        rd_resp = RESP_OKAY;                                                        
        case (rd_word)                                                              
            UART_STATUS:    rd_val = {24'b0, p_uart_status};                        
            UART_RX_DATA:   rd_val = {24'b0, uart_rx_data};                         
            UART_TX_DATA:   rd_val = '0;                                            // write-only, reads as 0
            META_CONTROL:   rd_val = {16'b0, p_meta_control, 8'b0};                 // lane 1 = META_CONTROL_RD mirror, lane 0 (write-only) reads as 0
            META_INSTR_C_0: rd_val = meta_instr_count;                              // whole 32-bit counter
            META_STALL_C_0: rd_val = meta_stall_count;                              
            META_L_USE_C_0: rd_val = meta_l_use_count;                              
            META_FLUSH_C_0: rd_val = meta_br_flush_count;                           
            default:        rd_resp = RESP_SLVERR;                                  // unmapped MMIO word
        endcase                                                                     
    end                                                                             

    // ----- ADD OUTPUT (WRITE PORTS) HERE -----

    always_ff @(posedge clk or negedge rst_n) begin  // reset values on rst_n signal
        if (!rst_n) begin
            data_rvalid     <= 1'b0;    // replaces mmio_data_ready
            data_rdata      <= '0;      // replaces mmio_data_out
            data_rresp      <= RESP_OKAY;   
            data_bvalid     <= 1'b0;    
            data_bresp      <= RESP_OKAY;   

            uart_tx_start   <= 1'b0;
            p_uart_tx_data  <= '0;      // was never reset
            p_meta_control  <= '0;
            uart_rx_ack     <= 1'b0;
        end else begin

            // initialization
            uart_tx_start   <= 1'b0;
            uart_rx_ack     <= 1'b0;                // one-cycle pulse
            
            p_meta_control[0] <= 1'b0;            // only the clear bit self-clears (one-cycle pulse), meta_enable (bit 1) is held

            // read side (RD_IDLE / RD_RESP), ARREADY is constant 1 so ARVALID is the handshake
            data_rvalid <= data_arvalid;                                            
            if (data_arvalid) begin                                                 // data latched at the handshake, before the pop below
                data_rdata <= rd_val;                                               
                data_rresp <= rd_resp;                                              
                if (rd_word == UART_RX_DATA) uart_rx_ack <= 1'b1;                   // pop exactly once per AR (replaces rx_read_hit)
            end                                                                     

            // write side (WR_IDLE / WR_RESP), AW and W arrive together
            data_bvalid <= data_awvalid && data_wvalid;                             
            if (data_awvalid && data_wvalid) begin                                  // output function
                case (wr_word)                                                      
                    UART_TX_DATA: begin                                             
                        data_bresp <= RESP_OKAY;                                    
                        if (data_wstrb[0] && !(uart_tx_busy || uart_tx_start)) begin    // lane 0 only, a write while busy is ignored (still OKAY)
                            p_uart_tx_data <= data_wdata[7:0];                      
                            uart_tx_start  <= 1'b1;                                 
                        end                                                         
                    end                                                             
                    META_CONTROL: begin                                             
                        data_bresp <= RESP_OKAY;                                    
                        if (data_wstrb[0]) p_meta_control <= data_wdata[7:0];       // lane 0 only (lane 1 is the read-only mirror)
                    end                                                             
                    default: data_bresp <= RESP_SLVERR;                             // read-only (status, RX data, counters) or unmapped, nothing is written
                endcase                                                             
            end                                                                     
        end
    end

endmodule