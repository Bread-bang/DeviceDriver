/* filename: test_virtual_dd.c */
/* PWD = ~/work/dd/iom_virtual_dd */
#include <stdio.h>
#include <fcntl.h> // O_RDWR
#include <unistd.h> // read(), write()
#include <sys/ioctl.h> // ioctl()
#include <string.h> // strerror()
#include <errno.h> // errno

#define DEV_NAME "/dev/iom_virtual_dd"

int main(int argc, char * argv[])
{
	int fd;

	fd = open(DEV_NAME, O_RDWR);
	if ( fd < 0 )
	{
		fprintf(stderr, "%s device file open error!!! %s \n", DEV_NAME, strerror(errno));
		return 0;
	}

	read(fd, 0, 0);
	write(fd, 0, 0);
	ioctl(fd, (int)NULL, 0);
	close(fd);
	
	return 0;
}

