/* filename: rpi4_bcm2711_gpio_registers.h */ 
/* Raspberrypi4 Register View for GPIO */
/* BCM2711 ARM Peripherals */

#define GPIO_BASE 0xFE200000 // 0x7E20_0000
#define GPFSEL0 0x00         // Offset of the GPFSEL0 register
#define GPFSEL1 0x04 	     // Offset of the GPFSEL1 register
#define GPFSEL2 0x08         // Offset of the GPFSEL2 register
#define GPFSEL3 0x0C         // Offset of the GPFSEL3 register
#define GPFSEL4 0x10         // Offset of the GPFSEL4 register
#define GPFSEL5 0x14         // Offset of the GPFSEL5 register

#define GPSET0 0x1C          // Offset of the GPSET0 register
#define GPSET1 0x20          // Offset of the GPSET1 register

#define GPCLR0 0x28          // Offset of the GPCLR0 register
#define GPCLR1 0x2C          // Offset of the GPCLR1 register

#define GPLEV0 0x34          // Offset of the GPLEV0 register
#define GPLEV1 0x38          // Offset of the GPLEV1 register

#define GPFSEL 0x00
#define GPSET 0x1C
#define GPCLR 0x28
#define GPLEV 0x34
