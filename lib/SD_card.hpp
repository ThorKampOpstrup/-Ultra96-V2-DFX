#pragma once
#include "ff.h"

class SD_card
{
private:
    const char *path;
    FATFS fatfs;
    FRESULT res;

    long mount();
    long unmount();

public:
    /*****************************************************************************
     * Constuctor for SD_card
     *
     * @param mounting_path
     *****************************************************************************/
    SD_card(const char *_path);
    long read_file(const char *file_name, void *dist_addr, u32 *bytes_read, u32 bytes_to_read);
    long write_file(const char *_file_name, void *src_addr, u32 size);
    int status;
    ~SD_card();
};