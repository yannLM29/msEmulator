#pragma once

#include "register-types.hpp"
#include "ram.hpp"

namespace ms
{

    
class z80
{

public:     // a changer
    Register2x8b BC, DE, HL, AF;
    Register2x8b AFp, BCp, DEp, HLp;

    Register16b IX, IY, SP;

    Register8b I, R;

    Register16b PC;
    
    uint16_t to_read;
    uint16_t to_write;

private:
    Ram &cpu_ram_;

public:
    z80(Ram &cpu_ram);
    // ~z80();

    void reset() noexcept;


    // -------- DataFrom --------
    // ---- Registers ----
    void DataFromR_A(std::vector<uint8_t>opcode)
    {
        to_read = (uint16_t)AF.r8.msb;
    }
    void DataFromR_B()
    {
        to_read = (uint16_t)BC.r8.msb;
    }
    void DataFromR_C()
    {
        to_read = (uint16_t)BC.r8.lsb;
    }
    void DataFromR_D()
    {
        to_read = (uint16_t)DE.r8.msb;
    }
    void DataFromR_E()
    {
        to_read = (uint16_t)DE.r8.lsb;
    }
    void DataFromR_H()
    {
        to_read = (uint16_t)HL.r8.msb;
    }
    void DataFromR_L()
    {
        to_read = (uint16_t)HL.r8.lsb;
    }

    // ---- Adresses ----
    void DataFromHLaddr()
    {
        to_read = (uint16_t)cpu_ram_.read(HL.r16);
    }


    // ---------------- DataTo ----------------
    // ---- Registers ----
    void DataToR_A()
    {
        AF.r8.msb = uint8_t(to_write);
    }

    void DataToR_B()
    {
        BC.r8.msb = uint8_t(to_write);
    }
    void DataToR_C()
    {
        BC.r8.lsb = uint8_t(to_write);
    }

    void DataToR_D()
    {
        DE.r8.msb = uint8_t(to_write);
    }
    void DataToR_E()
    {
        DE.r8.lsb = uint8_t(to_write);
    }

    void DataToR_H()
    {
        HL.r8.msb = uint8_t(to_write);
    }
    void DataToR_L()
    {
        HL.r8.lsb = uint8_t(to_write);
    }
    
    void LD()
    {
        to_write = to_read;

    }
};

template<typename reg_type>
void LD(reg_type from, reg_type &to)
{
    to = from;
}




}