#pragma once

#include <functional>
#include "register-types.hpp"
#include "ram.hpp"
#include "instruction-table.hpp"

namespace ms
{

class z80
{

public:     // a changer
    Register2x8b BC, DE, HL;
    Register2x8b_with_flag AF;
    Register2x8b AFp, BCp, DEp, HLp;

    Register16b IX, IY, SP;

    Register8b I, R;

    Register16b PC;
    
    std::vector<uint8_t>current_opcode;
    uint16_t to_read;
    uint16_t to_write;


    struct Instruction
    {
        std::string instruction_name;
        int opcode_1st_byte;
        int opcode_length;
        void(z80::*from)(void) = nullptr;
        void(z80::*to)(void) = nullptr;
        void(z80::*instruction)(void) = nullptr;
        int cycles;

    };
    std::vector<Instruction> instruction_table;

private:
    Ram &cpu_ram_;

public:
    z80(Ram &cpu_ram);
    // ~z80();

    void reset() noexcept;

    void fetch()
    {
        
    }

    // ---------------- Addressing ----------------
    // -------- DataFrom --------
    // ---- Registers ----
    // -- 8 bits --
    void DataFromRegA()
    {
        to_read = (uint16_t)AF.r8.msb;
    }
    void DataFromRegB()
    {
        to_read = (uint16_t)BC.r8.msb;
    }
    void DataFromRegC()
    {
        to_read = (uint16_t)BC.r8.lsb;
    }
    void DataFromRegD()
    {
        to_read = (uint16_t)DE.r8.msb;
    }
    void DataFromRegE()
    {
        to_read = (uint16_t)DE.r8.lsb;
    }
    void DataFromRegH()
    {
        to_read = (uint16_t)HL.r8.msb;
    }
    void DataFromRegL()
    {
        to_read = (uint16_t)HL.r8.lsb;
    }
    void DataFromRegI()
    {
        to_read = (uint16_t)I;
    }
    void DataFromRegR()
    {
        to_read = (uint16_t)R;
    }

    // -- 16 bits --
    void DataFromRegAF()
    {
        to_read = AF.r16;
    }
    void DataFromRegBC()
    {
        to_read = BC.r16;
    }
    void DataFromRegDE()
    {
        to_read = DE.r16;
    }
    void DataFromRegHL()
    {
        to_read = HL.r16;
    }
    void DataFromRegIX()
    {
        to_read = IX;
    }
    void DataFromRegIY()
    {
        to_read = IY;
    }
    void DataFromRegAFp()
    {
        to_read = AFp.r16;
    }
    void DataFromRegBCp()
    {
        to_read = BCp.r16;
    }
    void DataFromRegDEp()
    {
        to_read = DEp.r16;
    }
    void DataFromRegHLp()
    {
        to_read = HLp.r16;
    }
    

    // ---- Direct ----
    void DataFromN()
    {
        to_read = (uint16_t)current_opcode.back();
    }
    void DataFromNN()
    {
        to_read = (uint16_t)current_opcode.back() << 8 | (uint16_t)current_opcode[current_opcode.size()-1];
    }

    // ---- Adresses ----
    void DataFromHLaddr()
    {
        to_read = (uint16_t)cpu_ram_.read(HL.r16);
    }
    void DataFromBCaddr()
    {
        to_read = (uint16_t)cpu_ram_.read(BC.r16);
    }
    void DataFromDEaddr()
    {
        to_read = (uint16_t)cpu_ram_.read(DE.r16);
    }
    void DataFromIX_daddr()
    {
        to_read = (uint16_t)cpu_ram_.read(IX + (uint16_t)current_opcode[2]);
    }
    void DataFromIY_daddr()
    {
        to_read = (uint16_t)cpu_ram_.read(IY + (uint16_t)current_opcode[2]);
    }
    void DataFromNNaddr()
    {
        to_read = (uint16_t)cpu_ram_.read(IY + ((uint16_t)current_opcode.back() << 8 | (uint16_t)current_opcode[current_opcode.size()-1]));
    }



    // ---------------- DataTo ----------------
    // ---- Registers ----
    // -- 8 bits --
    void DataToRegA()
    {
        AF.r8.msb = uint8_t(to_write);
    }
    void DataToRegB()
    {
        BC.r8.msb = uint8_t(to_write);
    }
    void DataToRegC()
    {
        BC.r8.lsb = uint8_t(to_write);
    }
    void DataToRegD()
    {
        DE.r8.msb = uint8_t(to_write);
    }
    void DataToRegE()
    {
        DE.r8.lsb = uint8_t(to_write);
    }
    void DataToRegH()
    {
        HL.r8.msb = uint8_t(to_write);
    }
    void DataToRegL()
    {
        HL.r8.lsb = uint8_t(to_write);
    }
    
    // -- 16 bits --
    void DataToRegAF()
    {
        AF.r16 = to_write;
    }
    void DataToRegBC()
    {
        BC.r16 = to_write;
    }
    void DataToRegDE()
    {
        DE.r16 = to_write;
    }
    void DataToRegHL()
    {
        HL.r16 = to_write;
    }
    void DataToRegAFp()
    {
        AFp.r16 = to_write;
    }
    void DataToRegBCp()
    {
        BCp.r16 = to_write;
    }
    void DataToRegDEp()
    {
        DEp.r16 = to_write;
    }
    void DataToRegHLp()
    {
        HLp.r16 = to_write;
    }
    void DataToRegIX()
    {
        IX = to_write;
    }
    void DataToRegIY()
    {
        IY = to_write;
    }
    void DataToRegSP()
    {
        SP = to_write;
    }
    

    // ---- Addresses ----
    void DataToHLaddr()
    {
        cpu_ram_.write(HL.r16, (uint8_t)to_write);
    }
    void DataToBCaddr()
    {
        cpu_ram_.write(BC.r16, (uint8_t)to_write);
    }
    void DataToDEaddr()
    {
        cpu_ram_.write(DE.r16, (uint8_t)to_write);
    }
    void DataToIX_daddr()
    {
        cpu_ram_.write(IX + (uint16_t)current_opcode[2], (uint8_t)to_write);
    }
    void DataToIY_daddr()
    {
        cpu_ram_.write(IY + (uint16_t)current_opcode[2], (uint8_t)to_write);
    }
    void DataToNNaddr()
    {
        cpu_ram_.write(IY + ((uint16_t)current_opcode.back() << 8 | (uint16_t)current_opcode[current_opcode.size()-1]), (uint8_t)to_write);
    }
    void DataToSPaddr()
    {
        cpu_ram_.write(SP, (uint8_t)to_write);
    }

    // ---------------- Instructions ----------------
    void LD()
    {
        to_write = to_read;
    }
    void PUSH()
    {
        SP--;
        cpu_ram_.write(SP, (uint8_t)(to_read >> 8));
        SP--;
        cpu_ram_.write(SP, (uint8_t)to_read);
    }
    void POP()
    {
        to_write = (uint16_t)cpu_ram_.read(SP);
        SP++;
        to_write |= (uint16_t)cpu_ram_.read(SP) << 8;
        SP++;
    }
    void EXX()
    {
        
    }
    void ADD_A()
    {
        AF.r8.msb += uint8_t(to_read);
        // if()
        // {
        //     AF.r8.lsb.C = 1
        // }
    }
    void ADC_A()
    {
        AF.r8.msb += uint8_t(to_read) + AF.r8.lsb.C;
    }

    // void readRomFile(std::string path)
    // {

    //     auto current_instruction = instruction_table[read(PC)]
    //     this.opcode = copy(PC, PC + current_instruction.length);

    //     current_insctruction.from();
    //     current_insctruction.instruction();
    //     current_insctruction.to();

    //     PC+=current_insctruction.length
    //     cycles+= current_insctruction.cycles
    // }
};





}