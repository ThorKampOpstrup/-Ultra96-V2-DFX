#pragma once
#include "xil_types.h"


class Axi_gpio_controller
{
private:
    u32 base_addr;
    u64 data; // contains the data/status of the output of the axi gpio out controller
public:
    /*****************************************************************************
     * constructer for a Axi_gpio_controller
     *
     * @param offset memory address offset
     *****************************************************************************/
    Axi_gpio_controller(u32 _offset);

    /*****************************************************************************
     * Write data
     *
     * @param data The data to write and will be saved in the class
     *****************************************************************************/
    template <typename T>
    void write_data(T data);

    /*****************************************************************************
     * reads data and puts it in out
     *
     * @param out writes read data to the out
     *****************************************************************************/
    template <typename T>
    void read_data(T *out);

    /*****************************************************************************
     * Sets pin nr. N
     *
     * @param pinN Pin to set
     *****************************************************************************/
    void set_pin(u8 pinN);

    /*****************************************************************************
     * Clears pin nr. N
     *
     * @param pinN Pin to clear
     *****************************************************************************/
    void clear_pin(u8 pinN);

    ~Axi_gpio_controller();
};
