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

    a->showZ80Status(f);

    f.current_opcode.clear();
    f.current_opcode.emplace_back(0b00111110);
    f.current_opcode.emplace_back(0x05);
    f.DataFromN();
    f.LD();
    f.DataToRegA();

    a->showZ80Status(f);

    f.DataFromRegA();
    f.LD();
    f.DataToRegB();

    a->showZ80Status(f);

    f.IX = 0;
    f.current_opcode.clear();
    f.current_opcode.emplace_back(0b00111110);
    f.current_opcode.emplace_back(0x00);
    f.current_opcode.emplace_back(0x05);

    f.DataFromRegB();
    f.LD();
    f.DataToIX_daddr();

    a->showRAMData(main_ram, 0, 2000);

    return 0;
}