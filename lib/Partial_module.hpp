// #pragma once

//#include <stdbool.h>
//#include <stdlib.h>
#include "SETUP.hpp"
#include "SD_card.hpp"
#include "Axi_gpio_controller.hpp"
//#include "xil_types.h"
#include "xilfpga.h"
#include <stdlib.h>

class Partial_module
{
public:
    u32 rst_pinN;
    Axi_gpio_controller *rst_block;
    SD_card *card;
    unsigned char *bitstream_buffer_ptr;
    u32 bitFile_fileSize;
    XFpga *XFpgaInstance_ref;
    unsigned char *KeyAddr = NULL;
    int status;

    Partial_module(int _rst_pinN,
                   Axi_gpio_controller *_rst_block,
                   SD_card *card,
                   const char *_file_name,
                   XFpga *_XFpgaInstance_ref);
                   
    u32 reconfigure_PL(bool en_rst);
    ~Partial_module();
};
