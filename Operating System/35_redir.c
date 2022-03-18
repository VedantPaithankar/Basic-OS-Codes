#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
	int pid, s, err, fd;
	printf("parent started!\n");
	pid = fork();
	if(pid == 0)
	{
		// output redirection
		fd = open("out.txt", O_WRONLY | O_TRUNC | O_CREAT, 0664);
		close(1); // stdout
		dup(fd);
		close(fd);

		err = execl("./34_div.out", "34_div.out", NULL);
		if(err < 0)
		{
			perror("exec() failed");
			_exit(1);
		}
	}
	waitpid(-1, &s, 0);
	printf("parent completed!\n");
	return 0;
}

