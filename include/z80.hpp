#pragma once

#include <functional>
#include <memory>
#include <algorithm>

#include "register-types.hpp"
#include "ram.hpp"
#include "cartridge.hpp"

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
    
    std::vector<uint8_t>current_instruction_words;

    uint16_t to_read;
    uint16_t to_write;


    int cycles;


    struct Instruction
    {
        std::string instruction_name;
        uint8_t opcode_1st_byte;
        int opcode_length;
        void(z80::*from)(void) = nullptr;
        void(z80::*to)(void) = nullptr;
        void(z80::*instruction)(void) = nullptr;
        int cycles;

    };
    std::vector<Instruction> instruction_table;

private:
    Ram &cpu_ram_;
    // std::shared_ptr<Cartridge> cartridge_;
    Cartridge *cartridge_;

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
        to_read = (uint16_t)current_instruction_words.back();
    }
    void DataFromNN()
    {
        to_read = (uint16_t)current_instruction_words.back() << 8 | (uint16_t)current_instruction_words[current_instruction_words.size()-2];
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
        to_read = (uint16_t)cpu_ram_.read(IX + (uint16_t)current_instruction_words[2]);
    }
    void DataFromIY_daddr()
    {
        to_read = (uint16_t)cpu_ram_.read(IY + (uint16_t)current_instruction_words[2]);
    }
    void DataFromNNaddr()
    {
        to_read = (uint16_t)cpu_ram_.read(IY + ((uint16_t)current_instruction_words.back() << 8 | (uint16_t)current_instruction_words[current_instruction_words.size()-1]));
    }



    // -------- DataTo --------
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
        cpu_ram_.write(IX + (uint16_t)current_instruction_words[2], (uint8_t)to_write);
    }
    void DataToIY_daddr()
    {
        cpu_ram_.write(IY + (uint16_t)current_instruction_words[2], (uint8_t)to_write);
    }
    void DataToNNaddr()
    {
        cpu_ram_.write(IY + ((uint16_t)current_instruction_words.back() << 8 | (uint16_t)current_instruction_words[current_instruction_words.size()-1]), (uint8_t)to_write);
    }
    void DataToSPaddr()
    {
        cpu_ram_.write(SP, (uint8_t)to_write);
    }

    // ---------------- Opcodes analysers ----------------
    uint8_t get_b()
    {
        return (current_instruction_words.back() & 0x38) >> 3;
    }

    // ---------------- Instructions ----------------
    // -------- Load Groups --------
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

    // -------- Exchange, Transfert and Search Group
    // Les fonctions ci-dessous n'utilisent pas l'adressage car celui-ci n'est pas nécessaire ou pas adapté 
    void EX_DE_HL()
    {
        auto temp = HL;
        HL = DE;
        DE = temp;

    }
    void EX_AF_AFp()
    {
        auto temp = AF;
        AF = *((Register2x8b_with_flag*)&AFp);
        AFp = *((Register2x8b*)&temp);
    }
    void EXX_BC()
    {
        auto temp = BC;
        BC = BCp;
        BCp = temp;
    }
    void EXX_DE()
    {
        auto temp = DE;
        DE = DEp;
        DEp = temp;
    }
    void EXX_HL()
    {
        auto temp = HL;
        HL = HLp;
        HLp = temp;
    }
    void EX_SP_HL()
    {
        auto temp = HL;

        HL.r8.msb = cpu_ram_.read(SP+1);
        HL.r8.lsb = cpu_ram_.read(SP);

        cpu_ram_.write(SP+1, temp.r8.msb);
        cpu_ram_.write(SP, temp.r8.lsb);

    }
    void EX_SP_IX()
    {
        auto temp = IX;

        IX = (int16_t)(cpu_ram_.read(SP+1)) << 8 | (int16_t)(cpu_ram_.read(SP));
        
        cpu_ram_.write(SP+1, uint8_t(temp >> 8));
        cpu_ram_.write(SP, uint8_t(temp));

    }
    void EX_SP_IY()
    {
        auto temp = IY;

        IY = (int16_t)(cpu_ram_.read(SP+1)) << 8 | (int16_t)(cpu_ram_.read(SP));
        
        cpu_ram_.write(SP+1, uint8_t(temp >> 8));
        cpu_ram_.write(SP, uint8_t(temp));

    }
    void LDI()
    {
        cpu_ram_.write(DE.r16, cpu_ram_.read(HL.r16));
        DE.r16++;
        HL.r16++;
        BC.r16--;

        AF.r8.lsb.H = 0;
        AF.r8.lsb.PV = BC.r16 != 0 ? 1 : 0;
        AF.r8.lsb.N = 0;
    }
    void LDIR()
    {
        while (BC.r16 != 0)
        {
            LDI();
        }

        // cycles ??
        
    }
    void LDD()
    {
        cpu_ram_.write(DE.r16, cpu_ram_.read(HL.r16));
        DE.r16--;
        HL.r16--;
        BC.r16--;

        AF.r8.lsb.H = 0;
        AF.r8.lsb.PV = BC.r16 != 0 ? 1 : 0;
        AF.r8.lsb.N = 0;
    }
    void LDDR()
    {
        while (BC.r16 != 0)
        {
            LDD();
        }

        // cycles ??
        
    }
    void CPI()
    {
        int result = (int)AF.r8.msb - int(cpu_ram_.read(HL.r16));
        HL.r16++;
        BC.r16--;

        AF.r8.lsb.S = result < 0 ? 1 : 0;
        AF.r8.lsb.Z = result == 0 ? 1 : 0;
        // AF.r8.lsb.H ???
        AF.r8.lsb.PV = BC.r16 != 0 ? 1 : 0;
        AF.r8.lsb.N = 1; 

    }
    void CPIR()
    {

    }
    void CPD()
    {

    }
    void CPDR()
    {

    }




    // -------- Logic Groups --------
    void ADD_A()
    {
        uint16_t extended_result = (uint16_t)AF.r8.msb + to_read ;

        AF.r8.msb += uint8_t(to_read);

        AF.r8.lsb.S = AF.r8.msb & 0x80 ? 1 : 0;
        AF.r8.lsb.C = (int(AF.r8.msb) + int(to_read) > 0xFF) ? 1 : 0;
        // AF.r8.lsb.H = ???
        AF.r8.lsb.PV = extended_result > 0xFF ? 1 : 0;
        AF.r8.lsb.N = 0;
        AF.r8.lsb.C = extended_result & 0x0100;     // A vérifier
        

    }
    void ADC_A()
    {
        uint16_t extended_result = (uint16_t)AF.r8.msb + to_read + AF.r8.lsb.C ;

        AF.r8.msb += uint8_t(to_read) + AF.r8.lsb.C;

        AF.r8.lsb.S = AF.r8.msb & 0x80 ? 1 : 0;
        AF.r8.lsb.C = (int(AF.r8.msb) + int(to_read) > 0xFF) ? 1 : 0;
        // AF.r8.lsb.H = ???
        AF.r8.lsb.PV = extended_result > 0xFF ? 1 : 0;
        AF.r8.lsb.N = 0;
        AF.r8.lsb.C = extended_result & 0x0100;
    }
    void INC_8bit()
    {
        if(to_write == 0xFF)
        {
            to_read = 0;
            AF.r8.lsb.C = 1;
        }
        else
        {
            to_write = to_read + 1;
            AF.r8.lsb.C = 0;
        }
        
    }
    void INC_16bit()
    {
        if(to_write == 0xFFFF)
        {
            to_read = 0;
            AF.r8.lsb.C = 1;
        }
        else
        {
            to_write = to_read + 1;
            AF.r8.lsb.C = 0;
        }
    }
    void DEC()
    {
        if(to_write == 0x00)
        {
            to_read = 0xFFFF;       // cast vers uint8_t --> 0xFF ??
            AF.r8.lsb.N = 1;
        }
        else
        {
            to_write = to_read - 1;
            AF.r8.lsb.N = 0;
        }
        
    }
    // .....



    // -------- General-Purpose Arithmetic and CPU Control Groups --------
    void DAA()
    {

    }
    void CPL()
    {
        AF.r8.msb = ~AF.r8.msb;

        AF.r8.lsb.H = 1;
        AF.r8.lsb.N = 1;
    }
    void NEG()
    {
        // AF.r8.msb |= ~(AF.r8.msb & 0x80);

    }
    void CCF()
    {
        AF.r8.lsb.H = AF.r8.lsb.C;
        AF.r8.lsb.N = 0;
        AF.r8.lsb.C = ~AF.r8.lsb.C;
    }
    void SCF()
    {
        AF.r8.lsb.H = 0;
        AF.r8.lsb.N = 0;
        AF.r8.lsb.C = 1;
    }
    void NOP()
    {

    }
    void HALT()
    {
        
    }


    void fetchAndExecute()
    {
        current_instruction_words.clear();
        current_instruction_words.emplace_back(cartridge_->read(PC));
        
        std::cout << "PC = " << (int)PC << "\n";
        std::cout << "reading " << current_instruction_words[0] << "\n";
        
        // auto current_instruction_type = instruction_table[current_instruction_words[0]];
        // Solution temporaire a remplacer par la solution ci-dessus
        auto current_instruction_type = std::find_if(instruction_table.begin(), instruction_table.end(), [&](const auto &ins){
            return ins.opcode_1st_byte == current_instruction_words[0];
        });

        std::cout << "executing " << current_instruction_type->instruction_name << "\n";

        for(int i = PC+1; i < PC + current_instruction_type->opcode_length; i++)
        {
            current_instruction_words.emplace_back(cartridge_->read(i));
        }

        for(auto &e : current_instruction_words)
        {
            std::cout << std::hex << (int)e << " ";
        }
        std::cout << "\n";

        (this->*current_instruction_type->from)();
        (this->*current_instruction_type->instruction)();
        (this->*current_instruction_type->to)();

        PC += current_instruction_type->opcode_length;
        
        cycles+= current_instruction_type->cycles;

        
    }

    void executeCartridgeProgram()
    {
        PC = 0;
        do
        {
           fetchAndExecute();
        } while (PC < 2 || current_instruction_words[0] != 0);
        
        
    }

    void plugCartridge(Cartridge *cartridge)
    {
        cartridge_ = cartridge;
    }
};





}