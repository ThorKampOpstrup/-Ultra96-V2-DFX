#pragma once

#include <stdbool.h>
#include "xparameters.h"
#include "xil_types.h"
#include "xilfpga.h"


#define SIZE_OF_PARTIAL_BITSTREAM_BUFFER 1024*1024*8

//* Define how long the processor should sleep/hold rst low when doing DFX
#define RST_SLEEP_DURATION 0 //useconds

#define LED_PIN 0
#define LED_BASEADDR XPAR_AXI_GPIO_4_BASEADDR

#define RST_PIN 0
#define RST_BASEADDR XPAR_AXI_GPIO_3_BASEADDR
