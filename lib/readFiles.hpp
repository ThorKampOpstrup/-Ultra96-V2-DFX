#include "../SETUP.hpp"

#include "xilfpga.h"
#include "platform.h"
#include "sleep.h"
#include "xil_cache.h"
#include "xil_io.h"
#include "xgpio.h"
#include "xparameters.h"
#include "xil_exception.h"
#include "xscugic.h"
#include "xsdps.h"
#include "ff.h"

int read_all_bitFiles(void)
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

    for (i = 0; i < BITFILES_COUNT; i++)
    {
        SD_File = (char *)partial_bitstream_fileNames[i];

        Res = f_open(&fil, SD_File, FA_READ);
        if (Res)
            return XST_FAILURE;

        Res = f_lseek(&fil, 0);

        Res = f_read(&fil, partial_bitstream_buffers[i], SIZE_OF_PARTIAL_BITSTREAM_BUFFER, &NumBytesRead);
        if (Res)
            return XST_FAILURE;

        partial_bitstream_FileSizes[i] = NumBytesRead;
    }
}