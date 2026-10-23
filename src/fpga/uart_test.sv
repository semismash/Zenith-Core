// Zenith Core - hardware bring-up test, NO CPU. Only the same clock setup, reset and UART module the core uses.
//
//   make fpga FPGA_TOP=uart_test            (builds build/vivado/uart_test.bit)
//   make fpga-program FPGA_TOP=uart_test
//
// What you should see on the board (uses the same pins as the real design, so the XDC is unchanged):
//   - serial port, 9600 8N1: the text line  ZENITH UART TEST 0123456789  repeated forever (\015 = CR, SystemVerilog has no \r)
//   - LD4 (led[0]): heartbeat, 0.5 s on / 0.5 s off. Count it with a stopwatch: that is the 10 MHz clock
//   - LD5 (led[1]): on = the MMCM has locked
//   - LD6 (led[2]): on = the reset has been released (needs the MMCM lock, then 2 clocks)
//   - LD7 (led[3]): lights when the PC has sent any byte to the board, stays on until reset (tests the receive path)
module uart_test (
    input  logic       clk,         // 100 MHz board oscillator (E3)
    input  logic       rst_n,       // reset button (C2), active low
    output logic [3:0] led,
    input  logic       i_rx,        // usb_uart_rxd (A9)
    output logic       o_tx         // usb_uart_txd (D10)
);

    // ------------------------------------------------------------------------------------------
    // clock: 100 MHz -> 10 MHz, identical to top.sv
    // ------------------------------------------------------------------------------------------
    logic cpu_clk;
    logic mmcm_locked;
    logic clkfb;
    logic clkfb_buf;
    logic clk_10m;

    MMCME2_BASE #(
        .BANDWIDTH          ("OPTIMIZED"),
        .CLKIN1_PERIOD      (10.0),
        .DIVCLK_DIVIDE      (1),
        .CLKFBOUT_MULT_F    (10.0),
        .CLKOUT0_DIVIDE_F   (100.0),
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

    // reset: asynchronous assert, synchronous release, held until the MMCM locks, identical to top.sv
    logic [1:0] rst_sync;
    logic       core_rst_n;
    always_ff @(posedge cpu_clk or negedge rst_n) begin
        if (!rst_n)            rst_sync <= 2'b00;
        else if (!mmcm_locked) rst_sync <= 2'b00;
        else                   rst_sync <= {rst_sync[0], 1'b1};
    end
    assign core_rst_n = rst_sync[1];

    // ------------------------------------------------------------------------------------------
    // the UART module of the core, 9600 baud on the 10 MHz clock
    // ------------------------------------------------------------------------------------------
    logic [7:0] tx_data;
    logic       tx_start;
    logic       tx_busy;
    logic [7:0] rx_data;
    logic       rx_valid;
    logic       rx_ack;

    uart_module #(
        .CLK_FREQ      (10_000_000),
        .BAUD_RATE     (9600),
        .SAMPLING_RATE (16)
    ) u_uart (
        .clk      (cpu_clk),
        .rst_n    (core_rst_n),
        .tx_data  (tx_data),
        .tx_start (tx_start),
        .tx       (o_tx),
        .tx_busy  (tx_busy),
        .rx       (i_rx),
        .rx_ack   (rx_ack),
        .rx_data  (rx_data),
        .rx_valid (rx_valid)
    );

    // ------------------------------------------------------------------------------------------
    // transmit one text line over and over, back to back
    // ------------------------------------------------------------------------------------------
    localparam int MSG_LEN = 29;
    localparam logic [8*MSG_LEN-1:0] MSG = "ZENITH UART TEST 0123456789\015\n";

    logic [4:0] idx;

    always_ff @(posedge cpu_clk) begin
        tx_start <= 1'b0;
        if (!core_rst_n) begin
            idx <= 5'd0;
        end else if (!tx_busy && !tx_start) begin
            tx_data  <= MSG[8*(MSG_LEN-1-idx) +: 8];
            tx_start <= 1'b1;
            idx      <= (idx == 5'(MSG_LEN-1)) ? 5'd0 : idx + 5'd1;
        end
    end

    // ------------------------------------------------------------------------------------------
    // LEDs
    // ------------------------------------------------------------------------------------------
    logic [22:0] hb_cnt;
    logic        hb;
    logic        got_rx;

    always_ff @(posedge cpu_clk) begin
        rx_ack <= rx_valid;                          // consume received bytes so the receiver can take the next one
        if (!core_rst_n) begin
            hb_cnt <= 23'd0;
            hb     <= 1'b0;
            got_rx <= 1'b0;
        end else begin
            if (hb_cnt == 23'd4_999_999) begin       // 5,000,000 clocks at 10 MHz = 0.5 s
                hb_cnt <= 23'd0;
                hb     <= ~hb;
            end else begin
                hb_cnt <= hb_cnt + 23'd1;
            end
            if (rx_valid) got_rx <= 1'b1;
        end
    end

    assign led[0] = hb;
    assign led[1] = mmcm_locked;
    assign led[2] = core_rst_n;
    assign led[3] = got_rx;

endmodule