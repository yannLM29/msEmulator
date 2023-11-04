#pragma once

#include <iostream>
#include "debug/debug-strategy.hpp"
#include "z80.hpp"

namespace ms
{


class DebugTerminal : public DebugStrategy
{
private:
    /* data */
public:
    DebugTerminal()
    {

    }

    void showZ80Status(const z80 &processor)
    {
        std::cout << "z80 on terminal:\n";
        std::cout << "  AF: 0x" << std::hex << (uint16_t)processor.AF.r16 << " --> A: 0x" << std::hex << (uint16_t)processor.AF.r8.msb << "  F: 0x" << std::hex << (uint16_t)processor.AF.r8.lsb << "\n";
        std::cout << "  BC: 0x" << std::hex << (uint16_t)processor.BC.r16 << " --> B: 0x" << std::hex << (uint16_t)processor.BC.r8.msb << "  C: 0x" << std::hex << (uint16_t)processor.BC.r8.lsb << "\n";
        std::cout << "  DE: 0x" << std::hex << (uint16_t)processor.DE.r16 << " --> D: 0x" << std::hex << (uint16_t)processor.DE.r8.msb << "  E: 0x" << std::hex << (uint16_t)processor.DE.r8.lsb << "\n";
        std::cout << "  HL: 0x" << std::hex << (uint16_t)processor.HL.r16 << " --> H: 0x" << std::hex << (uint16_t)processor.HL.r8.msb << "  L: 0x" << std::hex << (uint16_t)processor.HL.r8.lsb << "\n\n";
  
        std::cout << "  AFp: 0x" << std::hex << (uint16_t)processor.AFp.r16 << " --> Ap: 0x" << std::hex << (uint16_t)processor.AFp.r8.msb << "  Fp: 0x" << std::hex << (uint16_t)processor.AFp.r8.lsb << "\n";
        std::cout << "  BCp: 0x" << std::hex << (uint16_t)processor.BCp.r16 << " --> Bp: 0x" << std::hex << (uint16_t)processor.BCp.r8.msb << "  Cp: 0x" << std::hex << (uint16_t)processor.BCp.r8.lsb << "\n";
        std::cout << "  DEp: 0x" << std::hex << (uint16_t)processor.DEp.r16 << " --> Dp: 0x" << std::hex << (uint16_t)processor.DEp.r8.msb << "  Ep: 0x" << std::hex << (uint16_t)processor.DEp.r8.lsb << "\n";
        std::cout << "  HLp: 0x" << std::hex << (uint16_t)processor.HLp.r16 << " --> Hp: 0x" << std::hex << (uint16_t)processor.HLp.r8.msb << "  Lp: 0x" << std::hex << (uint16_t)processor.HLp.r8.lsb << "\n\n";

        std::cout << "  IX: 0x" << std::hex << (uint16_t)processor.IX << "\n";
        std::cout << "  IY: 0x" << std::hex << (uint16_t)processor.IY << "\n";
        std::cout << "  SP: 0x" << std::hex << (uint16_t)processor.SP << "\n\n";
          
        std::cout << "  I: 0x" << std::hex << (unsigned int)processor.I << "\n";
        std::cout << "  R: 0x" << std::hex << (unsigned int)processor.R << "\n\n";
  
        std::cout << "  PC: 0x" << std::hex << (uint16_t)processor.PC << "\n";
    }

};


} // namespace ms

