import rv32i::*;

module data_decoder (
    input  logic       clk,
    input  logic       rst_n,

    // master side (LSU)
    input  Word        m_araddr,
    input  logic       m_arvalid,
    output logic       m_arready,
    output Word        m_rdata,
    output logic       m_rvalid,
    input  logic       m_rready,
    output Resp        m_rresp,
    input  Word        m_awaddr,
    input  logic       m_awvalid,
    output logic       m_awready,
    input  Word        m_wdata,
    input  logic [3:0] m_wstrb,
    input  logic       m_wvalid,
    output logic       m_wready,
    output logic       m_bvalid,
    input  logic       m_bready,
    output Resp        m_bresp,

    // slave 0: MMIO (mmio_interface.sv)
    output Word        mmio_araddr,
    output logic       mmio_arvalid,
    input  logic       mmio_arready,
    input  Word        mmio_rdata,
    input  logic       mmio_rvalid,
    output logic       mmio_rready,
    input  Resp        mmio_rresp,
    output Word        mmio_awaddr,
    output logic       mmio_awvalid,
    input  logic       mmio_awready,
    output Word        mmio_wdata,
    output logic [3:0] mmio_wstrb,
    output logic       mmio_wvalid,
    input  logic       mmio_wready,
    input  logic       mmio_bvalid,
    output logic       mmio_bready,
    input  Resp        mmio_bresp,

    // slave 1: external memory port (mem.sv, ROM / RAM / default slave)
    output Word        ext_araddr,
    output logic       ext_arvalid,
    input  logic       ext_arready,
    input  Word        ext_rdata,
    input  logic       ext_rvalid,
    output logic       ext_rready,
    input  Resp        ext_rresp,
    output Word        ext_awaddr,
    output logic       ext_awvalid,
    input  logic       ext_awready,
    output Word        ext_wdata,
    output logic [3:0] ext_wstrb,
    output logic       ext_wvalid,
    input  logic       ext_wready,
    input  logic       ext_bvalid,
    output logic       ext_bready,
    input  Resp        ext_bresp
);

    // data-side AXI4-Lite decoder inside rv32i_core: LSU (master) -> MMIO slave or the external port to mem.sv
    // address bit 31 selects MMIO; one select register per direction steers the response back (i.e. fixed-latency slaves)

    logic rd_mmio;      // this AR targets MMIO
    logic wr_mmio;      // this AW / W targets MMIO
    logic rd_sel_q;     // 1 = the outstanding R comes from MMIO
    logic wr_sel_q;     // 1 = the outstanding B comes from MMIO

    assign rd_mmio = (region_of(m_araddr) == REGION_MMIO);
    assign wr_mmio = (region_of(m_awaddr) == REGION_MMIO);

    // read address
    assign mmio_araddr  = m_araddr;
    assign ext_araddr   = m_araddr;
    assign mmio_arvalid = m_arvalid &&  rd_mmio;
    assign ext_arvalid  = m_arvalid && !rd_mmio;
    assign m_arready    = rd_mmio ? mmio_arready : ext_arready;

    // read data
    assign m_rvalid     = rd_sel_q ? mmio_rvalid : ext_rvalid;
    assign m_rdata      = rd_sel_q ? mmio_rdata  : ext_rdata;
    assign m_rresp      = rd_sel_q ? mmio_rresp  : ext_rresp;
    assign mmio_rready  = m_rready;
    assign ext_rready   = m_rready;

    // write address / write data (W steered with the AW address, both are sent in the same cycle)
    assign mmio_awaddr  = m_awaddr;
    assign ext_awaddr   = m_awaddr;
    assign mmio_wdata   = m_wdata;
    assign ext_wdata    = m_wdata;
    assign mmio_wstrb   = m_wstrb;
    assign ext_wstrb    = m_wstrb;
    assign mmio_awvalid = m_awvalid &&  wr_mmio;
    assign ext_awvalid  = m_awvalid && !wr_mmio;
    assign mmio_wvalid  = m_wvalid  &&  wr_mmio;
    assign ext_wvalid   = m_wvalid  && !wr_mmio;
    assign m_awready    = wr_mmio ? mmio_awready : ext_awready;
    assign m_wready     = wr_mmio ? mmio_wready  : ext_wready;

    // write response
    assign m_bvalid     = wr_sel_q ? mmio_bvalid : ext_bvalid;
    assign m_bresp      = wr_sel_q ? mmio_bresp  : ext_bresp;
    assign mmio_bready  = m_bready;
    assign ext_bready   = m_bready;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rd_sel_q <= 1'b0;
            wr_sel_q <= 1'b0;
        end else begin
            if (m_arvalid && m_arready)                             rd_sel_q <= rd_mmio;
            if (m_awvalid && m_wvalid && m_awready && m_wready)     wr_sel_q <= wr_mmio;
        end
    end

endmodule