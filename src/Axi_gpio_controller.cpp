#include "../lib/Axi_gpio_controller.hpp"
#include "xil_types.h"

Axi_gpio_controller::Axi_gpio_controller(u32 _offset)
{
    base_addr = _offset;
};

template <typename T>
void Axi_gpio_controller::write_data(T in_data)
{
    data = in_data; // set bit/pinN
    volatile T *LocalAddr = (volatile T *)base_addr;
    *LocalAddr = (T)data;
};

template <typename T>
void Axi_gpio_controller::read_data(T *out)
{
    out = (volatile T *) base_addr;
};

void Axi_gpio_controller::set_pin(u8 pinN)
{
    data |= (0x1 << pinN); // set bit/pinN
    write_data(data);
};

void Axi_gpio_controller::clear_pin(u8 pinN)
{
    data &= ~(0x1 << pinN); // clear bit/pinN

    write_data(data);
};

Axi_gpio_controller::~Axi_gpio_controller()
{
}