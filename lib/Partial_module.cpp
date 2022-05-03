#include <stdbool.h>
#include "SETUP.hpp"
#include "Rst_block.hpp"
#include "xil_types.h"
#include "readFiles.hpp"

#include "Partial_module.hpp"

Partial_module::Partial_module(u32 _rst_pinN, Rst_block *_rst_block, char *_path, char *_bitFile_name, u32 *_bitstream_image_addr)
{
    rst_pinN = _rst_pinN;
    rst_block = _rst_block;
    path = _path;
    bitFile_name = _bitFile_name;

    bitstream_buffer = _bitstream_image_addr;
}

u32 Partial_module::reconfigure_PL(bool en_rst){
    u32 status;

    if (en_rst)
    {
        rst_block->set_pin(rst_pinN);
        usleep(10);
    }

    //! IF XFpga_PL_BitStream_Load does not work use XFpga_BitStream_Load
    status = XFpga_PL_BitStream_Load(&XFpgaInstance, (UINTPTR)bitstream_buffer, (UINTPTR)partial_bitstream_FileSizes, XFPGA_PARTIAL_EN);
    
    
    return status;
}

Partial_module::~Partial_module()
{
}