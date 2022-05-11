// #pragma once
// #ifndef READ_
// #define READ_

// #include "SETUP.hpp"

// #include "xilfpga.h"
// #include "sleep.h"
// #include "xil_cache.h"
// #include "xil_io.h"
// #include "xgpio.h"
// #include "xparameters.h"
// #include "xil_exception.h"
// #include "xscugic.h"
// #include "xsdps.h"
// #include "ff.h"



// long copy_test(const char *path, const char *name)
// {
// 	static FIL fil;
// 	static FATFS fatfs;
// 	static char *SD_File;
// 	FRESULT Res;
// 	UINT NumBytesRead;

//     unsigned int *buffer;

//     read_bitFile(buffer,"1_low.bit", "0:/");

// 	Res = f_mount(&fatfs, path, 0);
// 	if (Res != FR_OK)
// 	{
// 		return XST_FAILURE;
// 	}

// 	Res = f_mkdir("sub1");
// 	while (1)
// 		;
// };



// long read_bitFile(u32 &dist, const char *file_name, const char *path)
// {
//     static FIL fil;
//     static FATFS fatfs;
//     FRESULT Res;
//     UINT NumBytesRead;
//     unsigned int bSize;

//     Res = f_mount(&fatfs, path, 0);
//     if (Res != FR_OK)
//     {
//         return XST_FAILURE;
//     }

//     Res = f_open(&fil, file_name, FA_READ);
//     bSize = f_size(&fil);
//     Res = f_read(&fil, &dist, bSize, &NumBytesRead);
//     int data = 0;
//     unsigned int i = 0;
//     while (1)
//     {
//         i++;
//         usleep(100000);
//         data = i % 2; // set bit/pinN
//         Xil_Out32(XPAR_AXI_GPIO_1_BASEADDR, data);
//     };
//     if (Res != FR_OK)
//     {
//         return XST_FAILURE;
//     }

//     //! DELETE THIS
//     // Res = f_close(&fil);

//     if (Res != FR_OK)
//         return XST_FAILURE;
//     // f_unmount(path);
//     return 0;
// };

// void copy_to_file(u32)
// {
// }

// #endif
