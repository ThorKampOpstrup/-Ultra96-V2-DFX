#include "../lib/Axi_gpio_controller.hpp"
#include "../lib/Partial_module.hpp"
//#include "../lib/read_files.hpp"
#include "xparameters.h"
#include "xilfpga.h"
#include "SETUP.hpp"
#include "../lib/SD_card.hpp"

// #include "xscugic.h"
// #include "xsdps.h"
// static XScuGic_Config *GicConfig;
// XScuGic InterruptController;

#define LED_PIN 0
#define RST_PIN 0

XFpga XFpgaInstance = {0U};
u32 xStatus = 0;

void cp_file(SD_card *_card, const char *_src, const char *_dist)
{
	unsigned char *buffer;
	u32 bytes_read = 0;
	u32 bytes_t_read = 1024 * 1024 * 4;
	buffer = (unsigned char *)malloc(bytes_t_read);
	_card->read_file(_src, buffer, &bytes_read, bytes_t_read);
	buffer = (unsigned char *)realloc(buffer, bytes_read);
	_card->write_file(_dist, buffer, bytes_read);
}

void test()
{

	// int data = (0x1 << 0); // set bit/pinN
	// Xil_Out32(XPAR_AXI_GPIO_1_BASEADDR, data);

	xStatus = XFpga_Initialize(&XFpgaInstance);
	// xStatus = ScuGicInterrupt_Init(XPAR_SCUGIC_0_DEVICE_ID);

	Axi_gpio_controller LED(XPAR_AXI_GPIO_1_BASEADDR);
	LED.clear_pin(LED_PIN);

	Axi_gpio_controller partial_rst_block(XPAR_AXI_GPIO_0_BASEADDR);

	// write_test("0:/", "test1");
	SD_card card("0:/");
	cp_file(&card, "test_org.JPG", "test_cp.jpg");

	Partial_module part_0(RST_PIN, &partial_rst_block, &card, "1_low.bit", &XFpgaInstance);

	part_0.reconfigure_PL(1);

	Partial_module part_1(RST_PIN, &partial_rst_block, &card, "1_high.bit", &XFpgaInstance);
	//  LED.clear_pin(LED_PIN);

	// LED.set_pin(LED_PIN);

	partial_rst_block.set_pin(RST_PIN);

	while (1)
	{
		LED.clear_pin(LED_PIN);
		part_0.reconfigure_PL(1);
		LED.set_pin(LED_PIN);
		//usleep(10000);
		LED.clear_pin(LED_PIN);
		part_1.reconfigure_PL(1);
		LED.set_pin(LED_PIN);
		//usleep(10000);
	}

	// int data = 0;
	// unsigned int i = 0;
	// while (1)
	// {
	// 	i++;
	// 	usleep(100000);
	// 	data = i % 2; // set bit/pinN
	// 	Xil_Out32(XPAR_AXI_GPIO_1_BASEADDR, data);
	// }
}
