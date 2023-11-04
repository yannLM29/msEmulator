#include <iostream>
#include <memory>

#include "register-types.hpp"
#include "debug/debug-terminal.hpp"
#include "z80.hpp"
#include "ram.hpp"

int main()
{
    ms::Ram main_ram(20000, 0);
    ms::z80 f(main_ram);
    
    std::unique_ptr<ms::DebugStrategy> a(std::make_unique<ms::DebugTerminal>());
    
    f.AF.r16 = 9;
    a->showZ80Status(f);

    return 0;
}