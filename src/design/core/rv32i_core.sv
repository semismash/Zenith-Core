import rv32i::*;
import uart::*;

// NOTE: The RTL in this file was rewritten with the help of AI using logic dictated by the programmer, and was then human reviewed and tested.

module rv32i_core (
    input logic clk,            // CPU clock
    input logic rst_n,          // active low reset

    // AXI4-Lite master, instruction port (to mem.sv), driven by fetch.sv
    output Word  if_araddr,         
    output logic if_arvalid,        
    input  logic if_arready,        
    input  logic if_rvalid,         
    output logic if_rready,         
    input  Word  if_rdata,          
    input  Resp  if_rresp,          

    // AXI4-Lite master, data port (to mem.sv), LSU traffic that is not MMIO
    output Word  data_awaddr,       
    output logic data_awvalid,      
    input  logic data_awready,      
    output Word  data_wdata,        
    output logic [3:0] data_wstrb,  
    output logic data_wvalid,       
    input  logic data_wready,       
    input  logic data_bvalid,       
    output logic data_bready,       
    input  Resp  data_bresp,        
    output Word  data_araddr,       
    output logic data_arvalid,      
    input  logic data_arready,      
    input  Word  data_rdata,        
    input  logic data_rvalid,       
    output logic data_rready,       
    input  Resp  data_rresp,        

    output logic halt,              // halt on panic;sticky (any fault), freezes the core until reset
    output logic instr_fault_out,   // instr fetch fault; sticky
    output logic data_fault_out,    //  data fetch fault; sticky
    output logic illegal_instr_out, // illegal instr fault;
    output logic stop,              // safe halt (called by ecall or ebreak); sticky

    // I/O
    input logic i_rx,
    output logic o_tx

    // telemetry
    // output MetaCount meta_instr_count,
    // output MetaCount meta_stall_count,
    // output MetaCount meta_l_use_count,
    // output MetaCount meta_br_flush_count
);

    // hazard unit
    logic hz_pc_enable;
    logic hz_if_id_enable;
    logic hz_id_ex_enable;
    logic hz_ex_mem_enable;
    logic hz_mem_wb_enable;
    logic hz_if_id_clear;
    logic hz_id_ex_clear;
    logic hz_meta_is_stall;
    logic hz_meta_is_l_use;
    logic hz_meta_branch_flush;
    logic hz_meta_is_instr;     // instruction counter pulse, straight from the hazard unit

    Word  fetch_pc;
    logic fetch_valid;
    logic data_fetch_valid;
    logic mem_stage_busy;
    logic lsu_pre_fault;        // access rejected by the LSU prechecks
    logic lsu_data_fault;       // any data fault this cycle
    logic wb_data_wait;         // load in WB without its R yet
    logic stop_in_flight;       // ECALL / EBREAK in EX, MEM or WB
    logic freeze;               // sticky STOP or HALT
    logic id_kill;              // ID instruction is illegal or faulted, its control signals are forced to a bubble
    Word  fwd_jalr_rs1;         // forwarded rs1 for the JALR target (pc.sv)
    Word  pc_target;            // redirect target from pc.sv
    Word  wb_rd_data;           // value written back (load extracted in WB), also the MEM/WB forwarding source
    logic load_fault;           // WB load returned an error, its register write is dropped
    logic wb_cap_valid;         // the WB load's R already arrived while WB was held (RREADY is 1, so it must be kept)
    Word  wb_cap_data;
    Resp  wb_cap_resp;
    Word  wb_rdata;             // R data seen by write_back.sv (captured copy while held)
    Resp  wb_rresp;

    // LSU <-> data decoder
    Word  data_araddr_out;      
    logic data_arvalid_out;     
    logic data_arready_in;      
    Word  data_rdata_in;        
    logic data_rvalid_in;       
    logic data_rready_out;      
    Resp  data_rresp_in;        
    Word  data_awaddr_out;      
    logic data_awvalid_out;     
    logic data_awready_in;      
    Word  data_wdata_out;       
    logic [3:0] data_wstrb_out; 
    logic data_wvalid_out;      
    logic data_wready_in;       
    logic data_bvalid_in;       
    logic data_bready_out;      
    Resp  data_bresp_in;        

    // data decoder <-> mmio_interface
    Word  mmio_araddr;          
    logic mmio_arvalid;         
    logic mmio_arready;         
    Word  mmio_rdata;           
    logic mmio_rvalid;          
    logic mmio_rready;          
    Resp  mmio_rresp;           
    Word  mmio_awaddr;          
    logic mmio_awvalid;         
    logic mmio_awready;         
    Word  mmio_wdata;           
    logic [3:0] mmio_wstrb;     
    logic mmio_wvalid;          
    logic mmio_wready;          
    logic mmio_bvalid;          
    logic mmio_bready;          
    Resp  mmio_bresp;           

    // ticky STOP / fault flags (LEDs)
    logic stop_q;               
    logic instr_fault_q;        
    logic data_fault_q;         
    logic illegal_q;            

    // fetch
    logic if_fault_out;
    Instruction instr;
    logic if_id_fault;          // fetch fault carried in IF/ID

    // Reg File
    logic   reg_w_enable;
    RegAddr rdst_addr;
    Word    rdst_data;
    RegAddr rs1_addr;
    RegAddr rs2_addr;
    Word    rs1_data;
    Word    rs2_data;

    // PC
    logic pc_in1_sel;

    // IF/ID
    Word if_id_pc;
    Instruction if_id_instr;
    OpCode if_id_opcode;
    RegAddr if_id_rs1_addr;
    RegAddr if_id_rs2_addr;

    // decoder
    logic mem_to_reg;
    logic imm_to_reg;        
    logic illegal_instr_fault;
    logic d_is_branch;
    logic d_is_jal;
    logic d_is_jalr;
    logic d_stop;

    // imm
    Word imm_val;
    ImmPackFmt imm_type;

    // ID/EX
    Word id_ex_pc;
    RegAddr id_ex_rs1_addr;
    RegAddr id_ex_rs2_addr;
    RegAddr id_ex_rd_addr;
    OpCode id_ex_opcode;
    Word id_ex_rs1_data;
    Word id_ex_rs2_data;
    Word fwd_store_data;  // rs2, forwarded, for store-data path (bypasses the ALU entirely so needs its own mux)
    Word id_ex_imm_val;
    logic id_ex_alu_in1_ropc;
    logic id_ex_alu_in2_roi;    // reconsider this, replace with branch taken condition later on
    AluOp id_ex_alu_op;
    logic id_ex_alu_bypass;
    logic id_ex_mem_read;
    logic id_ex_mem_write;
    logic [2:0] id_ex_funct3;
    logic id_ex_pc_in1_sel;
    logic id_ex_is_branch;
    logic id_ex_is_jal;
    logic id_ex_is_jalr;
    logic id_ex_reg_write;
    logic id_ex_imm_to_reg;
    logic id_ex_mem_to_reg;
    logic id_ex_stop;           
    logic id_ex_illegal;        
    logic id_ex_if_fault;       

    // alu
    AluOp alu_op;
    logic alu_in1_sel;
    logic alu_in2_sel;
    logic alu_bypass;
    logic alu_zero;
    Word alu_out;

    // branch unit
    logic branch_taken;

    // EX/MEM
    Word ex_mem_rs2_val;
    RegAddr ex_mem_rd_addr;
    Word ex_mem_result;
    logic ex_mem_mem_read;
    logic ex_mem_mem_write;
    logic [2:0] ex_mem_funct3;
    logic ex_mem_reg_write;
    logic ex_mem_mem_to_reg;
    logic ex_mem_stop;          

    // lsu
    logic [2:0] funct3;
    logic mem_read;
    logic mem_write;

    // MEM/WB
    RegAddr mem_wb_rd_addr;
    Word mem_wb_result;
    logic mem_wb_reg_write;
    logic mem_wb_mem_to_reg;    
    logic [2:0] mem_wb_funct3;  
    logic [1:0] mem_wb_addr_lo; 
    logic mem_wb_stop;          


    // forwarding unit
    logic fwd_alu_in1_ex_mem;
    logic fwd_alu_in1_mem_wb;
    logic fwd_alu_in2_ex_mem;
    logic fwd_alu_in2_mem_wb;

    logic [7:0] uart_rx_data;
    logic       uart_rx_valid;
    logic [7:0] uart_tx_data;
    logic       uart_tx_start;
    logic       uart_tx_busy;
    logic       uart_rx_ack;

    // meta unit
    logic meta_clear;
    logic meta_enable;
    MetaCount meta_instr_count;
    MetaCount meta_stall_count;
    MetaCount meta_l_use_count;
    MetaCount meta_br_flush_count;

    Word ex_result;
    Word pc_plus4;

    assign pc_plus4  = id_ex_pc + 32'd4;
    assign ex_result = (id_ex_is_jal || id_ex_is_jalr) ? pc_plus4 : alu_out;
gns
    assign data_fetch_valid = !mem_stage_busy;
    assign wb_rdata         = wb_cap_valid ? wb_cap_data : data_rdata_in;              
    assign wb_rresp         = wb_cap_valid ? wb_cap_resp : data_rresp_in;              
    assign wb_data_wait     = mem_wb_mem_to_reg && !data_rvalid_in && !wb_cap_valid;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin                                                               
            wb_cap_valid <= 1'b0;                                                       
            wb_cap_data  <= '0;                                                         
            wb_cap_resp  <= RESP_OKAY;                                                  
        end else if (hz_mem_wb_enable) begin
            wb_cap_valid <= 1'b0;                                                       
        end else if (mem_wb_mem_to_reg && data_rvalid_in && !wb_cap_valid) begin
            wb_cap_valid <= 1'b1;                                                       
            wb_cap_data  <= data_rdata_in;                                              
            wb_cap_resp  <= data_rresp_in;                                              
        end                                                                             
    end                                                                                 
    assign stop_in_flight   = id_ex_stop | ex_mem_stop | mem_wb_stop;                  
    assign id_kill          = illegal_instr_fault | if_id_fault;                       
    assign fwd_jalr_rs1     = fwd_alu_in1_ex_mem ? ex_mem_result : fwd_alu_in1_mem_wb ? wb_rd_data : id_ex_rs1_data;

    reg_file u_reg_file(
        // clk and reset
        .clk            (clk),
        .rst_n          (rst_n), 
        // write
        .w_enable       (mem_wb_reg_write && !load_fault && !wb_data_wait),
        .w_addr         (mem_wb_rd_addr),
        .w_data         (wb_rd_data),
        // read address
        .r_addr1        (rs1_addr),
        .r_addr2        (rs2_addr),
        // reg data output
        .r_data1        (rs1_data),
        .r_data2        (rs2_data)
    );

    pc u_pc(    // x
        // from decoder
        .pcinc_in1_pcor (id_ex_pc_in1_sel),
        // from reg and imm gen, based on decoder signal
        .rs1_in         (fwd_jalr_rs1),
        .pc_in          (id_ex_pc),
        .imm_in         (id_ex_imm_val),
        // out
        .pc_target      (pc_target)
    );

    fetch #(    // X
        .DATA_WIDTH        (rv32i::DATA_WIDTH),
        .MAX_OUTSTANDING   (2)                  // pipelined fetch (1 = strict)
    ) u_fetch (
        // clock, reset, and stall
        .clk               (clk),
        .rst_n             (rst_n),
        .stall             (!hz_if_id_enable),  // IF/ID frozen (was !hz_pc_enable, the PC register moved into fetch)
        // redirect from EX
        .redirect          (branch_taken),      
        .redirect_pc       (pc_target),         
        // AXI4-Lite instruction port (straight to the core ports)
        .if_araddr         (if_araddr),
        .if_arvalid        (if_arvalid),        
        .if_arready        (if_arready),        
        .if_rvalid         (if_rvalid),
        .if_rdata          (if_rdata),
        .if_rresp          (if_rresp),
        .if_rready         (if_rready),         
        // outputs
        .pc_out            (fetch_pc),
        .instr_out         (instr),
        .mem_fault         (if_fault_out),
        .fetch_valid       (fetch_valid)
    );

    if_id u_if_id (
        // clk and reset
        .clk            (clk),
        .rst_n          (rst_n),
        .stall          (!hz_if_id_enable),
        .clear          (hz_if_id_clear),
        // input
        .i_pc           (fetch_pc),
        .i_instr        (instr),
        .i_fault        (if_fault_out),     // fetch fault travels with the instruction
        // output
        .o_pc           (if_id_pc),
        .o_instr        (if_id_instr),      // added trailing comma for o_fault
        .o_fault        (if_id_fault)       
    );

    // direct primitive slice (does not require explicit decoding)
    assign if_id_opcode     = OpCode'(if_id_instr[6:0]);
    assign if_id_rs1_addr   = RegAddr'(if_id_instr[19:15]);
    assign if_id_rs2_addr   = RegAddr'(if_id_instr[24:20]);

    decoder u_decoder(
        // IN
        .instr          (if_id_instr),
        //.alu_zero       (alu_zero),
        .rs1_addr       (rs1_addr),
        .rs2_addr       (rs2_addr),
        .rd_addr        (rdst_addr),
        // branches
        .is_branch      (d_is_branch),
        .is_jal         (d_is_jal),
        .is_jalr        (d_is_jalr),
        // ALU
        .alu_op         (alu_op),
        .alu_in1_ropc   (alu_in1_sel),
        .alu_in2_roi    (alu_in2_sel),
        .alu_bypass     (alu_bypass),
        // REG FILE
        .reg_write      (reg_w_enable),
        // LSU
        .mem_read       (mem_read),
        .mem_write      (mem_write),
        .mem_to_reg     (mem_to_reg),
        .imm_to_reg     (imm_to_reg),
        // IMM GEN
        .imm_val        (imm_val),
        // PC
        .pcinc_in1_pcor (pc_in1_sel),
        //.pcinc_in2_doi  (pc_in2_sel), (CHECK AGAIN)
        // funct3
        .funct3         (funct3),
        // panic
        .illegal_instr  (illegal_instr_fault),
        .stop           (d_stop)            // goes down the pipe, the stop port is the sticky flag now
    );

    id_ex u_id_ex (
        // clk and reset
        .clk              (clk),
        .rst_n            (rst_n),
        .stall            (!hz_id_ex_enable),
        .clear            (hz_id_ex_clear),
        // input
        .i_opcode         (if_id_opcode),
        .i_pc             (if_id_pc),
        .i_rs1_addr       (rs1_addr),
        .i_rs2_addr       (rs2_addr),
        .i_rd_addr        (rdst_addr),
        .i_rs1_data       (rs1_data),
        .i_rs2_data       (rs2_data),
        .i_imm_val        (imm_val),
        .i_alu_in1_ropc   (alu_in1_sel),
        .i_alu_in2_roi    (alu_in2_sel),
        .i_alu_op         (alu_op),
        .i_alu_bypass     (alu_bypass),
        .i_mem_read       (mem_read & ~id_kill),        // an illegal or faulted instruction carries no side effects to EX
        .i_mem_write      (mem_write & ~id_kill),       // ditto
        .i_funct3         (funct3),
        .i_pc_in1_sel     (pc_in1_sel),
        .i_is_branch      (d_is_branch & ~id_kill),     // ditto
        .i_is_jal         (d_is_jal & ~id_kill),        // ditto
        .i_is_jalr        (d_is_jalr & ~id_kill),       // dtito
        .i_reg_write      (reg_w_enable & ~id_kill),    // ditto
        .i_imm_to_reg     (imm_to_reg),
        .i_mem_to_reg     (mem_to_reg & ~id_kill),      // ditto
        .i_is_stop        (d_stop),
        .i_illegal        (id_kill),                    // decode-illegal or fetch fault, flushed with the instruction if it was on a wrong path
        .i_if_fault       (if_id_fault),
        // output
        .o_opcode         (id_ex_opcode),
        .o_pc             (id_ex_pc),
        .o_rs1_addr       (id_ex_rs1_addr),
        .o_rs2_addr       (id_ex_rs2_addr),
        .o_rd_addr        (id_ex_rd_addr),
        .o_rs1_data       (id_ex_rs1_data),
        .o_rs2_data       (id_ex_rs2_data),
        .o_imm_val        (id_ex_imm_val),
        .o_alu_in1_ropc   (id_ex_alu_in1_ropc),
        .o_alu_in2_roi    (id_ex_alu_in2_roi),
        .o_alu_op         (id_ex_alu_op),
        .o_alu_bypass     (id_ex_alu_bypass),
        .o_mem_read       (id_ex_mem_read),
        .o_mem_write      (id_ex_mem_write),
        .o_funct3         (id_ex_funct3),
        .o_pc_in1_sel     (id_ex_pc_in1_sel),
        .o_is_branch      (id_ex_is_branch),
        .o_is_jal         (id_ex_is_jal),
        .o_is_jalr        (id_ex_is_jalr),
        .o_reg_write      (id_ex_reg_write),
        .o_imm_to_reg     (id_ex_imm_to_reg),
        .o_mem_to_reg     (id_ex_mem_to_reg),
        .o_is_stop        (id_ex_stop),
        .o_illegal        (id_ex_illegal),    
        .o_if_fault       (id_ex_if_fault)    
    );

    alu u_alu(  // x
        // from ID
        .alu_op             (id_ex_alu_op),
        .alu_bypass         (id_ex_alu_bypass),
        .imm_to_reg         (id_ex_imm_to_reg),
        // from REG FILE
        .r_data1            (id_ex_rs1_data),
        .r_data2            (id_ex_rs2_data),
        // from PC & ID
        .pc                 (id_ex_pc),
        .use_pc             (id_ex_alu_in1_ropc),
        // from IMM & ID
        .imm                (id_ex_imm_val),
        .use_imm            (id_ex_alu_in2_roi),  
        // for forwarding
        .fwd_alu_in1_ex_mem (fwd_alu_in1_ex_mem),
        .fwd_alu_in2_ex_mem (fwd_alu_in2_ex_mem),
        .fwd_alu_in1_mem_wb (fwd_alu_in1_mem_wb),
        .fwd_alu_in2_mem_wb (fwd_alu_in2_mem_wb),
        // forwarded data
        .ex_mem_rd_data     (ex_mem_result),
        .mem_wb_rd_data     (wb_rd_data),           // write-back value (load extracted in WB)
        // OUT
        .alu_out            (alu_out),
        .out_zero           (alu_zero)
    );

    branch_unit u_branch_unit (
        // input
        .is_branch      (id_ex_is_branch),
        .is_jal         (id_ex_is_jal),
        .is_jalr        (id_ex_is_jalr),
        .id_ex_funct3   (id_ex_funct3),
        .alu_zero       (alu_zero),
        // output
        .branch_taken   (branch_taken)
    );

    // forwards data for storing too as rs2 never actually went through ALU, js pass into EX/MEM directly here
    assign fwd_store_data = fwd_alu_in2_ex_mem ? ex_mem_result : fwd_alu_in2_mem_wb ? wb_rd_data : id_ex_rs2_data;  // MEM/WB source is the write-back value now

    ex_mem u_ex_mem (
        // clk and reset
        .clk            (clk),
        .rst_n          (rst_n),
        .stall          (!hz_ex_mem_enable),
        .clear          (1'b0),
        // input
        .i_rs2_val      (fwd_store_data),
        .i_rd_addr      (id_ex_rd_addr),
        .i_result       (ex_result),
        .i_mem_read     (id_ex_mem_read),
        .i_mem_write    (id_ex_mem_write),
        .i_funct3       (id_ex_funct3),
        .i_reg_write    (id_ex_reg_write),
        .i_mem_to_reg   (id_ex_mem_to_reg),
        .i_is_stop      (id_ex_stop),       // replaces i_valid_instr
        // output
        .o_rs2_val      (ex_mem_rs2_val),
        .o_rd_addr      (ex_mem_rd_addr),
        .o_result       (ex_mem_result),
        .o_mem_read     (ex_mem_mem_read),
        .o_mem_write    (ex_mem_mem_write),
        .o_funct3       (ex_mem_funct3),
        .o_reg_write    (ex_mem_reg_write),
        .o_mem_to_reg   (ex_mem_mem_to_reg),
        .o_is_stop      (ex_mem_stop)       // replaces o_valid_instr
    );

    lsu #(  // X
        .DATA_WIDTH        (rv32i::DATA_WIDTH)
    ) u_lsu (
        .clk               (clk),
        .rst_n             (rst_n),
        .funct3            (ex_mem_funct3),

        .alu_res           (ex_mem_result),
        .is_mem_read       (ex_mem_mem_read),
        .is_mem_write      (ex_mem_mem_write),
        .rs2_in            (ex_mem_rs2_val),

        .mem_advance       (hz_ex_mem_enable),      // next instruction enters MEM at this edge
        .freeze            (freeze),                // no requests once STOP / HALT is latched

        // AXI4-Lite master -> data decoder
        .data_araddr       (data_araddr_out),       
        .data_arvalid      (data_arvalid_out),      
        .data_arready      (data_arready_in),       
        .data_rvalid       (data_rvalid_in),        
        .data_rresp        (data_rresp_in),         
        .data_rready       (data_rready_out),       
        .data_awaddr       (data_awaddr_out),       
        .data_awvalid      (data_awvalid_out),      
        .data_awready      (data_awready_in),       
        .data_wdata        (data_wdata_out),        
        .data_wstrb        (data_wstrb_out),        
        .data_wvalid       (data_wvalid_out),       
        .data_wready       (data_wready_in),        
        .data_bvalid       (data_bvalid_in),        
        .data_bresp        (data_bresp_in),         
        .data_bready       (data_bready_out),       

        .mem_stage_busy    (mem_stage_busy),
        .pre_fault         (lsu_pre_fault),         
        .data_fault        (lsu_data_fault)         
    );

    data_decoder u_data_decoder (                   // LSU -> MMIO (address bit 31) or the external data port
        .clk               (clk),                   
        .rst_n             (rst_n),                 
        // master side (LSU)
        .m_araddr          (data_araddr_out),       
        .m_arvalid         (data_arvalid_out),      
        .m_arready         (data_arready_in),       
        .m_rdata           (data_rdata_in),         
        .m_rvalid          (data_rvalid_in),        
        .m_rready          (data_rready_out),       
        .m_rresp           (data_rresp_in),         
        .m_awaddr          (data_awaddr_out),       
        .m_awvalid         (data_awvalid_out),      
        .m_awready         (data_awready_in),       
        .m_wdata           (data_wdata_out),        
        .m_wstrb           (data_wstrb_out),        
        .m_wvalid          (data_wvalid_out),       
        .m_wready          (data_wready_in),        
        .m_bvalid          (data_bvalid_in),        
        .m_bready          (data_bready_out),       
        .m_bresp           (data_bresp_in),         
        // slave 0: MMIO
        .mmio_araddr       (mmio_araddr),           
        .mmio_arvalid      (mmio_arvalid),          
        .mmio_arready      (mmio_arready),          
        .mmio_rdata        (mmio_rdata),            
        .mmio_rvalid       (mmio_rvalid),           
        .mmio_rready       (mmio_rready),           
        .mmio_rresp        (mmio_rresp),            
        .mmio_awaddr       (mmio_awaddr),           
        .mmio_awvalid      (mmio_awvalid),          
        .mmio_awready      (mmio_awready),          
        .mmio_wdata        (mmio_wdata),            
        .mmio_wstrb        (mmio_wstrb),            
        .mmio_wvalid       (mmio_wvalid),           
        .mmio_wready       (mmio_wready),           
        .mmio_bvalid       (mmio_bvalid),           
        .mmio_bready       (mmio_bready),           
        .mmio_bresp        (mmio_bresp),            
        // slave 1: external port (core outputs to mem.sv)
        .ext_araddr        (data_araddr),           
        .ext_arvalid       (data_arvalid),          
        .ext_arready       (data_arready),          
        .ext_rdata         (data_rdata),            
        .ext_rvalid        (data_rvalid),           
        .ext_rready        (data_rready),           
        .ext_rresp         (data_rresp),            
        .ext_awaddr        (data_awaddr),           
        .ext_awvalid       (data_awvalid),          
        .ext_awready       (data_awready),          
        .ext_wdata         (data_wdata),            
        .ext_wstrb         (data_wstrb),            
        .ext_wvalid        (data_wvalid),           
        .ext_wready        (data_wready),           
        .ext_bvalid        (data_bvalid),           
        .ext_bready        (data_bready),           
        .ext_bresp         (data_bresp)             
    );

    mmio_interface u_mmio_interface (   // X
        .clk                (clk),
        .rst_n              (rst_n),
        // AXI4-Lite slave <- data decoder
        .data_araddr        (mmio_araddr),          
        .data_arvalid       (mmio_arvalid),         
        .data_arready       (mmio_arready),         
        .data_rdata         (mmio_rdata),           
        .data_rvalid        (mmio_rvalid),          
        .data_rready        (mmio_rready),          
        .data_rresp         (mmio_rresp),           
        .data_awaddr        (mmio_awaddr),          
        .data_awvalid       (mmio_awvalid),         
        .data_awready       (mmio_awready),         
        .data_wdata         (mmio_wdata),           
        .data_wstrb         (mmio_wstrb),           
        .data_wvalid        (mmio_wvalid),          
        .data_wready        (mmio_wready),          
        .data_bvalid        (mmio_bvalid),          
        .data_bready        (mmio_bready),          
        .data_bresp         (mmio_bresp),           
        // TO I/O modules:
        // UART RX/TX
        .uart_rx_data       (uart_rx_data),
        .uart_rx_valid      (uart_rx_valid),
        .uart_tx_data       (uart_tx_data),
        .uart_tx_start      (uart_tx_start),
        .uart_tx_busy       (uart_tx_busy),
        .uart_rx_ack        (uart_rx_ack),
        // TELEMETRY UNIT
        .meta_enable        (meta_enable),
        .meta_clear         (meta_clear),
        .meta_instr_count   (meta_instr_count),
        .meta_stall_count   (meta_stall_count),
        .meta_l_use_count   (meta_l_use_count),
        .meta_br_flush_count(meta_br_flush_count)
    );

    mem_wb u_mem_wb (
        // clk
        .clk            (clk),
        .rst_n          (rst_n),
        .stall          (!hz_mem_wb_enable),
        .clear          (1'b0),
        // input
        .i_rd_addr      (ex_mem_rd_addr),
        .i_result       (ex_mem_result),    // replaces .i_rd_data (reg_write_data)
        .i_reg_write    (ex_mem_reg_write && !lsu_pre_fault),   // a rejected access writes nothing
        .i_mem_to_reg   (ex_mem_mem_to_reg && !lsu_pre_fault),  // and is not a load in WB (no R will come)
        .i_funct3       (ex_mem_funct3),    
        .i_addr_lo      (ex_mem_result[1:0]),   
        .i_is_stop      (ex_mem_stop),
        // output
        .o_rd_addr      (mem_wb_rd_addr),
        .o_result       (mem_wb_result),    // replaces .o_rd_data
        .o_reg_write    (mem_wb_reg_write),
        .o_mem_to_reg   (mem_wb_mem_to_reg),    
        .o_funct3       (mem_wb_funct3),    
        .o_addr_lo      (mem_wb_addr_lo),   
        .o_is_stop      (mem_wb_stop)       // replaces .o_valid_instr
    );

    write_back u_write_back (               // load lane pick + sign / zero extension + mem_to_reg mux
        .funct3         (mem_wb_funct3),    
        .addr_lo        (mem_wb_addr_lo),   
        .mem_to_reg     (mem_wb_mem_to_reg),    
        .result         (mem_wb_result),    
        .data_rdata     (wb_rdata),         // R data of the load in WB (or its captured copy)
        .data_rresp     (wb_rresp),         
        .rd_data        (wb_rd_data),       
        .load_fault     (load_fault)        
    );

    hazard_unit u_hazard_unit ( // X
        // IF/ID (incl. OpCode bits)
        .if_id_opcode          (if_id_opcode),
        .id_ex_opcode          (id_ex_opcode),
        .if_id_rs1             (if_id_rs1_addr),
        .if_id_rs2             (if_id_rs2_addr),
        // ID/EX
        .id_ex_rs1             (id_ex_rs1_addr),
        .id_ex_rs2             (id_ex_rs2_addr),
        .id_ex_rd              (id_ex_rd_addr),
        // EX/MEM
        .ex_mem_rd             (ex_mem_rd_addr),
        // MEM/WB
        .mem_wb_rd             (mem_wb_rd_addr),
        // TO STALL UNIT DIRECTLY
        .id_ex_mem_read        (id_ex_mem_read),    // if load (X)
        .id_ex_reg_write       (id_ex_reg_write),   // if reg write (X)
        .branch_taken          (branch_taken),      // check if a branch was taken, to stall control hazards for now (X)
        .data_fetch_valid      (data_fetch_valid),
        .wb_data_wait          (wb_data_wait),          
        .freeze                (freeze),                
        .stop_in_flight        (stop_in_flight),        
        // TO FORWARDING UNIT DIRECTLY
        .ex_mem_reg_write      (ex_mem_reg_write),
        .mem_wb_reg_write      (mem_wb_reg_write),
        // OUTPUTS
        // STALLING
        .pc_enable             (hz_pc_enable),
        .if_id_enable          (hz_if_id_enable),
        .id_ex_enable          (hz_id_ex_enable),
        .ex_mem_enable         (hz_ex_mem_enable),
        .mem_wb_enable         (hz_mem_wb_enable),
        .if_id_clear           (hz_if_id_clear),
        .id_ex_clear           (hz_id_ex_clear),
        // FORWARDING
        .fwd_alu_in1_ex_mem    (fwd_alu_in1_ex_mem),    // forward to alu in 1 from src res in ex mem (X)
        .fwd_alu_in2_ex_mem    (fwd_alu_in2_ex_mem),    // forward to alu in 2 from src res in ex mem (X)
        .fwd_alu_in1_mem_wb    (fwd_alu_in1_mem_wb),    // forward to alu in 1 from src res in ex mem (X)
        .fwd_alu_in2_mem_wb    (fwd_alu_in2_mem_wb),    // forward to alu in 2 from src res in ex mem (X)
        // METADATA
        .meta_branch_flush     (hz_meta_branch_flush),
        .meta_is_stall         (hz_meta_is_stall),
        .meta_is_l_use         (hz_meta_is_l_use),
        .meta_is_instr         (hz_meta_is_instr)       
    );

    meta u_meta (
        .clk                    (clk),
        .rst_n                  (rst_n),
        .enable                 (meta_enable),
        .clear                  (meta_clear),
        .is_instr               (hz_meta_is_instr),     // counted at ID, replaces the pipelined valid_instr
        .is_stall               (hz_meta_is_stall),
        .is_l_use               (hz_meta_is_l_use),
        .is_br_flush            (hz_meta_branch_flush),
        .meta_instr_count       (meta_instr_count),
        .meta_stall_count       (meta_stall_count),
        .meta_l_use_count       (meta_l_use_count),
        .meta_br_flush_count    (meta_br_flush_count)
    );

    uart_module #(
        .CLK_FREQ         (CPU_CLOCK_FREQ),
        .BAUD_RATE        (UART_BAUD_RATE),
        .SAMPLING_RATE    (UART_SAMPLING_RATE)
    ) u_uart_module (
        // clock and reset
        .clk              (clk),
        .rst_n            (rst_n),
        // tx
        .tx_data          (uart_tx_data),
        .tx_start         (uart_tx_start),
        .tx               (o_tx),
        .tx_busy          (uart_tx_busy),
        // rx
        .rx               (i_rx),
        .rx_ack           (uart_rx_ack),
        .rx_data          (uart_rx_data),
        .rx_valid         (uart_rx_valid)
    );

    // sticky STOP and fault flags (cleared only by reset). A fault is only taken from an instruction that survives to EX
    // (fetch fault / illegal) or from the LSU, so wrong-path faults are flushed and can never halt the CPU
    always_ff @(posedge clk or negedge rst_n) begin                     
        if (!rst_n) begin                                               
            stop_q        <= 1'b0;                                      
            instr_fault_q <= 1'b0;                                      
            data_fault_q  <= 1'b0;                                      
            illegal_q     <= 1'b0;                                      
        end else begin                                                  
            if (mem_wb_stop)                     stop_q        <= 1'b1; // ECALL / EBREAK reached WB, everything older has finished
            if (id_ex_if_fault)                  instr_fault_q <= 1'b1; 
            if (id_ex_illegal && !id_ex_if_fault) illegal_q    <= 1'b1; // Na faulted fetch's garbage word does not also count as illegal
            if (lsu_data_fault)                  data_fault_q  <= 1'b1; 
        end                                                             
    end                                                                 

    assign freeze = stop_q | halt;                                      // holds every stage until reset

    assign halt = instr_fault_q | data_fault_q | illegal_q;             // was a combinational pulse from ID (wrong-path faults could halt)
    assign instr_fault_out = instr_fault_q;                             
    assign data_fault_out = data_fault_q;                               // was the raw memory fault
    assign illegal_instr_out = illegal_q;                               // was the raw decoder output
    assign stop = stop_q;                                               // was the decoder's stop straight from ID

endmodule