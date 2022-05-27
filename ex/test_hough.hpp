#include "lib/Axi_gpio_controller.hpp"
#include "lib/Partial_module.hpp"
#include "SETUP.hpp"
#include "xhoughlines_accel.h"
#include "xilfpga.h"
#include "xparameters.h"
#include "lib/SD_card.hpp"
#include "tgmath.h"

#define IMAGE_X 640
#define IMAGE_Y 480
#define SIZE IMAGE_X *IMAGE_Y

#define LINES_OUT 32

XFpga XFpgaInstance = {0U};
u32 xStatus = 0;

void generate_circle_on_adress(uint8_t *addr_ptr, int width, int hight, int radius)
{
    for (int y = 0; y < hight; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (sqrt(abs(pow(x - (width / 2), 2)) + (abs(pow((y - (hight / 2)), 2)))) > 200)
                *(addr_ptr + x + y) = 255;
            else
                *(addr_ptr + x + y) = 0;
        }
    }
}

// int callHoughIP(uint8_t *ptr_img_data_in, uint8_t *ptr_lines_out)//!Old name
int get_hough(uint8_t *ptr_img_data_in, uint8_t *ptr_lines_out)
{
    XHoughlines_accel xhl;
    xhl.Bus_a_BaseAddress = XPAR_HIER_HOUGH_HOUGHLINES_ACCEL_0_S_AXI_BUS_A_BASEADDR;

    int length;

    // RCLCPP_DEBUG(this->get_logger(), "Polling for houghlines_accel IP ready");

    while (!XHoughlines_accel_IsReady(&xhl))
        ;

    length = XHoughlines_accel_Write_img_in_Bytes(&xhl, 0, (char *)ptr_img_data_in, SIZE);

    // if (length == SIZE)
    // {
    //     RCLCPP_DEBUG(this->get_logger(), "Wrote batch to houghlines_accel IP");
    // }
    // else
    // {
    //     RCLCPP_ERROR(this->get_logger(), "Could not write batch to houghlines_accel IP");

    //     return 0;
    // }

    // RCLCPP_DEBUG(this->get_logger(), "Polling for houghlines_accel IP idle");

    while (!XHoughlines_accel_IsIdle(&xhl))
        ;

    // RCLCPP_DEBUG(this->get_logger(), "Starting houghlines_accel IP");

    XHoughlines_accel_Start(&xhl);

    // RCLCPP_DEBUG(this->get_logger(), "Started houghlines_accel IP");

    while (!XHoughlines_accel_IsIdle(&xhl))
        ;

    // RCLCPP_DEBUG(this->get_logger(), "IP houghlines_accel is idle, reading out bytes");

    XHoughlines_accel_Read_theta_array_Bytes(&xhl, 0, (char *)(&ptr_lines_out[0]), LINES_OUT);

    return 1;
}

//! call this test function
int test_hough()
{
    SD_card card("0:/");
    uint8_t *pic_ptr;
    pic_ptr = (uint8_t *)malloc(SIZE);
    u32 pic_size;
    Axi_gpio_controller LED(LED_BASEADDR);
    LED.set_pin(LED_PIN);


	Partial_module part_0(&card, "1_low.bit", &XFpgaInstance);
	// Partial_module part_0(RST_PIN, &partial_rst_block, &card, "1_low.bit", &XFpgaInstance);

	Partial_module part_1(&card, "1_high.bit", &XFpgaInstance);

    part_0.reconfigure_PL(1);
	part_1.reconfigure_PL(1);
	u32 region_selector = 0;


	while (1)
	{
		LED.clear_pin(LED_PIN);
		region_selector % 2 ? part_0.reconfigure_PL(1) : part_1.reconfigure_PL(1);
		LED.set_pin(LED_PIN);
		usleep(100000);
		region_selector++;
	}

    generate_circle_on_adress(pic_ptr, IMAGE_X, IMAGE_Y, 200);

    card.write_file("TEST.JPG", pic_ptr, SIZE);
    uint8_t hough_data[LINES_OUT];
    LED.clear_pin(LED_PIN);

    get_hough(pic_ptr, hough_data);

    return 1;
};