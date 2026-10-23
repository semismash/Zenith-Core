# Zenith Core - program the Arty A7-100T over JTAG with the bitstream from build.tcl
#
#   cd build/vivado && vivado -mode batch -source ../../src/fpga/program.tcl [-tclargs <bitstream name>]
#                                                                               (`make fpga-program` does exactly this)
# The optional argument names a bitstream in build/vivado/ (default zenith_core, or e.g. uart_test).
#
# The configuration is volatile: it is gone after a power cycle (programming the on-board flash is a separate step).

proc die {msg} {
    puts "ERROR: $msg"
    exit 1
}

set script_dir [file dirname [file normalize [info script]]]
set root       [file normalize [file join $script_dir .. ..]]
set bit_name   zenith_core
if {$argc > 0} { set bit_name [lindex $argv 0] }
set bit_file   [file join $root build vivado $bit_name.bit]

if {![file exists $bit_file]} { die "$bit_file not found, run 'make fpga' first" }

open_hw_manager
connect_hw_server
open_hw_target

set devices [get_hw_devices]
if {[llength $devices] == 0} { die "no JTAG device found: board connected, powered, USB cable in the PROG/UART port?" }
set dev [lindex $devices 0]
puts "INFO: programming $dev with $bit_file"

current_hw_device $dev
set_property PROGRAM.FILE $bit_file $dev
program_hw_devices $dev
puts "INFO: programmed, press the board's RESET button once if the BIOS banner does not show up"

close_hw_target
close_hw_manager
