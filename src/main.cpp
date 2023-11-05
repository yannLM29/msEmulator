#include <iostream>
#include <memory>

#include "register-types.hpp"
#include "debug/debug-terminal.hpp"
#include "z80.hpp"
#include "ram.hpp"
#include "cartridge.hpp"

int main()
{
    ms::Ram main_ram(64, 0);
    ms::z80 f(main_ram);
    ms::Cartridge c("./hello(3).bin");
    // auto cartridge = std::make_shared<ms::Cartridge>("./rom1.ms");
    f.plugCartridge(&c);
    
    std::unique_ptr<ms::DebugStrategy> a(std::make_unique<ms::DebugTerminal>());

    a->showZ80Status(f);
    std::cout << "\nROM: ";
    a->showCartridgeData(c, 0, 64);

    f.executeCartridgeProgram();

    a->showZ80Status(f);

    a->showRAMData(main_ram, 0, 63);

    return 0;
}