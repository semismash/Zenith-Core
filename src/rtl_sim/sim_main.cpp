#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <iomanip>
#include <chrono>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vtop.h"
#include "Vtop___024root.h"

constexpr size_t RAM_SIZE = 65536;
constexpr size_t MAX_CYCLE_COUNT = 10000; // maximum safe cycle count for CPU before automatically crashing
constexpr bool AUTO_STOP = true; // automatically injects an 0xFFFFFFFF word in the end of the program to signal the CPU simulation to stop at the end
constexpr size_t PIPELINE_STAGES = 5;

// --- GPR TRACKING CONFIGURATION (Compile-Time Validated) ---
constexpr int MIN_GPR = 1; // inclusive
constexpr int MAX_GPR = 31; // inclusive

static_assert(MIN_GPR >= 1 && MIN_GPR <= 31, "[COMPILE ERROR] MIN_GPR must be between 1 and 31!");
static_assert(MAX_GPR >= 1 && MAX_GPR <= 31, "[COMPILE ERROR] MAX_GPR must be between 1 and 31!");
static_assert(MIN_GPR <= MAX_GPR, "[COMPILE ERROR] MIN_GPR cannot be greater than MAX_GPR!");

double sc_time_stamp() {
    return 0;
}

namespace std {
    namespace __cxx11 {
        template class basic_string<char>;
    }
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    std::ifstream file("tmp/program.bin", std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "[TB ERROR] Could not open program binary (program.bin)!" << std::endl;
        return -1;
    }

    std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> ram_buffer(file_size);
    if (!file.read(ram_buffer.data(), file_size)) {
        std::cerr << "[TB ERROR] Failed to read program.bin content." << std::endl;
        return -1;
    }

    std::cout << "========================================================" << std::endl;
    std::cout << "[TB] VERIFYING PROGRAM.BIN BYTES (LITTLE-ENDIAN WORDS):" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    for (size_t i = 0; i < ram_buffer.size(); i += 4) {
        std::cout << "Addr 0x" << std::hex << std::setw(8) << std::setfill('0') << i << ": 0x";
        for (int b = 3; b >= 0; --b) {
            if (i + b < ram_buffer.size()) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)(uint8_t)ram_buffer[i + b];
            } else {
                std::cout << "00";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "========================================================\n" << std::endl;

    auto DUT = std::make_unique<Vtop>();
    auto trace = std::make_unique<VerilatedVcdC>();
    DUT->trace(trace.get(), 99);
    trace->open("waveform.vcd");

    if (file_size > RAM_SIZE) {
        std::cerr << "[TB ERROR] Binary size exceeds 64KB limit!" << std::endl;
        return -1;
    }
    
    for (size_t i = 0; i < ram_buffer.size(); ++i) {
        DUT->rootp->top__DOT__u_instr_mem__DOT__container[i] = ram_buffer[i]; // initialize program into instruction memory
        DUT->rootp->top__DOT__u_data_mem__DOT__container[i] = ram_buffer[i];  // if any data intiialization left via .word directives
    }

    if (AUTO_STOP && (ram_buffer.size() + 4 <= RAM_SIZE)) {
        for (size_t b = 0; b < 4; ++b) {
            DUT->rootp->top__DOT__u_instr_mem__DOT__container[ram_buffer.size() + b] = (char)0xFF;
        }
    }

    // reset in the beginning to initialize, and set clk to 0
    DUT->rst_n = 0;
    DUT->clk = 0;
    DUT->eval(); 
    trace->dump(0);
    
    DUT->rst_n = 1;
    DUT->eval(); 
    std::cout << "[TB] Reset de-asserted. Commencing execution loop..." << std::endl;

    uint64_t cycles = 0;
    uint64_t sim_time = 1;

    // Start benchmark clocking session right before loop initialization
    auto start_wall_time = std::chrono::high_resolution_clock::now();

    while (!Verilated::gotFinish() && !DUT->halt && !DUT->stop) {
        DUT->clk = 0;
        DUT->eval();
        trace->dump(sim_time++);

        DUT->clk = 1;
        DUT->eval();
        trace->dump(sim_time++);
        cycles++;

        uint32_t current_pc    = DUT->rootp->top__DOT__if_addr;
        uint32_t instruction   = DUT->rootp->top__DOT__instr;
        uint32_t mem_data_addr = DUT->rootp->top__DOT__data_addr;
        uint32_t mem_wdata     = DUT->rootp->top__DOT__write_data;
        bool     mem_we        = DUT->rootp->top__DOT__write_enable;

        std::cout << "\n========================================================" << std::endl;
        std::cout << "[CYCLE " << std::dec << cycles << "]  Executing at PC: 0x" 
                  << std::hex << std::setw(8) << std::setfill('0') << current_pc << std::endl;
        std::cout << " -> Raw Instruction Hex:  0x" << std::setw(8) << instruction << std::endl;
        std::cout << " -------------------- REGISTER FILE --------------------" << std::endl;
        
        int printed_in_row = 0;
        std::cout << " -> ";
        for (int r = MIN_GPR; r <= MAX_GPR; ++r) {
            uint32_t reg_val = DUT->rootp->top__DOT__u_cpu__DOT__u_reg_file__DOT__registers[r];
            
            // format register number to always use 2 digits with zero-padding (e.g., x01, x12)
            std::cout << "x" << std::dec << std::setw(2) << std::setfill('0') << r << ": 0x" 
                      << std::hex << std::setw(8) << std::right << std::setfill('0') << reg_val;
            
            printed_in_row++;
            if (printed_in_row == 4 && r != MAX_GPR) {
                std::cout << "\n -> ";
                printed_in_row = 0;
            } else if (r != MAX_GPR) {
                std::cout << " | ";
            }
        }
        std::cout << std::endl;

        std::cout << " ----------------------- CONTROLS ----------------------" << std::endl;
        std::cout << " -> Data Memory Access:   [" << (mem_we ? "WRITE" : "READ") << "] "
                  << "Addr: 0x" << mem_data_addr << " | WData: 0x" << mem_wdata << std::endl;

        if (cycles > MAX_CYCLE_COUNT) {
            std::cout << "\n[TB WARNING] Safety simulation cutoff breached!" << std::endl;
            break;
        }
    }

    // Stop wall-clock timing right as simulation drops out
    auto end_wall_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_wall_time - start_wall_time;

    std::cout << "\n========================================================" << std::endl;
    if (DUT->halt) {
        std::cout << "[TB INFO] CPU core crashed safely and generated a HALT signal." << std::endl;
        std::cout << "[FINAL STATUS]" << std::endl;
        std::cout << " -> Final Data Address: 0x" << std::hex << DUT->rootp->top__DOT__data_addr << std::endl;
        std::cout << " -> Final Data Out:     0x" << std::hex << DUT->rootp->top__DOT__write_data << std::endl;
    } else if (DUT->stop) {
        std::cout << "[TB INFO] CPU core stopped safety and reached a safe STOP signal." << std::endl;
        std::cout << "[FINAL STATUS]" << std::endl;
        std::cout << " -> Final Data Address: 0x" << std::hex << DUT->rootp->top__DOT__data_addr << std::endl;
        std::cout << " -> Final Data Out:     0x" << std::hex << DUT->rootp->top__DOT__write_data << std::endl;
    } else {
        std::cout << "[TB INFO] Simulation finished processing." << std::endl;
    }

    // Capture telemetry signals directly from the new hardware output ports
    uint32_t total_retired_instr = DUT->meta_instr_count;
    uint32_t total_stalls        = DUT->meta_stall_count;
    uint32_t load_use_stalls     = DUT->meta_l_use_count;
    uint32_t branch_flushes      = DUT->meta_br_flush_count;

    std::cout << "\n------------------- PERFORMANCE METRICS -------------------" << std::endl;
    std::cout << "Total Clock Cycles:       " << std::dec << cycles << std::endl;
    std::cout << "Instructions Retired:     " << total_retired_instr << std::endl;
    
    if (total_retired_instr > 0) {
        uint64_t steady_state_cycles = (cycles > (PIPELINE_STAGES - 1)) ? (cycles - (PIPELINE_STAGES - 1)) : 0;
        
        double cpi_clean = static_cast<double>(cycles) / total_retired_instr;
        double cpi_steady = static_cast<double>(steady_state_cycles) / total_retired_instr;
        
        std::cout << "Measured CPI (w/ Overhead): " << std::fixed << std::setprecision(2) << cpi_clean << std::endl;
        std::cout << "Steady-State CPI (True):    " << std::fixed << std::setprecision(2) << cpi_steady << std::endl;
    } else {
        std::cout << "Measured CPI (w/ Overhead): N/A" << std::endl;
        std::cout << "Steady-State CPI (True):    N/A" << std::endl;
    }

    std::cout << " ------------------ MICROARCHITECTURAL STATS --------------" << std::endl;
    std::cout << "Total Stall Cycles:       " << std::dec << total_stalls;
    if (cycles > 0) {
        double stall_ratio = (static_cast<double>(total_stalls) / cycles) * 100.0;
        std::cout << " (" << std::fixed << std::setprecision(1) << stall_ratio << "% of cycles)" << std::endl;
    } else {
        std::cout << " (0.0%)" << std::endl;
    }

    std::cout << " -> Load-Use Stalls:      " << load_use_stalls << std::endl;
    std::cout << " -> Structural/ALU Stalls:" << (total_stalls - load_use_stalls) << std::endl;
    std::cout << "Total Branch Flush Cycles:" << branch_flushes << std::endl;

    std::cout << " ------------------- SIMULATION SPEED ---------------------" << std::endl;
    std::cout << "Elapsed Compute Time:     " << std::fixed << std::setprecision(6) << elapsed_seconds.count() << " seconds" << std::endl;
    
    if (elapsed_seconds.count() > 0.0) {
        double sim_hz = static_cast<double>(cycles) / elapsed_seconds.count();
        if (sim_hz >= 1000000.0) {
            std::cout << "Simulation Frequency:     " << std::fixed << std::setprecision(2) << (sim_hz / 1000000.0) << " MHz" << std::endl;
        } else if (sim_hz >= 1000.0) {
            std::cout << "Simulation Frequency:     " << std::fixed << std::setprecision(2) << (sim_hz / 1000.0) << " kHz" << std::endl;
        } else {
            std::cout << "Simulation Frequency:     " << std::fixed << std::setprecision(2) << sim_hz << " Hz" << std::endl;
        }
    } else {
        std::cout << "Simulation Frequency:     N/A" << std::endl;
    }
    std::cout << "========================================================\n" << std::endl;

    trace->close();
    DUT->final();
    return 0;
}