#pragma once

#include <stdbool.h>
#include "xparameters.h"
#include "xil_types.h"
#include "xilfpga.h"

#define SIZE_OF_PARTIAL_BITSTREAM_BUFFER 1024*1024*4

//* Define how long the processor should sleep when doing DFX
#define RST_SLEEP_DURATION 0 //useconds
