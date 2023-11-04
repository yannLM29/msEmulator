#pragma once

#include <cstdint>

namespace ms
{

struct DoubleRegister
{
    uint16_t lsb : 8;
    uint16_t msb : 8;
    

};

union Register2x8b
{
    uint16_t r16;
    DoubleRegister r8;
};

using Register16b = uint16_t;
using Register8b = uint8_t;

struct StateRegister
{
    uint8_t C:1;
    uint8_t N:1;
    uint8_t PV:1;
    uint8_t U1:1;
    uint8_t H:1;
    uint8_t U2:1;
    uint8_t Z:1;
    uint8_t S:1;
};

}
