#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
	int pfd[2], ret, pid_wr, pid_rd, s1, s2, err;

	ret = pipe(pfd);
	if(ret < 0)
	{
		perror("pipe() failed");
		_exit(1);
	}

	pid_wr = fork();
	if(pid_wr == 0)
	{	// writer
		close(pfd[0]); // close read end of pipe
		dup2(pfd[1], STDOUT_FILENO); // dup write end of pipe on stdout
		close(pfd[1]); // close write end of pipe

		err = execlp("cal", "cal", NULL);
		if(err < 0)
		{
			perror("exec() failed for writer process");
			_exit(1);
		}
	}
	
	pid_rd = fork();
	if(pid_rd == 0)
	{	// reader
		close(pfd[1]); // close write end of pipe
		dup2(pfd[0], STDIN_FILENO); // dup read end of pipe on stdin
		close(pfd[0]); // close read end of pipe

		err = execlp("wc", "wc", NULL);
		if(err < 0)
		{
			perror("exec() failed for reader process");
			_exit(1);
		}
	}
	
	close(pfd[1]); // close write end of pipe
	close(pfd[0]); // close read end of pipe

	waitpid(pid_wr, &s1, 0);
	waitpid(pid_rd, &s2, 0);
	return 0;
}


