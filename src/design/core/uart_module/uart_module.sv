module uart_module #(
    parameter CLK_FREQ = 10_000_000,
    parameter BAUD_RATE = 9600,
    parameter SAMPLING_RATE = 16
) (
    // clock and reset
    input   logic clk,
    input   logic rst_n,
    // tx
    input   logic [7:0] tx_data,
    input   logic tx_start,
    output  logic tx,
    output  logic tx_busy,
    // rx
    input   logic rx,
    input   logic rx_ack,
    output  logic [7:0] rx_data,
    output  logic rx_valid
);

    logic baud_tick;

    baud_rate_gen #(
        .CLK_FREQ         (CLK_FREQ),
        .BAUD_RATE        (BAUD_RATE),
        .SAMPLING_RATE    (SAMPLING_RATE)
    ) u_baud_rate_gen (
        .clk              (clk),
        .rst_n            (rst_n),
        .tick             (baud_tick)
    );

    uart_tx #(
        .SAMPLING_RATE    (SAMPLING_RATE)
    ) u_uart_tx (
        // clock, reset, and tick
        .clk          (clk),
        .rst_n        (rst_n),
        .baud_tick    (baud_tick),
        // validity
        .tx_start     (tx_start),       // start transmission
        // data input
        .tx_data      (tx_data),
        // output bit
        .tx           (tx),             // high = currently transmitting a signal
        .tx_busy      (tx_busy)
    );

    uart_rx #(
        .SAMPLING_RATE    (SAMPLING_RATE)
    ) u_uart_rx (
        // clock, reset, and tick
        .clk              (clk),
        .rst_n            (rst_n),
        .baud_tick        (baud_tick),
        // input receiver
        .rx               (rx),
        .rx_ack           (rx_ack),
        // data and validity output
        .rx_data          (rx_data),
        .rx_valid         (rx_valid)
    );

endmodule
