#pragma once

#include "z80.hpp"

namespace ms
{

class DebugStrategy
{

public:
    virtual void showZ80Status(const z80 &processor) = 0;
};


}
