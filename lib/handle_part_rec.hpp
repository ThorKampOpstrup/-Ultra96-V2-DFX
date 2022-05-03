#include "SETUP.hpp"
#include "readFiles.hpp"
#include <stdlib.h>
#include <stdbool.h>

#include "xilfpga.h"
#include "sleep.h"
#include "xil_cache.h"
#include "xil_io.h"
#include "xgpio.h"
#include "xil_exception.h"
#include "xscugic.h"
#include "xsdps.h"


void init_part_rec()
{
    if (xStatus != XST_SUCCESS){
        xStatus = XFpga_Initialize ( &XFpgaInstance );
        //Asumes that the initialization od the FPGA was successful
    }

    //! RESET ALL PARTIAL BLOCKS
};
