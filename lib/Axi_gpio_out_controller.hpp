#pragma once

#include "SETUP.hpp"

#include "xil_types.h"

class Axi_gpio_out_controller
{
public:
    u32 base_addr;
    u32 data = 0; //contains the data/status of the output of the axi gpio out controller

    /*****************************************************************************
     * constructer for a Axi_gpio_controller
     *
     * @param offset memory address offset
     *****************************************************************************/
    Axi_gpio_out_controller(u32 _offset);

    /*****************************************************************************
     * Sets pin nr. N
     *
     * @param pinN Pin to set
     *****************************************************************************/
    void set_pin(u32 pinN);

    /*****************************************************************************
     * Clears pin nr. N
     *
     * @param pinN Pin to clear
     *****************************************************************************/
    void clear_pin(u32 pinN);

    ~Axi_gpio_out_controller();
};
