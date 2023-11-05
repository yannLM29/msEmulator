#pragma once

#include <cstdint>
#include <vector>
#include <stdexcept>
#include <iostream>

namespace ms
{

class Ram
{
private:
    std::vector<uint8_t> data_;
    uint16_t base_adrr_;

public:
    Ram(uint16_t size, uint16_t base_adrr);
    
    // ~Ram();

    uint8_t read(uint16_t addr) const;
    void write(uint16_t addr, uint8_t new_data);
};


} // namespace ms

