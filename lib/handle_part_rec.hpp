#include "../SETUP.hpp"
#include "readFiles.hpp"

//#include <string.h>
#include <stdbool.h>
#include "xilfpga.h"
#include "platform.h"
#include "sleep.h"
#include "xil_cache.h"
#include "xil_io.h"
#include "xgpio.h"
#include "xil_exception.h"
#include "xscugic.h"
#include "xsdps.h"
//#include "ff.h"

// contains the axi gpio
uint32_t axi_gpio = 0;

//! What is this?
XFpga XFpgaInstance = {0U};

int init_part_rec()
{
    for (int i = 0; i < BITFILES_COUNT; i++)
    {
        partial_bitstream_buffers[i] = (unsigned char *)malloc(SIZE_OF_PARTIAL_BITSTREAM_BUFFER);
    }

    read_all_bitFiles();
};

// Set the axi-gpio pinN if set, and clear else
void set_rstPin(bool set, uint8_t pinN)
{
    if (set)
        axi_gpio |= (0x1 << pinN); // set bit/pinN
    else
        axi_gpio &= ~(0x1 << pinN); // clear bit/pinN

    Xil_Out32(RST_OFFSET, axi_gpio);
};

// //Partially reconfigures the fpga with the *.bit file send as argument, and returns the status of the fpga
int do_partial_reconfiguration(int partial_bitFile_index)
{
    int status;

    //! IF XFpga_PL_BitStream_Load does not work use XFpga_BitStream_Load
    status = XFpga_PL_BitStream_Load(&XFpgaInstance, partial_bitstream_buffers[partial_bitFile_index], partial_bitstream_FileSizes[partial_bitFile_index], XFPGA_PARTIAL_EN);
    return status;
};
