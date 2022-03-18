#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// reader
int main()
{
	char buf[40];
	int fd;
	printf("opening pipe.\n");
	fd = open("desd_fifo", O_RDONLY);
	
	read(fd, buf, sizeof(buf));
	printf("read from pipe: %s\n", buf);

	close(fd);
	return 0;
}


