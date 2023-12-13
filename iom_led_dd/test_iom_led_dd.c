/*
	filename: test_iom_led_dd.c
	Test program for LED device driver
*/

#include <stdio.h>
#include <unistd.h> // open()
#include <fcntl.h>  // O_WRONLY

#define DEV_NAME "/dev/iom_led"
#define ON 1
#define OFF 0

int main(int argc, char * argv[])
{
	int fd = -1;
	unsigned char led_signal = OFF;

	fd = open(DEV_NAME, O_WRONLY);
	
	if (fd < 0)
	{
		printf("Device open error!!!\n");
		return -1;
	}

	while(1)
	{
		printf("led_signal : %d\n", led_signal);
		led_signal = led_signal ? OFF : ON; // toggle
		write(fd, &led_signal, sizeof(led_signal));
		sleep(1);
	}

	close(fd);
	return 0;
}
