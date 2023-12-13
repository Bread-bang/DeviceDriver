/*
	filename: test_iom_fnd_dd.c
	Test program for FND device driver
*/

#include <stdio.h>
#include <unistd.h> // open()
#include <fcntl.h>  // O_WRONLY
#include <signal.h> // SIGINT

#define DEV_NAME "/dev/iom_fnd"
#define ON 1
#define OFF 0
#define YES 1
#define NO 0

int isQuit = 0;

void isQuit_signal(int sig)
{
	isQuit = YES;
}

int main(int argc, char * argv[])
{
	int fd = -1;
	unsigned char fnd_data = 0;

	fd = open(DEV_NAME, O_WRONLY);
	
	if (fd < 0)
	{
		printf("Device open error!!!\n");
		return -1;
	}

	signal(SIGINT, isQuit_signal);

	while(!isQuit)
	{
		write(fd, &fnd_data, sizeof(fnd_data));
		printf("FND data to be sent to DD: %d\n", fnd_data);
		sleep(1);
		fnd_data = (fnd_data + 1) % 10;
	}

	printf("Program is terminated by sigint signal...\n");
	
	close(fd);
	return 0;
}
