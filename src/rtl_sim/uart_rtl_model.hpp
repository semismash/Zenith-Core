// C++ port of baud_tick.sv + uart_tx.sv + uart_rx.sv (same state machines, same registered-output timing) plus a tiny
// echo "firmware" (every received byte comes back as byte + 1). Used only by the bridge self-tests, never by the real sim.
#pragma once
#include <cstdint>
#include <deque>
#include <vector>

// ---------------------------------------------------------------------------------------------------
//  port of the UART RTL
// ---------------------------------------------------------------------------------------------------
struct UartRtl {
    int clk_hz, baud, samp;
    int max;                       // baud_rate_gen MAX
    // baud_rate_gen
    int bg_counter = 0;
    bool tick = false;
    // uart_rx
    int rx_meta = 1, rx_sync = 1;
    enum St { IDLE, START, DATA, STOP };
    St rx_state = IDLE;
    int rx_tick_counter = 0;
    uint8_t rx_data_reg = 0;
    int rx_data_cntr = 0;
    bool rx_valid = false;
    // uart_tx
    St tx_state = IDLE;
    int tx_data_cntr = 0;
    uint8_t tx_data_reg = 0;
    int tx = 1;
    bool tx_start_pending = false;
    int tx_tick_cntr = 0;

    UartRtl(int clk, int bd, int sp) : clk_hz(clk), baud(bd), samp(sp), max(clk / (bd * sp)) {}

    void reset() {
        bg_counter = 0; tick = false;
        rx_meta = rx_sync = 1; rx_state = IDLE; rx_tick_counter = 0; rx_data_reg = 0; rx_data_cntr = 0; rx_valid = false;
        tx_state = IDLE; tx_data_cntr = 0; tx_data_reg = 0; tx = 1; tx_start_pending = false; tx_tick_cntr = 0;
    }
    bool tx_busy() const { return tx_state != IDLE || tx_start_pending; }

    // one rising clock edge: everything is computed from the CURRENT register values (non-blocking semantics)
    void clock(int rx_pin, bool tx_start, uint8_t tx_data, bool rx_ack) {
        const bool baud_tick = tick;
        // ---- baud_rate_gen
        bool tick_n = false;
        int bg_n;
        if (bg_counter >= max - 1) { tick_n = true; bg_n = 0; } else { tick_n = false; bg_n = bg_counter + 1; }

        // ---- uart_rx
        int rx_meta_n = rx_pin, rx_sync_n = rx_meta;
        St st_n = rx_state;
        int tc_n = rx_tick_counter;
        uint8_t dr_n = rx_data_reg;
        int dc_n = rx_data_cntr;
        bool v_n = rx_valid;
        const int mid = samp / 2 - 1;
        if (rx_ack) v_n = false;
        switch (rx_state) {
        case IDLE:
            if (rx_sync == 0) { st_n = START; tc_n = 0; }
            break;
        case START:
            if (baud_tick) {
                if (rx_tick_counter == mid) {
                    if (rx_sync == 0) { st_n = DATA; dc_n = 0; v_n = false; } else st_n = IDLE;
                }
                tc_n = (rx_tick_counter == samp - 1) ? 0 : rx_tick_counter + 1;
            }
            break;
        case DATA:
            if (baud_tick) {
                if (rx_tick_counter == mid) {
                    dr_n = static_cast<uint8_t>((rx_sync << 7) | (rx_data_reg >> 1));
                    dc_n = (rx_data_cntr + 1) & 7;
                    if (rx_data_cntr == 7) st_n = STOP;
                }
                tc_n = (rx_tick_counter == samp - 1) ? 0 : rx_tick_counter + 1;
            }
            break;
        case STOP:
            if (baud_tick) {
                if (rx_tick_counter == mid) {
                    if (rx_sync == 1) v_n = true;
                    st_n = IDLE;
                }
                tc_n = (rx_tick_counter == samp - 1) ? 0 : rx_tick_counter + 1;
            }
            break;
        }

        // ---- uart_tx
        const bool bit_done = baud_tick && (tx_tick_cntr == samp - 1);
        int ttc_n = tx_tick_cntr;
        if (tx_state == IDLE) ttc_n = 0;
        else if (baud_tick) ttc_n = bit_done ? 0 : tx_tick_cntr + 1;
        St tst_n = tx_state;
        int tdc_n = tx_data_cntr;
        uint8_t tdr_n = tx_data_reg;
        int tx_n = tx;
        bool sp_n = tx_start_pending;
        switch (tx_state) {
        case IDLE:
            tx_n = 1;
            if (tx_start && !tx_start_pending) { tdr_n = tx_data; sp_n = true; }
            if (tx_start_pending && baud_tick) { tst_n = START; tx_n = 0; sp_n = false; }
            break;
        case START:
            tx_n = 0;
            if (bit_done) { tst_n = DATA; tdc_n = 0; tx_n = tx_data_reg & 1; }
            break;
        case DATA:
            tx_n = tx_data_reg & 1;
            if (bit_done) {
                if (tx_data_cntr == 7) { tst_n = STOP; tx_n = 1; }
                else { tdr_n = static_cast<uint8_t>(tx_data_reg >> 1); tx_n = (tx_data_reg >> 1) & 1; tdc_n = tx_data_cntr + 1; }
            }
            break;
        case STOP:
            tx_n = 1;
            if (bit_done) tst_n = IDLE;
            break;
        }

        // ---- commit
        tick = tick_n; bg_counter = bg_n;
        rx_meta = rx_meta_n; rx_sync = rx_sync_n; rx_state = st_n; rx_tick_counter = tc_n; rx_data_reg = dr_n;
        rx_data_cntr = dc_n; rx_valid = v_n;
        tx_tick_cntr = ttc_n; tx_state = tst_n; tx_data_cntr = tdc_n; tx_data_reg = tdr_n; tx = tx_n; tx_start_pending = sp_n;
    }
};

// ---------------------------------------------------------------------------------------------------
//  the "firmware": echoes every received byte + 1, one at a time
// ---------------------------------------------------------------------------------------------------
struct EchoFw {
    UartRtl& u;
    std::vector<uint8_t> seen;        // every byte the device received, in order
    std::deque<uint8_t> out;
    explicit EchoFw(UartRtl& u_) : u(u_) {}
    void clock(int rx_pin) {
        bool ack = false;
        if (u.rx_valid) { seen.push_back(u.rx_data_reg); out.push_back(static_cast<uint8_t>(u.rx_data_reg + 1)); ack = true; }
        bool start = false;
        uint8_t d = 0;
        if (!u.tx_busy() && !out.empty()) { start = true; d = out.front(); out.pop_front(); }
        u.clock(rx_pin, start, d, ack);
    }
    void reset() { u.reset(); out.clear(); }
};