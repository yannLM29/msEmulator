#pragma once

#include "z80.hpp"
#include "ram.hpp"

namespace ms
{

class DebugStrategy
{

public:
    virtual void showZ80Status(const z80 &processor) = 0;
    virtual void showRAMData(const Ram &ram, uint16_t from, uint16_t to) = 0;
    virtual void showCartridgeData(const Cartridge &cartridge, uint16_t from, uint16_t to) = 0;
    virtual void showCurrentInstruction(const z80 &processor) = 0;
};


}
