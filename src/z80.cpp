#include "z80.hpp"

namespace ms
{
    
z80::z80(Ram &cpu_ram) : cpu_ram_(cpu_ram)
{
    reset();
}

void z80::reset() noexcept
{
    PC = 0;
    I = 0;
    R = 0;
}

} // namespace ms
