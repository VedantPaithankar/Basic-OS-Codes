#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// writer
int main()
{
	char buf[40];
	int fd;
	fd = open("desd_fifo", O_WRONLY);
	
	printf("wr: enter a string: ");
	gets(buf);

	write(fd, buf, strlen(buf)+1);

	close(fd);
	return 0;
}


