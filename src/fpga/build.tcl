# Zenith Core - Vivado batch build (non-project mode) for the Arty A7-100T
#
#   cd build/vivado && vivado -mode batch -source ../../src/fpga/build.tcl        (`make fpga` does exactly this)
#
# Optional arguments:  <top module> <bitstream name> <ROM image, path relative to the repo root>
# 1) the top module. Default is the real design ('top', bitstream zenith_core.bit). Any other name has to
#    be a module in src/fpga/<name>.sv, e.g. 'uart_test' (CPU-free UART and clock bring-up test).
# 2) the bitstream name without extension (default zenith_core, or the top module's name for a test top).
# 3) the ROM image (default build/bios/bios.hex). A different one, e.g. a small test program built with
#    'make rom-asm', runs the real CPU on the board without the BIOS.
#
# Reads the RTL from src/design, the constraints from src/fpga and the BIOS image from build/bios/bios.hex and writes
# the bitstream, checkpoints and reports to build/vivado/. No Vivado project is kept anywhere, so there is no state
# to get out of sync. Every check below stops the build with a message instead of producing a bitstream that boots
# nothing.

proc die {msg} {
    puts "ERROR: $msg"
    exit 1
}

set script_dir [file dirname [file normalize [info script]]]
set root       [file normalize [file join $script_dir .. ..]]
set design_dir [file join $root src design]
set xdc_file   [file join $script_dir zenith_core_arty_a7.xdc]
set bios_hex   [file join $root build bios bios.hex]
set out_dir    [file join $root build vivado]
set part       xc7a100tcsg324-1
set top        top
set bit_name   zenith_core
if {$argc > 0 && [lindex $argv 0] ne "top"} {
    set top      [lindex $argv 0]
    set bit_name $top
}
if {$argc > 1 && [lindex $argv 1] ne ""} { set bit_name [lindex $argv 1] }
if {$argc > 2 && [lindex $argv 2] ne ""} { set bios_hex [file normalize [file join $root [lindex $argv 2]]] }
set rom_words  2048                      ;# 8 KiB ROM

file mkdir $out_dir
cd $out_dir

# ---------------------------------------------------------------------------------------- inputs
foreach f [list $xdc_file $bios_hex] {
    if {![file exists $f]} {
        die "$f not found (the hex file comes from 'make bios', 'make fpga' runs that first)"
    }
}

# bios.hex must be what $readmemh expects: one 32-bit hex word per line, not more than the ROM holds
set fh [open $bios_hex r]
set words 0
while {[gets $fh line] >= 0} {
    set line [string trim $line]
    if {$line eq ""} { continue }
    if {![regexp {^[0-9a-fA-F]{8}$} $line]} {
        close $fh
        die "$bios_hex line [expr {$words + 1}] is not an 8 digit hex word: '$line'"
    }
    incr words
}
close $fh
if {$words < 1 || $words > $rom_words} {
    die "$bios_hex has $words words, the ROM holds $rom_words"
}
puts "INFO: BIOS image $bios_hex, $words of $rom_words words"
puts "INFO: this must be the FPGA image (TIMEOUT_DIV=1, 'make bios'), never bios_sim.hex"

# rom.sv does `include "rom_init_path.vh" outside Verilator: an absolute path that is always found
set fh [open [file join $out_dir rom_init_path.vh] w]
puts $fh "`define ROM_INIT_FILE \"$bios_hex\""
close $fh

# ---------------------------------------------------------------------------------------- sources
proc find_sv {dir} {
    set found {}
    foreach f [glob -nocomplain -directory $dir -types f *.sv] {
        lappend found [file normalize $f]
    }
    foreach d [glob -nocomplain -directory $dir -types d *] {
        set found [concat $found [find_sv $d]]
    }
    return $found
}

# packages first, in dependency order (same list as PKG_SRCS in the makefile); everything else after them
set pkg_files [list [file normalize [file join $design_dir rv32i.sv]] [file normalize [file join $design_dir uart.sv]]]
foreach f $pkg_files {
    if {![file exists $f]} { die "package $f not found" }
}
set other_files {}
foreach f [lsort [find_sv $design_dir]] {
    if {[lsearch -exact $pkg_files $f] < 0} { lappend other_files $f }
}
puts "INFO: [llength $pkg_files] package files + [llength $other_files] other SystemVerilog files from $design_dir"

read_verilog -sv $pkg_files
read_verilog -sv $other_files
if {$top ne "top"} {
    set test_file [file join $script_dir $top.sv]
    if {![file exists $test_file]} { die "top module '$top' requested but $test_file does not exist" }
    read_verilog -sv $test_file
    puts "INFO: top module $top from $test_file"
}
read_xdc $xdc_file

# ---------------------------------------------------------------------------------------- synthesis
synth_design -top $top -part $part -include_dirs [list $out_dir]
write_checkpoint -force post_synth.dcp
report_utilization -file post_synth_utilization.rpt

# ---------------------------------------------------------------------------------------- implementation
opt_design
place_design
route_design
write_checkpoint -force post_route.dcp
report_timing_summary -delay_type min_max -max_paths 10 -file post_route_timing.rpt
report_utilization -file post_route_utilization.rpt
report_clock_utilization -file post_route_clocks.rpt
report_drc -file post_route_drc.rpt

proc worst_slack {kind} {
    set p [get_timing_paths -$kind -max_paths 1]
    if {[llength $p] == 0} { return "" }
    return [get_property SLACK $p]
}
set wns [worst_slack setup]
set whs [worst_slack hold]
puts "INFO: worst setup slack '$wns' ns, worst hold slack '$whs' ns"
if {$wns ne "" && $wns < 0} { die "setup timing not met (worst slack $wns ns), see post_route_timing.rpt" }
if {$whs ne "" && $whs < 0} { die "hold timing not met (worst slack $whs ns), see post_route_timing.rpt" }

# ---------------------------------------------------------------------------------------- bitstream
write_bitstream -force $bit_name.bit
puts "INFO: done, bitstream: [file join $out_dir $bit_name.bit]"