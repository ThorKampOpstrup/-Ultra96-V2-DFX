#include "../lib/SD_card.hpp"
#include "ff.h"
#include "xstatus.h"
#include "xil_cache.h"
#include "xilfpga.h"

SD_card::SD_card(const char *_path)
{
    path = _path;
    status = mount();
}

long SD_card::mount()
{
    res = f_mount(&fatfs, path, 1);
    if (res)
        return XST_FAILURE;
    return XST_SUCCESS;
}

long SD_card::unmount()
{
    res = f_mount(0, path, 1);
    if (res)
        return XST_FAILURE;
    return XST_SUCCESS;
};

long SD_card::read_file(const char *file_name, void *dist_addr, u32 *bytes_read, u32 bytes_to_read)
{
    FIL fil;

    res = f_open(&fil, file_name, FA_READ);
    if (res)
        return XST_FAILURE;

    res = f_lseek(&fil, 0);
    if (res)
        return XST_FAILURE;

    res = f_read(&fil, dist_addr, bytes_to_read, bytes_read);

    if (res)
        return XST_FAILURE;

    res = f_close(&fil);
    if (res)
        return XST_FAILURE;

    return XST_SUCCESS;
}

long SD_card::write_file(const char *_file_name, void *src_addr, u32 size)
{
    UINT bytes_written;
    static FIL fil;

    res = f_open(&fil, (char *)_file_name, FA_OPEN_ALWAYS | FA_WRITE);
    if (res)
        return XST_FAILURE;

    res = f_write(&fil, (const void *)src_addr, size, &bytes_written);
    if (res)
        return XST_FAILURE;

    res = f_close(&fil);
    if (res)
        return XST_FAILURE;

    return XST_SUCCESS;
}

SD_card::~SD_card()
{
    status = unmount();
    Xil_DCacheFlush();
}
