#include "z80.hpp"

namespace ms
{

z80::z80(Ram &cpu_ram) : cpu_ram_(cpu_ram)
{
    instruction_table = {
        {"NOP", 0x00, 1, &z80::no_data, &z80::no_data, &z80::NOP, 4},
        {"LD BC,NN", 0x01, 3, &z80::DataFromNN, &z80::DataToRegBC, &z80::LD, 10},
        {"LD (BC),A", 0x02, 1, &z80::DataFromRegA, &z80::DataToBCaddr, &z80::LD, 7},
        {"LD B,N", 0x06, 2, &z80::DataFromN, &z80::DataToRegB, &z80::LD, 7},
        {"LD A,(BC)", 0x0A, 1, &z80::DataFromBCaddr, &z80::DataToRegA, &z80::LD, 7},
        {"LD C,N", 0x0E, 2, &z80::DataFromN, &z80::DataToRegC, &z80::LD, 7},

        {"LD DE,NN", 0x11, 3, &z80::DataFromNN, &z80::DataToRegDE, &z80::LD, 10},
        {"LD (DE),A", 0x12, 1, &z80::DataFromRegA, &z80::DataToDEaddr, &z80::LD, 7},
        {"LD D,N", 0x16, 2, &z80::DataFromN, &z80::DataToRegD, &z80::LD, 7},
        {"LD A,(DE)", 0x1A, 1, &z80::DataFromDEaddr, &z80::DataToRegA, &z80::LD, 7},
        {"LD E,N", 0x1E, 2, &z80::DataFromN, &z80::DataToRegE, &z80::LD, 7},

        {"LD HL,NN", 0x21, 3, &z80::DataFromNN, &z80::DataToRegHL, &z80::LD, 10},
        {"LD (HL),A", 0x22, 1, &z80::DataFromRegA, &z80::DataToHLaddr, &z80::LD, 7},
        {"LD H,N", 0x26, 2, &z80::DataFromN, &z80::DataToRegH, &z80::LD, 7},
        {"LD A,(HL)", 0x2A, 1, &z80::DataFromHLaddr, &z80::DataToRegA, &z80::LD, 7},
        {"LD L,N", 0x2E, 2, &z80::DataFromN, &z80::DataToRegL, &z80::LD, 7},
        
        {"LD HL,NN", 0x21, 3, &z80::DataFromNN, &z80::DataToRegHL, &z80::LD, 6},

        {"LD A,N", 0x3E, 2, &z80::DataFromN, &z80::DataToRegA, &z80::LD, 2},

        {"LD C,(HL)", 0x4E, 1, &z80::DataFromHLaddr, &z80::DataToRegC, &z80::LD, 7},
    };
    reset();
}

void z80::reset() noexcept
{
    PC = 0;
    I = 0;
    R = 0;
    cycles = 0;
}

} // namespace ms
