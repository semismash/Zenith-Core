## NEW: new file. Zenith Core on the Digilent Arty A7-100T (xc7a100tcsg324-1)
## NEW: pins taken from the board files (part0_pins.xml / board.xml), all banks are 3.3 V (LVCMOS33)

## ---------------------------------------------------------------------------------------------
## Clock: 100 MHz oscillator. The MMCM in top.sv makes the 10 MHz core clock, Vivado derives
## that generated clock automatically from this constraint
## ---------------------------------------------------------------------------------------------
set_property -dict { PACKAGE_PIN E3  IOSTANDARD LVCMOS33 } [get_ports { clk }]
create_clock -name sys_clk -period 10.000 -waveform {0.000 5.000} [get_ports { clk }]

## ---------------------------------------------------------------------------------------------
## Reset button (active low, rst_polarity = 0 in board.xml). Synchronized inside top.sv
## ---------------------------------------------------------------------------------------------
set_property -dict { PACKAGE_PIN C2  IOSTANDARD LVCMOS33 } [get_ports { rst_n }]
set_false_path -from [get_ports { rst_n }]

## ---------------------------------------------------------------------------------------------
## USB-UART bridge (FTDI). usb_uart_rxd is the FPGA input, usb_uart_txd the FPGA output
## i_rx goes through the 2-flop synchronizer in uart_rx.sv, so it is not timed
## ---------------------------------------------------------------------------------------------
set_property -dict { PACKAGE_PIN A9  IOSTANDARD LVCMOS33 } [get_ports { i_rx }]
set_property -dict { PACKAGE_PIN D10 IOSTANDARD LVCMOS33 } [get_ports { o_tx }]
set_false_path -from [get_ports { i_rx }]
set_false_path -to   [get_ports { o_tx }]

## ---------------------------------------------------------------------------------------------
## Green LEDs LD4 - LD7 (led_4bits)
##   led[0] = stop                (ECALL / EBREAK reached WB)
##   led[1] = instruction fault   (fetch error or misaligned PC)
##   led[2] = data fault          (precheck, read or write error)
##   led[3] = illegal instruction
## All four are sticky until reset. HALT (any fault) is not on a pin for now
## ---------------------------------------------------------------------------------------------
set_property -dict { PACKAGE_PIN H5  IOSTANDARD LVCMOS33 } [get_ports { led[0] }]
set_property -dict { PACKAGE_PIN J5  IOSTANDARD LVCMOS33 } [get_ports { led[1] }]
set_property -dict { PACKAGE_PIN T9  IOSTANDARD LVCMOS33 } [get_ports { led[2] }]
set_property -dict { PACKAGE_PIN T10 IOSTANDARD LVCMOS33 } [get_ports { led[3] }]
set_false_path -to [get_ports { led[*] }]

## ---------------------------------------------------------------------------------------------
## Configuration bank voltage (standard for the Arty A7)
## ---------------------------------------------------------------------------------------------
set_property CFGBVS VCCO [current_design]
set_property CONFIG_VOLTAGE 3.3 [current_design]
