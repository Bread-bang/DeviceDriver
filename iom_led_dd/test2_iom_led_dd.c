/*
	filename: test_iom_led_dd.c
	Test program for LED device driver
*/

#include <stdio.h>
#include <unistd.h> // open()
#include <fcntl.h>  // O_WRONLY
#include <signal.h> // SIGINT

#define DEV_NAME "/dev/iom_led"
#define ON 1
#define OFF 0

int quit = 0;

void quit_signal(int sig)
{
	quit = 1;
}

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

	signal(SIGINT, quit_signal);

	while(!quit)
	{
		led_signal = led_signal ? OFF : ON; // toggle
		write(fd, &led_signal, sizeof(led_signal));
		sleep(1);
	}

	printf("Program is terminated by sigint signal...\n");
	
	close(fd);
	return 0;
}
