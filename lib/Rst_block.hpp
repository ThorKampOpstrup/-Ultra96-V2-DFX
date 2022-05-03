#pragma once

#include "SETUP.hpp"

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
