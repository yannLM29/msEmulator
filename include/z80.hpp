#pragma once

#include "register-types.hpp"

namespace ms
{

    
class z80
{
    
private:
    ms::DoubleRegister AF, BC, DE, HL;
    ms::DoubleRegister AFp, BCp, DEp, HLp;

    ms::Register16b IX, IY, SP;

    ms::Register8b I, R;

    ms::Register16b PC;

public:
    z80(/* args */);
    ~z80();
};

z80::z80(/* args */)
{
}

z80::~z80()
{
}



}