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
        int(z80::*instruction)(void) = nullptr;
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
    void DataFromI()
    {
        to_read = (uint16_t)I;
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
    void DataToSPaddr() // useless 
    {
        cpu_ram_.write(SP, (uint8_t)to_write);
    }

    // ---------------- Opcodes analysers ----------------
    uint8_t get_b()
    {
        return (current_instruction_words.back() & 0x38) >> 3;
    }

    // ---------------- Instructions ----------------
    // -------- Empty --------
    void no_data()
    {

    }
    int TO_IMPLEMENT()
    {
        std::cout << "need implement\n";
    }
    int no()
    {

    }
    
    // -------- Redirect to other tables --------
    int TABLE_CB()
    {
        std::cout << "call to bit func\n";
    }
    int TABLE_IX()
    {
        std::cout << "call to IX func\n";
    }
    int TABLE_IY()
    {
        std::cout << "call to IY func\n";
    }
    int TABLE_Misc()
    {
        std::cout << "call to misc func\n";
    }


    // -------- Load Groups --------
    int LD()
    {
        to_write = to_read;
        return 0;
    }
    int PUSH()
    {
        SP--;
        cpu_ram_.write(SP, (uint8_t)(to_read >> 8));
        SP--;
        cpu_ram_.write(SP, (uint8_t)to_read);

        return 0;
    }
    int POP()
    {
        to_write = (uint16_t)cpu_ram_.read(SP);
        SP++;
        to_write |= (uint16_t)cpu_ram_.read(SP) << 8;
        SP++;
    
        return 0;
    }

    // -------- Exchange, Transfert and Search Group
    // Les fonctions ci-dessous n'utilisent pas l'adressage car celui-ci n'est pas nécessaire ou pas adapté 
    int EX_DE_HL()
    {
        auto temp = HL;
        HL = DE;
        DE = temp;

        return 0;

    }
    int EX_AF_AFp()
    {
        auto temp = AF;
        AF = *((Register2x8b_with_flag*)&AFp);
        AFp = *((Register2x8b*)&temp);

        return 0;
    }
    int EXX()
    {
        auto temp = BC;
        BC = BCp;
        BCp = temp;

        temp = DE;
        DE = DEp;
        DEp = temp;

        temp = HL;
        HL = HLp;
        HLp = temp;

        return 0;
    }
    int EX_SP_HL()
    {
        auto temp = HL;

        HL.r8.msb = cpu_ram_.read(SP+1);
        HL.r8.lsb = cpu_ram_.read(SP);

        cpu_ram_.write(SP+1, temp.r8.msb);
        cpu_ram_.write(SP, temp.r8.lsb);

        return 0;

    }
    int EX_SP_IX()
    {
        auto temp = IX;

        IX = (int16_t)(cpu_ram_.read(SP+1)) << 8 | (int16_t)(cpu_ram_.read(SP));
        
        cpu_ram_.write(SP+1, uint8_t(temp >> 8));
        cpu_ram_.write(SP, uint8_t(temp));

        return 0;

    }
    int EX_SP_IY()
    {
        auto temp = IY;

        IY = (int16_t)(cpu_ram_.read(SP+1)) << 8 | (int16_t)(cpu_ram_.read(SP));
        
        cpu_ram_.write(SP+1, uint8_t(temp >> 8));
        cpu_ram_.write(SP, uint8_t(temp));

        return 0;

    }
    int LDI()
    {
        cpu_ram_.write(DE.r16, cpu_ram_.read(HL.r16));
        DE.r16++;
        HL.r16++;
        BC.r16--;

        AF.r8.lsb.H = 0;
        AF.r8.lsb.PV = BC.r16 != 0 ? 1 : 0;
        AF.r8.lsb.N = 0;

        return 0;
    }
    int LDIR()
    {
        int cycles = BC.r16 == 0 ? 4 : 0;

        while (BC.r16 != 0)
        {
            LDI();
            cycles += 5;
        }

        return cycles;
        
    }
    int LDD()
    {
        cpu_ram_.write(DE.r16, cpu_ram_.read(HL.r16));
        DE.r16--;
        HL.r16--;
        BC.r16--;

        AF.r8.lsb.H = 0;
        AF.r8.lsb.PV = BC.r16 != 0 ? 1 : 0;
        AF.r8.lsb.N = 0;

        return 0;
    }
    int LDDR()
    {
        int cycles = BC.r16 == 0 ? 4 : 0;

        while (BC.r16 != 0)
        {
            LDD();
            cycles += 5;
        }

        return cycles;
        
    }
    int CPI()
    {
        int result = (int)AF.r8.msb - int(cpu_ram_.read(HL.r16));
        HL.r16++;
        BC.r16--;

        AF.r8.lsb.S = result < 0 ? 1 : 0;
        AF.r8.lsb.Z = result == 0 ? 1 : 0;
        AF.r8.lsb.H = AF.r8.msb & 0x0F < cpu_ram_.read(HL.r16) & 0x0F ? 1 : 0;          // a verifer
        AF.r8.lsb.PV = BC.r16 != 0 ? 1 : 0;
        AF.r8.lsb.N = 1; 

        return 0;
    }
    int CPIR()
    {
        int cycles = BC.r16 == 0 ? 4 : 0;

        while (BC.r16 != 0)
        {
            CPI();
            cycles += 5;
        }
    
        return cycles;
    }
    int CPD()
    {
        int result = (int)AF.r8.msb - int(cpu_ram_.read(HL.r16));
        HL.r16--;
        BC.r16--;

        AF.r8.lsb.S = result < 0 ? 1 : 0;
        AF.r8.lsb.Z = result == 0 ? 1 : 0;
        AF.r8.lsb.H = AF.r8.msb & 0x0F < cpu_ram_.read(HL.r16) & 0x0F ? 1 : 0;          //a verifier
        AF.r8.lsb.PV = BC.r16 != 0 ? 1 : 0;
        AF.r8.lsb.N = 1; 

        return 0;
    }
    int CPDR()
    {
        int cycles = BC.r16 == 0 ? 4 : 0;

        while (BC.r16 != 0)
        {
            CPD();
            cycles += 5;
        }
    
        return cycles;
    }




    // -------- Logic Groups --------
    int ADD()
    {
        uint16_t extended_result = (uint16_t)AF.r8.msb + to_read ;

        AF.r8.msb += (uint8_t)to_read;       

        AF.r8.lsb.S = AF.r8.msb & 0x80 ? 1 : 0;
        AF.r8.lsb.Z = AF.r8.msb == 0 ? 1 : 0;
        AF.r8.lsb.C = (int(AF.r8.msb) + int(to_read) > 0xFF) ? 1 : 0;
        // AF.r8.lsb.H = ???
        AF.r8.lsb.PV = extended_result > 0xFF ? 1 : 0;
        AF.r8.lsb.N = 0;
        AF.r8.lsb.C = extended_result & 0x0100;     // A vérifier
        
        return 0;
    }
    int ADC()
    {
        uint16_t extended_result = (uint16_t)AF.r8.msb + to_read + AF.r8.lsb.C ;

        AF.r8.msb += uint8_t(to_read) + AF.r8.lsb.C;

        AF.r8.lsb.S = AF.r8.msb & 0x80 ? 1 : 0;
        AF.r8.lsb.Z = AF.r8.msb == 0 ? 1 : 0;
        AF.r8.lsb.C = (int(AF.r8.msb) + int(to_read) > 0xFF) ? 1 : 0;
        // AF.r8.lsb.H = ???
        AF.r8.lsb.PV = extended_result > 0xFF ? 1 : 0;
        AF.r8.lsb.N = 0;
        AF.r8.lsb.C = extended_result & 0x0100;

        return 0;
    }
    int SUB()
    {
        uint16_t extended_result = (uint16_t)AF.r8.msb - to_read ;

        AF.r8.msb -= (uint8_t)to_read; 

        AF.r8.lsb.S = AF.r8.msb & 0x80 ? 1 : 0;
        AF.r8.lsb.Z = AF.r8.msb == 0 ? 1 : 0;
        AF.r8.lsb.C = (int(AF.r8.msb) + int(to_read) > 0xFF) ? 1 : 0;           // 2x C ???
        // AF.r8.lsb.H = ???
        AF.r8.lsb.PV = extended_result > 0xFF ? 1 : 0;
        AF.r8.lsb.N = 0;
        AF.r8.lsb.C = extended_result & 0x0100;     // A vérifier

        return 0;
    }
    int SBC()
    {

        return 0;
    }   
    int AND()
    {

        return 0;
    }
    int OR()
    {
        uint16_t extended_result = AF.r8.msb | (uint8_t)to_read;        
        AF.r8.msb |= (uint8_t)to_read;

        AF.r8.lsb.S = AF.r8.msb & 0x80 ? 1 : 0;
        AF.r8.lsb.Z = AF.r8.msb == 0 ? 1 : 0;
        AF.r8.lsb.H = 0;
        AF.r8.lsb.PV = extended_result > 0xFF ? 1 : 0;
        AF.r8.lsb.N = 0;
        AF.r8.lsb.C = 0;

        return 0;
    }
    int XOR()
    {
        AF.r8.msb ^= (uint8_t)to_read;

        AF.r8.lsb.S = AF.r8.msb & 0x80 ? 1 : 0;
        AF.r8.lsb.Z = AF.r8.msb == 0 ? 1 : 0;
        AF.r8.lsb.H = 0;
        AF.r8.lsb.PV = !(AF.r8.msb % 2);
        AF.r8.lsb.N = 0;
        AF.r8.lsb.C = 0;

        return 0;
    }
    int CP()
    {

        return 0;
    }


    int INC_8bit()
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
        
        return 0;
    }
    int INC_16bit()
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

        return 0;
    }
    int DEC()
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

        return 0;
        
    }
    // .....



    // -------- General-Purpose Arithmetic and CPU Control Groups --------
    int DAA()
    {

        return 0;
    }
    int CPL()
    {
        AF.r8.msb = ~AF.r8.msb;

        AF.r8.lsb.H = 1;
        AF.r8.lsb.N = 1;

        return 0;
    }
    int NEG()
    {
        // AF.r8.msb |= ~(AF.r8.msb & 0x80);

        return 0;
    }
    int CCF()
    {
        AF.r8.lsb.H = AF.r8.lsb.C;
        AF.r8.lsb.N = 0;
        AF.r8.lsb.C = ~AF.r8.lsb.C;

        return 0;
    }
    int SCF()
    {
        AF.r8.lsb.H = 0;
        AF.r8.lsb.N = 0;
        AF.r8.lsb.C = 1;

        return 0;
    }
    int NOP()
    {
        return 0;
    }
    int HALT()
    {
        return 0;
    }



    // -------- Rotate and shift Groups --------





    int fetchAndExecute()
    {
        int instruction_cycles = 0;

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
        instruction_cycles = (this->*current_instruction_type->instruction)();
        (this->*current_instruction_type->to)();

        PC += current_instruction_type->opcode_length;
        
        instruction_cycles += current_instruction_type->cycles;

        return instruction_cycles;        
    }

    void executeCartridgeProgram()
    {
        PC = 0;
        int instruction_cycles = 0;

        do
        {
            if(instruction_cycles == 0)
            {
                instruction_cycles = fetchAndExecute() - 1;
            }
            else
            {
                instruction_cycles--;
            }

        } while (PC < 20 && current_instruction_words[0] != 0);

    }

    void plugCartridge(Cartridge *cartridge)
    {
        cartridge_ = cartridge;
    }
};





}