/* filename: rpi4_gpio_control.c */

#include "./rpi4_bcm2711_gpio_registers.h"

//select gpio function: input(000), output(001), alternate function(010 ~ 111)
#define GPIO_FSEL_INPUT 0x00
#define GPIO_FSEL_OUTPUT 0x01
#define GPIO_INPUT 0x00 // same as GPIO_FSEL_INPUT
#define GPIO_OUTPUT 0x01 // same as GPIO_FSEL_OUTPUT

#define GPIO_SET 1
#define GPIO_CLR 1
#define SET_GPIO 1
#define CLR_GPIO 1
#define GPIO_LEV_HIGH 1
#define GPIO_LEV_LOW 0

//#define IOREMAP_SIZE 0x40 // GPFSEL0 ~ GPLEV1

//static unsigned int *ioremapped_gpio_addr;

// 해당 단자를 INPUT으로 할 것인지 OUTPUT으로 할 것인지
void gpio_select(int gpio_pin_number,int function)
{
	
	//reset 3bit to 000
	ioremapped_gpio_addr[GPFSEL/4 + (gpio_pin_number/10)] &= ~(0x07<<(3*(gpio_pin_number%10)));	

	switch(function)
	{
		case GPIO_FSEL_INPUT:
			break;
		case GPIO_FSEL_OUTPUT:
			ioremapped_gpio_addr[GPFSEL/4 + (gpio_pin_number/10)] |= GPIO_FSEL_OUTPUT<<(3*(gpio_pin_number%10));
			break;
		default:;
	}
}

//set gpio register
void gpio_set(int gpio_pin_number,int function)
{
	if(function) //set
		ioremapped_gpio_addr[GPSET/4 + (gpio_pin_number/32)] = GPIO_SET<<(gpio_pin_number%32);
	else //unset
		ioremapped_gpio_addr[GPSET/4+(gpio_pin_number/32)] &= ~(0x01<<(gpio_pin_number%32));
}

// clear gpio register
void gpio_clr(int gpio_pin_number,int function)
{
	if(function)
        ioremapped_gpio_addr[GPCLR/4 + (gpio_pin_number/32)] = GPIO_SET<<(gpio_pin_number%32);
	else
        ioremapped_gpio_addr[GPCLR/4 + (gpio_pin_number/32)] &= ~(0x01<<(gpio_pin_number%32));

}

//read gpio level
int gpio_lev(int gpio_pin_number)
{
	//Level 레지스터에서 GPIO Pin에 대한 해당 bit을 확인하여 INPUT 여부 확인(register bit이 1일 경우 INPUT 발생한 것)
	if(ioremapped_gpio_addr[GPLEV/4 + (gpio_pin_number/32)] &= 0x1<<(gpio_pin_number%32)) 
		return GPIO_LEV_HIGH;
	else
		return GPIO_LEV_LOW;	
}

