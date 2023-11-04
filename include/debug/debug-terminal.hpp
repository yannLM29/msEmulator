#pragma once

#include <iostream>
#include "debug/debug-strategy.hpp"

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
        std::cout << "debug on terminal\n";
    }

};


} // namespace ms

