#pragma once

#include "register-types.hpp"
#include "ram.hpp"

namespace ms
{

    
class z80
{

public:     // a changer
    Register2x8b AF, BC, DE, HL;
    Register2x8b AFp, BCp, DEp, HLp;

    Register16b IX, IY, SP;

    Register8b I, R;

    Register16b PC;

private:
    Ram &cpu_ram_;

public:
    z80(Ram &cpu_ram);
    // ~z80();

    void reset() noexcept;
};





}