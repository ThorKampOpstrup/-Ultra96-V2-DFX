// #pragma once

//#include <stdbool.h>
//#include <stdlib.h>
#include "SETUP.hpp"
#include "SD_card.hpp"
#include "Axi_gpio_out_controller.hpp"
//#include "xil_types.h"
#include "xilfpga.h"
#include <stdlib.h>

class Partial_module
{
public:
    u32 rst_pinN = 0;
    Axi_gpio_out_controller *rst_block = NULL;
    SD_card *card;
    unsigned char *bitstream_buffer_ptr;
    u32 bitFile_fileSize;
    XFpga *XFpgaInstance_ref;
    unsigned char *KeyAddr = NULL; // for future proofing
    int status;

    /*****************************************************************************
     * constructer for a partial module
     *
     * @param card reference to the sd card mount position
     *
     * @param file_name Name of the bitfile on the mounted position
     *
     * @param XFpgaInstance_ref Where to put the status of the fpga
     *****************************************************************************/
    Partial_module(SD_card *card,
                   const char *_file_name,
                   XFpga *_XFpgaInstance_ref);

    /****************************************************************************
     * Overload constructer for a partial module
     *
     * @param rst_pin Pin in rst_block that resets block of type "Axi_gpio_out_controller"
     *
     * @param rst_block Reference to rst_block og type A
     *
     * @param card Reference to the sd card mount position
     *
     * @param file_name Name of the bitfile on the mounted position
     *
     * @param XFpgaInstance_ref Where to put the status of the fpga
     *****************************************************************************/
    Partial_module(int _rst_pinN,
                   Axi_gpio_out_controller *_rst_block,
                   SD_card *card,
                   const char *_file_name,
                   XFpga *_XFpgaInstance_ref);

    /*****************************************************************************
     * reconfugires the partial module
     *
     * @param en_rst Reset block on reconfiguration, will only reset if a rst_block is defined.
     *****************************************************************************/
    u32 reconfigure_PL(bool en_rst);

    ~Partial_module();
};
