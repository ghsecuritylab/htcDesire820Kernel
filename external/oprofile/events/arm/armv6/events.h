    {0x00, CTR(0) | CTR(1), 0, "IFU_IFETCH_MISS",
     "number of instruction fetch misses"},
    {0x01, CTR(0) | CTR(1), 0, "CYCLES_IFU_MEM_STALL",
     "cycles instruction fetch pipe is stalled"},
    {0x02, CTR(0) | CTR(1), 0, "CYCLES_DATA_STALL",
     "cycles stall occurs for due to data dependency"},
    {0x03, CTR(0) | CTR(1), 0, "ITLB_MISS",
     "number of Instruction MicroTLB misses"},
    {0x04, CTR(0) | CTR(1), 0, "DTLB_MISS",
     "number of Data MicroTLB misses"},
    {0x05, CTR(0) | CTR(1), 0, "BR_INST_EXECUTED",
     "branch instruction executed w/ or w/o program flow change"},
    {0x06, CTR(0) | CTR(1), 0, "BR_INST_MISS_PRED",
     "branch mispredicted"},
    {0x07, CTR(0) | CTR(1), 0, "INSN_EXECUTED",
     "instructions executed"},
    {0x09, CTR(0) | CTR(1), 0, "DCACHE_ACCESS",
     "data cache access, cacheable locations"},
    {0x0a, CTR(0) | CTR(1), 0, "DCACHE_ACCESS_ALL",
     "data cache access, all locations"},
    {0x0b, CTR(0) | CTR(1), 0, "DCACHE_MISS",
     "data cache miss"},
    {0x0c, CTR(0) | CTR(1), 0, "DCACHE_WB",
     "data cache writeback, 1 event for every half cacheline"},
    {0x0d, CTR(0) | CTR(1), 0, "PC_CHANGE",
     "number of times the program counter was changed without a mode switch"},
    {0x0f, CTR(0) | CTR(1), 0, "TLB_MISS",
     "Main TLB miss"},
    {0x10, CTR(0) | CTR(1), 0, "EXP_EXTERNAL",
     "Explict external data access"},
    {0x11, CTR(0) | CTR(1), 0, "LSU_STALL",
     "cycles stalled because Load Store request queque is full"},
    {0x12, CTR(0) | CTR(1), 0, "WRITE_DRAIN",
     "Times write buffer was drained"},
    {0x20, CTR(0) | CTR(1), 0, "ETMEXTOUT0",
     "nuber of cycles ETMEXTOUT[0] signal was asserted"},
    {0x21, CTR(0) | CTR(1), 0, "ETMEXTOUT1",
     "nuber of cycles ETMEXTOUT[1] signal was asserted"},
    {0x22, CTR(0) | CTR(1), 0, "ETMEXTOUT_BOTH",
     "nuber of cycles both ETMEXTOUT [0] and [1] were asserted * 2"},
    {0xff, CTR(0) | CTR(1) | CTR(2), 0, "CPU_CYCLES",
     "clock cycles counter"},