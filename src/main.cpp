#include <iostream>
#include "register-types.hpp"
#include "debug/debug-terminal.hpp"
#include "z80.hpp"
#include <memory>

int main()
{
    ms::Register2x8b AB;
    AB.r16 = 0x1101;
    // ms::DebugTerminal a{};
    ms::z80 f;
    
    std::unique_ptr<ms::DebugStrategy> a(std::make_unique<ms::DebugTerminal>());
    a->showZ80Status(f);
    std::cout << "msb:" << (unsigned int)(AB.r8.msb) << "\n";

    return 0;
}