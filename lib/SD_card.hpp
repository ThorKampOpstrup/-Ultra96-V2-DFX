#pragma once
#include "ff.h"

class SD_card
{
public:
    const char *path;
    FATFS fatfs;
    FRESULT res;

    long mount();
    long unmount();

    /*****************************************************************************
     * Constuctor for SD_card
     *
     * @param mounting_path
     *****************************************************************************/
    SD_card(const char *_path);
    long read_file(const char *file_name, void *dist_addr, u32 *bytes_read, u32 bytes_to_read);
    long write_file(const char *_file_name, void *src_addr, u32 size);
    long get_ptr_to_file(const char *_file_name, unsigned char &ptr, u32 &_size);
    int status;
    ~SD_card();
};