#pragma once

#include "SETUP.hpp"

#include "xil_types.h"

class Axi_gpio_controller
{
public:
    u32 base_addr;
    u32 data = 0;
    Axi_gpio_controller(u32 _rst_offset);
    void set_pin(u32 pinN);
    void clear_pin(u32 pinN);
    ~Axi_gpio_controller();
};
