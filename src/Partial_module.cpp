#include "SETUP.hpp"
#include "../lib/Partial_module.hpp"
#include "../lib/SD_card.hpp"
#include "../lib/Axi_gpio_out_controller.hpp"
#include "xil_types.h"
#include <stdlib.h>

Partial_module::Partial_module(SD_card *_card,
                               const char *_file_name,
                               XFpga *_XFpgaInstance_ref)
{
    card = _card;
    XFpgaInstance_ref = _XFpgaInstance_ref;

    bitstream_buffer_ptr = (unsigned char *)malloc(SIZE_OF_PARTIAL_BITSTREAM_BUFFER);
    status = _card->read_file(_file_name, bitstream_buffer_ptr, &bitFile_fileSize, SIZE_OF_PARTIAL_BITSTREAM_BUFFER);
    bitstream_buffer_ptr = (unsigned char *)realloc(bitstream_buffer_ptr, bitFile_fileSize);
    //status = _card->write_file("test.bit", bitstream_buffer_ptr, bitFile_fileSize);
};


Partial_module::Partial_module(int _rst_pinN,
                               Axi_gpio_out_controller *_rst_block,
                               SD_card *_card,
                               const char *_file_name,
                               XFpga *_XFpgaInstance_ref)
{
    rst_pinN = _rst_pinN;
    rst_block = _rst_block;
    card = _card;
    XFpgaInstance_ref = _XFpgaInstance_ref;

    bitstream_buffer_ptr = (unsigned char *)malloc(SIZE_OF_PARTIAL_BITSTREAM_BUFFER);
    status = _card->read_file(_file_name, bitstream_buffer_ptr, &bitFile_fileSize, SIZE_OF_PARTIAL_BITSTREAM_BUFFER);
    bitstream_buffer_ptr = (unsigned char *)realloc(bitstream_buffer_ptr, bitFile_fileSize);
    //status = _card->write_file("test.bit", bitstream_buffer_ptr, bitFile_fileSize);
};

u32 Partial_module::reconfigure_PL(bool en_rst)
{
    u32 status;

    if (en_rst && rst_block != NULL)
    {
        rst_block->set_pin(rst_pinN);
    }

    //! This 'XFpga_PL_BitStream_Load' will be deprecated in the 2022.1 release. Use the updated ' XFpga_BitStream_Load() ' API to perform the same functionality.
    status = XFpga_PL_BitStream_Load(XFpgaInstance_ref, (UINTPTR)bitstream_buffer_ptr, bitFile_fileSize, XFPGA_PARTIAL_EN);
    // status = XFpga_BitStream_Load(XFpgaInstance_ref, (UINTPTR)bitstream_buffer_ptr, (UINTPTR)key_addr, bitFile_fileSize, XFPGA_PARTIAL_EN);

    if (en_rst && rst_block != NULL)
    {
        usleep(RST_SLEEP_DURATION);
        rst_block->clear_pin(rst_pinN);
    }

    return status;
};

Partial_module::~Partial_module()
{
}
