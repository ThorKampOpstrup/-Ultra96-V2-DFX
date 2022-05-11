#include "../lib/Axi_gpio_controller.hpp"
#include "xil_types.h"

Axi_gpio_controller::Axi_gpio_controller(u32 _rst_offset)
{
    base_addr = _rst_offset;
};

void Axi_gpio_controller::set_pin(u32 pinN)
{
    data |= (0x1 << pinN); // set bit/pinN
    Xil_Out32(base_addr, data);
};

void Axi_gpio_controller::clear_pin(u32 pinN)
{
    data &= ~(0x1 << pinN); // clear bit/pinN
    Xil_Out32(base_addr, data);
};

Axi_gpio_controller::~Axi_gpio_controller()
{
}