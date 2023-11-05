#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

namespace ms
{
    
class Cartridge
{
private:
    std::vector<uint8_t> data_;
    int mapper_type;


public:
    Cartridge(std::string rom_path)
    {
        std::ifstream rom_file_stream;
        rom_file_stream.open(rom_path, std::ifstream::binary);
        if(!rom_file_stream.is_open())
        {
            throw std::runtime_error("ms error: Can't open rom file");
        }
        
        char tempBuffer;
        
        while (rom_file_stream.read(&tempBuffer, 1)) {
            data_.emplace_back(tempBuffer);
        }


        data_.resize(64);

    }

    uint8_t read(uint16_t addr) const
    {
        
        if(addr >= data_.size())
        {
            throw std::runtime_error("ms error: In cartridge reading, wrong address");
        }

        return data_[addr];

    
    }
    // void write(uint16_t addr, uint8_t new_data);
};


} // namespace ms
