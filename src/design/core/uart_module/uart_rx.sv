import uart::*;

module uart_rx #(
    parameter int SAMPLING_RATE = 16
) (
    // clock, reset, and tick
    input logic         clk,
    input logic         rst_n,
    input logic         baud_tick,
    // input receiver
    input logic         rx,
    input logic         rx_ack,     // pulses for 1 cycle, so rx_valid knows byte was taken
    // data and validity output
    output logic [7:0]  rx_data,
    output logic        rx_valid
);

    logic rx_meta;
    logic rx_sync;    // synchronize rx to avoid metastability
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rx_meta <= 1'b1;
            rx_sync <= 1'b1;
        end else begin
            rx_meta <= rx;
            rx_sync <= rx_meta;
        end
    end

    State cur_state;

    localparam int TICK_W    = $clog2(SAMPLING_RATE);
    localparam int MID_TICK  = (SAMPLING_RATE / 2) - 1;

    logic [TICK_W-1:0] tick_counter;

    //data bus
    logic [7:0] data_reg;
    assign rx_data = data_reg;
    logic [2:0] data_cntr;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cur_state    <= IDLE;
            tick_counter <= '0;
            data_reg     <= '0;
            data_cntr    <= 3'd0;
            rx_valid     <= 1'b0;
        end else begin
            // rx_valid only now clears on explicit ack signal (allowing bytes to be successfully claimed on non-sycnhronized reads)
            if (rx_ack)
                rx_valid <= 1'b0;

            unique case (cur_state)
                default: begin //covers IDLE
                    if (rx_sync == 1'b0) begin
                        cur_state    <= START;
                        tick_counter <= '0;
                    end
                end
                START: begin
                    if (baud_tick) begin
                        if (tick_counter == MID_TICK[TICK_W-1:0]) begin
                            if (rx_sync == 1'b0) begin
                                cur_state <= DATA;
                                data_cntr <= '0;
                                rx_valid  <= 1'b0;
                            end else begin
                                cur_state <= IDLE;
                            end
                        end
                        tick_counter <= (tick_counter == SAMPLING_RATE-1) ? '0 : tick_counter + 1'b1; // explicitly wrap sampling rate
                    end
                end
                DATA: begin
                    if (baud_tick) begin
                        if (tick_counter == MID_TICK[TICK_W-1:0]) begin
                            data_reg  <= {rx_sync, data_reg [7:1]};
                            data_cntr <= data_cntr + 1;
                            if (data_cntr == 3'd7) cur_state <= STOP;
                        end
                        tick_counter <= (tick_counter == SAMPLING_RATE-1) ? '0 : tick_counter + 1'b1;
                    end
                end
                STOP: begin
                    if (baud_tick) begin
                        if (tick_counter == MID_TICK[TICK_W-1:0]) begin
                            if (rx_sync == 1'b1) rx_valid <= 1'b1;
                            cur_state <= IDLE;
                        end
                        tick_counter <= (tick_counter == SAMPLING_RATE-1) ? '0 : tick_counter + 1'b1;
                    end
                end
            endcase
        end
    end

endmodule
