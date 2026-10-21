package rv32i;

    localparam CPU_CLOCK_FREQ = 10_000_000;
    
    localparam DATA_WIDTH = 32;
    localparam ADDR_WIDTH = 5;

    typedef logic [rv32i::DATA_WIDTH-1:0] Instruction;
    typedef logic [rv32i::DATA_WIDTH-1:0] Word;
    typedef logic [7:0] Byte;
    typedef logic [ADDR_WIDTH-1:0] RegAddr;

    typedef logic [31:0] MetaCount;

    localparam Instruction NOP_INSTR = 32'h00000013;  // canonical NOP (addi x0, x0, 0), the only encoding used for bubbles/clears anywhere in the CPU

    typedef logic [1:0] Resp;                       // AXI4-Lite RRESP / BRESP (bit 1 set = error)
    localparam Resp RESP_OKAY   = 2'b00;            // access completed
    localparam Resp RESP_SLVERR = 2'b10;            // slave exists but refused the access (write to ROM, read-only MMIO register, unmapped MMIO register)
    localparam Resp RESP_DECERR = 2'b11;            // nothing mapped at this address (default slave)

    localparam BITS_FIT = $clog2(DATA_WIDTH>>3) + 1;    // 3
    typedef enum logic [BITS_FIT - 1:0] {  // to be shared between LSU and mem module
        ZERO = 'd0,
        ONE  = 'd1,
        TWO  = 'd2,
        FOUR = 'd4
    } ReqBytes;

    typedef enum logic [6:0] {  //7 bits for opcode
        OP_R        = 7'b0110011,
        OP_I        = 7'b0010011,
        OP_I_L      = 7'b0000011,
        OP_S        = 7'b0100011,
        OP_B        = 7'b1100011,
        OP_J        = 7'b1101111,
        OP_I_J      = 7'b1100111,
        OP_LUI      = 7'b0110111,
        OP_AUIPC    = 7'b0010111,
        OP_I_E      = 7'b1110011,
        OP_FENCE    = 7'b0001111
    } OpCode;

    typedef enum logic [3:0] { 
        ADD  = 4'b0000,
        SUB  = 4'b0001,
        XOR  = 4'b0100,
        OR   = 4'b0101,
        AND  = 4'b0110,
        SLL  = 4'b1000,
        SRL  = 4'b1010,
        SRA  = 4'b1011,
        SLT  = 4'b1101,
        SLTU = 4'b1100
    } AluOp;

    typedef enum logic [2:0] { 
        I, S, B, U, J, N // default
    } ImmPackFmt;

    // memory spec
    localparam ROM_SIZE_BYTES  = 8192;
    localparam RAM_SIZE_BYTES  = 131072;
    localparam Word MMIO_OFFSET     = 32'h8000_0000; // (0x80000000)  // sized hex literal, the unsized decimal 2147483648 overflowed a 32-bit signed integer
    localparam Word MMIO_SIZE_BYTES = 32'h8000_0000;

    // memory map, the one place every master, decoder and slave takes its bounds from (keep in sync with linker.ld)
    localparam Word ROM_BASE     = 32'h0000_0000;                        // BIOS ROM
    localparam Word RAM_BASE     = ROM_BASE + ROM_SIZE_BYTES;            // RAM starts right after the ROM (0x00002000)
    localparam Word RAM_END      = RAM_BASE + RAM_SIZE_BYTES;            // first byte after the RAM (0x00022000)
    localparam Word RESET_VECTOR = ROM_BASE;                             // first instruction fetched after reset

    typedef enum logic [1:0] {      // which slave owns an address
        REGION_NONE,                // unmapped (0x00022000 - 0x7FFFFFFF)
        REGION_ROM,
        REGION_RAM,
        REGION_MMIO                 // 0x80000000 and above (bit 31 set)
    } Region;

    function automatic Region region_of(input Word addr);   // shared address decode
        if (addr[31])               return REGION_MMIO;
        else if (addr < RAM_BASE)   return REGION_ROM;
        else if (addr < RAM_END)    return REGION_RAM;
        else                        return REGION_NONE;
    endfunction

endpackage