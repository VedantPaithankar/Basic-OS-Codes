#include <stdio.h>
#include <unistd.h>

/*
	pipe() return two fds via out param.
		fd[0] -- read end of pipe
		fd[1] -- write end of pipe
*/
int main()
{
	int fd[2], ret;
	char buf[20];

	ret = pipe(fd);
	if(ret < 0)
	{
		perror("pipe() failed");
		_exit(1);
	}

	write(fd[1], "hello desd!\n", 13);
	read(fd[0], buf, sizeof(buf));
	printf("read from pipe : %s\n", buf);

	close(fd[1]);
	close(fd[0]);
	return 0;
}






