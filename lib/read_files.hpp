#ifndef READ_FILES_
#define READ_FILES_

#include "SETUP.hpp"

#include "xilfpga.h"
#include "sleep.h"
#include "xil_cache.h"
#include "xil_io.h"
#include "xgpio.h"
#include "xparameters.h"
#include "xil_exception.h"
#include "xscugic.h"
#include "xsdps.h"
#include "ff.h"

long read_bitFile(u32 &dist, char *file_name, const char *path)
{
    static FIL fil;
    static FATFS fatfs;
    static char *SD_File;
    FRESULT Res;
    UINT NumBytesRead;
    unsigned int i;

    Res = f_mount(&fatfs, path, 0);
    if (Res != FR_OK)
    {
        return XST_FAILURE;
    }

    SD_File = (char *)dist;

    Res = f_open(&fil, SD_File, FA_READ);
    if (Res)
        return XST_FAILURE;

    Res = f_lseek(&fil, 0);

    Res = f_read(&fil, &dist, SIZE_OF_PARTIAL_BITSTREAM_BUFFER, &NumBytesRead);
    if (Res)
        return XST_FAILURE;

    dist = NumBytesRead;
};

#endif //#ifdef READ_FILES_
