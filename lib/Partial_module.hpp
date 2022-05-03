#include <stdbool.h>
#include <stdlib.h>
#include "SETUP.hpp"
#include "Rst_block.hpp"
#include "xil_types.h"

class Partial_module
{
public:
    u32 rst_pinN;
    Rst_block *rst_block;
    const char *path;
    const char *bitFile_name;
    u32 *bitstream_buffer;


    Partial_module(u32 _rst_pinN, Rst_block *_rst_block, char *_path, char *_bitFile_name, u32 *bitstream_buffer);
    u32 reconfigure_PL(bool en_rst);

    ~Partial_module();
};