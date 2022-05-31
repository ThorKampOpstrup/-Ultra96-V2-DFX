#include "xilfpga.h"
#include "../lib/SD_card.hpp"
#include "SETUP.hpp"
#include <stdlib.h>

XFpga XFpgaInstance = {0U};
u32 xStatus = 0;


void test_full()
{
    xStatus = XFpga_Initialize(&XFpgaInstance);

    unsigned char *bitstream_buffer_ptr;
    bitstream_buffer_ptr = (unsigned char *)malloc(SIZE_OF_PARTIAL_BITSTREAM_BUFFER);
    u32 bitFile_fileSize;

    SD_card card("0:/");
    card.read_file("full.bit", bitstream_buffer_ptr, &bitFile_fileSize, SIZE_OF_PARTIAL_BITSTREAM_BUFFER);
    bitstream_buffer_ptr = (unsigned char *)realloc(bitstream_buffer_ptr, bitFile_fileSize);

    while (1)
    {
        xStatus = XFpga_PL_BitStream_Load(&XFpgaInstance, (UINTPTR)bitstream_buffer_ptr, bitFile_fileSize, XFPGA_FULLBIT_EN);
        //usleep(1000000);
    }
    
}