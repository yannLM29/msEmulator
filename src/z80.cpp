#include "z80.hpp"

namespace ms
{

z80::z80(Ram &cpu_ram) : cpu_ram_(cpu_ram)
{
    instruction_table = {
        {"NOP", 0x00, 1, nullptr, nullptr, nullptr, 4},
        {"LD BC,NN", 0x01, 3, &z80::DataFromNN, &z80::DataToRegBC, &z80::LD, 2},
        {"LD BC,A", 0x02, 1, &z80::DataFromRegA, &z80::DataToBCaddr, &z80::LD, 2},
        {"LD A,N", 0x3E, 2, &z80::DataFromRegA, &z80::DataToBCaddr, &z80::LD, 2},
    };
    reset();
}

void z80::reset() noexcept
{
    PC = 0;
    I = 0;
    R = 0;
}

} // namespace ms
