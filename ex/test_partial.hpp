#include "../lib/Axi_gpio_controller.hpp"
#include "../lib/Partial_module.hpp"
#include "xparameters.h"
#include "xilfpga.h"
#include "SETUP.hpp"
#include "../lib/SD_card.hpp"
#include <xtime_l.h>

XFpga XFpgaInstance = {0U};
u32 xStatus = 0;

void cp_file(SD_card *_card, const char *_src, const char *_dist)
{
	unsigned char *buffer;
	u32 bytes_read = 0;
	u32 bytes_t_read = 1024 * 1024 * 6;

	buffer = (unsigned char *)malloc(bytes_t_read);
	_card->read_file(_src, buffer, &bytes_read, bytes_t_read);
	buffer = (unsigned char *)realloc(buffer, bytes_read);
	_card->write_file(_dist, buffer, bytes_read);
}

void test_partial()
{
	// int data = (0x1 << 0); // set bit/pinN
	// Xil_Out32(XPAR_AXI_GPIO_1_BASEADDR, data);

	xStatus = XFpga_Initialize(&XFpgaInstance);
	// xStatus = ScuGicInterrupt_Init(XPAR_SCUGIC_0_DEVICE_ID);

	Axi_gpio_controller LED(LED_BASEADDR);
	LED.set_pin(LED_PIN);

	// Axi_gpio_out_controller partial_rst_block(XPAR_AXI_GPIO_3_BASEADDR);
	// LED.set_pin(LED_PIN);

	// write_test("0:/", "test1");
	SD_card card("0:/");
	// cp_file(&card, "ORG.JPG", "CP.JPG");
	//Bit_file _1_low;
	//_1_low.name = "1_low.bit";
	//card.get_ptr_to_file(_1_low.name, _1_low.ptr, _1_low.size);

	//Bit_file _1_high;
	//_1_high.name = "1_high.bit";
	//card.get_ptr_to_file(_1_high.name, _1_high.ptr, _1_high.size);


	//Partial_module part_0(&_1_low.ptr, _1_low.size, &XFpgaInstance, &xStatus);
	Partial_module part_0(&card, "1_low.bit", &XFpgaInstance, &xStatus);
	// Partial_module part_0(RST_PIN, &partial_rst_block, &card, "1_low.bit", &XFpgaInstance);

	//Partial_module part_1(&_1_high.ptr, _1_high.size, &XFpgaInstance, &xStatus);
	Partial_module part_1(&card, "1_high.bit", &XFpgaInstance, &xStatus);
	// Partial_module part_1(RST_PIN, &partial_rst_block, &card, "1_high.bit", &XFpgaInstance);
	//  LED.clear_pin(LED_PIN);
	// spart_0.reconfigure_PL(1);
	// part_1.set_rst_block(RST_PIN,partial_rst_block);

	u32 data_points = 100;
	float collection[data_points];

	XTime start, stop;
	XTime_StartTimer();

	part_0.reconfigure_PL(1);
	part_1.reconfigure_PL(1);
	u32 region_selector = 0;

	XTime_GetTime(&start);
	// while (region_selector < data_points)
	while (1)
	{
		LED.set_pin(LED_PIN);
		// XTime_GetTime(&start);
		region_selector % 2 ? part_0.reconfigure_PL(0) : part_1.reconfigure_PL(0);
		// XTime_GetTime(&stop);
		LED.clear_pin(LED_PIN);

		// collection[region_selector]=((float)(stop-start))/100000;

		usleep(100000);
		region_selector++;
	}
}
