#include "ram.hpp"
namespace ms
{

Ram::Ram(uint16_t size, uint16_t base_adrr) : base_adrr_(base_adrr)
{
    data_.resize(size);

}

uint8_t Ram::read(uint16_t addr) const
{

    if(addr >= data_.size())
    {
        throw std::runtime_error("ms error: In ram reading, wrong address");
    }

    return data_[addr];

}

void Ram::write(uint16_t addr, uint8_t new_data)
{
    if(addr >= data_.size())
    {
        throw std::runtime_error("ms error: In ram writing, wrong address");
    }

    data_[addr] = new_data;
}

    
} // namespace ms


