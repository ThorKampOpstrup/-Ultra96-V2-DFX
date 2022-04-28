#include "xparameters.h"


#define RST_OFFSET XPAR_AXI_GPIO_0_BASEADDR

#define NAME_LENGTH 6
#define BITFILES_COUNT 2

#define SIZE_OF_PARTIAL_BITSTREAM_BUFFER 	3*1024*1024


// Optional define bitfile to indexes
// #define _0BIT 0
// #define _1BIT 1
// #define _2BIT 2



// Define the path to the *.bit files
char *path="0:/";

//! Remember to check the NAME_LENGTH and BITFILES_COUNT
// Define partial bitstream files here
char partial_bitstream_fileNames[BITFILES_COUNT][NAME_LENGTH]={
    "0.bit",
    "1.bit"
};

// Choose init configurations
bool config_0_active = 1;


// DO nat care about this
uint32_t partial_bitstream_FileSizes[NAME_LENGTH];
UINTPTR partial_bitstream_buffers[NAME_LENGTH];
uint32_t partial_bitstream_index;

