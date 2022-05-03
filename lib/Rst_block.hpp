#include "SETUP.hpp"

#include "xil_io.h"
#include "xil_types.h"

class Rst_block
{
public:
    u32 base_addr;
    u32 data = 0;
    Rst_block(u32 _rst_offset);
    void set_pin(u32 pinN);
    void clear_pin(u32 pinN);
    ~Rst_block();
};

Rst_block::Rst_block(u32 _rst_offset)
{
    base_addr = _rst_offset;
};

void Rst_block::set_pin(u32 pinN)
{
    data |= (0x1 << pinN); // set bit/pinN
    Xil_Out32(base_addr, data);
};

void Rst_block::clear_pin(u32 pinN)
{
    data &= ~(0x1 << pinN); // clear bit/pinN
    Xil_Out32(base_addr, data);
};

Rst_block::~Rst_block()
{
}
