#pragma once

#include <string>
#include <functional>
#include "register-types.hpp"

struct InstructionTable
{
    std::string instruction_name;
    int opcode_1st_byte;
    int opcode_length;
    std::function<void(void)> from;
    std::function<void(void)> to;
    std::function<void(void)> instruction;
    int cycles;

};
