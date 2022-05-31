#pragma once

#include "SETUP.hpp"
#include "SD_card.hpp"
#include "Axi_gpio_controller.hpp"
#include "xilfpga.h"
#include <stdlib.h>

class Partial_module
{
private:
    u8 rst_pinN = 0;
    Axi_gpio_controller *axi_block = NULL;
    unsigned char *bitstream_buffer_ptr;
    u32 bitFile_fileSize;
    XFpga *XFpgaInstance_ref;
    u32 *xStatus_ref;
    // unsigned char *KeyAddr = NULL; // for future proofing with the use of XFpga_BitStream_Load()

public:
    /*****************************************************************************
     * constructer for a partial module
     *
     * @param bitfile reference to the bitfile location
     *
     * @param size size of the bitfile
     *
     * @param XFpgaInstance_ref An FPGA tag
     * 
     * @param xStatus_ref Where to put the status of the fpga
     *****************************************************************************/

    Partial_module(unsigned char *bitfile,
                   u32 size,
                   XFpga *_XFpgaInstance_ref,
                   u32 *xStatus_ref);
    /*****************************************************************************
     * constructer for a partial module
     *
     * @param card reference to the sd card mount position
     *
     * @param file_name Name of the bitfile on the mounted position
     *
     * @param XFpgaInstance_ref An FPGA tag
     * 
     * @param xStatus_ref Where to put the status of the fpga
     *****************************************************************************/
    Partial_module(SD_card *card,
                   const char *_file_name,
                   XFpga *_XFpgaInstance_ref,
                   u32 *xStatus_ref);

    /****************************************************************************
     * Set rst block reference
     *
     * @param rst_pin Pin in rst_block that resets block of type "Axi_gpio_controller"
     *
     * @param rst_block Reference to rst_block og type A
     *****************************************************************************/
    void set_rst_block(u8 _rst_pinN,
                       Axi_gpio_controller *axi_block);

    /*****************************************************************************
     * reconfigures the partial module
     *
     * @param en_rst Reset block on reconfiguration, will only reset if a rst_block is defined.
     *****************************************************************************/
    u32 reconfigure_PL(bool en_rst);

    ~Partial_module();
};
