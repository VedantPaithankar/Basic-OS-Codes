#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fd[2], ret, pid;

	ret = pipe(fd);
	if(ret < 0)
	{
		perror("pipe() failed");
		_exit(1);
	}

	pid = fork();
	if(pid == 0)
	{	// child -- writer
		char buf1[40];
		close(fd[0]); // close read end
		printf("child: enter a string : ");
		gets(buf1);
		write(fd[1], buf1, strlen(buf1)+1); // write into pipe
		close(fd[1]);
	}
	else
	{	// parent -- reader
		char buf2[40];
		close(fd[1]); // close write end
		read(fd[0], buf2, sizeof(buf2)); // read from pipe
		printf("parent: read from pipe : %s\n", buf2);
		close(fd[0]);
	}
	return 0;
}


