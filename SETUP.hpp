#ifndef SETUP_
#define SETUP_

#include <stdbool.h>
#include "xil_types.h"
#include "xparameters.h"
#include "xilfpga.h"

#define NAME_LENGTH 6
#define BITFILES_COUNT 2

#define SIZE_OF_PARTIAL_BITSTREAM_BUFFER 	3*1024*1024

//* Define how long the processor should sleep when doing DFX
#define SLEEP_DURATION 10 //useconds

//* Optional: Define bitfile to indexes
// #define _0BIT 0
// #define _1BIT 1
// #define _2BIT 2

//* Optional: Define Settings for DFX
#define RST_ON_RF TRUE
//#define SEND_RF_REQUEST FALSE //!Not implemented yet

//* DEFINE variables that contain axi gpio data
u32 axi_gpio_rst_out = 0;
//uint32_t axi_gpio_req_ack_in = 0; //! Not implemented yet


//* Choose init configurations
bool config_0_active = 1;


// Do not care about this
u32 partial_bitstream_FileSizes[NAME_LENGTH];
unsigned char *partial_bitstream_buffers[NAME_LENGTH];
u32 partial_bitstream_index;

XFpga XFpgaInstance = {0U};
u32 xStatus=0;

#endif //SETUP_





/*
#ifndef SETUP_
#define SETUP_

#include <stdbool.h>
#include <stdint.h>
#include "xparameters.h"

#define NAME_LENGTH 6
#define BITFILES_COUNT 2

#define SIZE_OF_PARTIAL_BITSTREAM_BUFFER 	3*1024*1024

//* Define how long the processor should sleep when doing DFX
#define SLEEP_DURATION 10 //useconds

//* Optional: Define bitfile to indexes
// #define _0BIT 0
// #define _1BIT 1
// #define _2BIT 2

//* optional: Define base addr to axi gpio blocks 
#define RST_OFFSET XPAR_AXI_GPIO_0_BASEADDR
//#define PR_REQUEST_OFFSET //!FILL

//* Optional: Define Settings for DFX
#define RST_ON_RF TRUE
//#define SEND_RF_REQUEST FALSE //!Not implemented yet

//* DEFINE variables that contain axi gpio data
uint32_t axi_gpio_rst_out = 0;
//uint32_t axi_gpio_req_ack_in = 0; //! Not implemented yet

//* Define the path to the *.bit files
char *path="0:/";

//! Remember to check the NAME_LENGTH and BITFILES_COUNT
//* Define partial bitstream files here
char partial_bitstream_fileNames[BITFILES_COUNT][NAME_LENGTH]={
    "0.bit",
    "1.bit"
};

//* Choose init configurations
bool config_0_active = 1;


// Do not care about this
unsigned int partial_bitstream_FileSizes[NAME_LENGTH];
unsigned char *partial_bitstream_buffers[NAME_LENGTH];
unsigned int partial_bitstream_index;

XFpga XFpgaInstance = {0U};
int xStatus=0;

#endif //SETUP_
*/