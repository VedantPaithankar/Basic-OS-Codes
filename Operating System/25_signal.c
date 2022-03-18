#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

// avoid zombie -- wait() syscall

void sigchld_handler(int sig)
{
	int s;
	waitpid(-1, &s, 0);
	printf("child exit value = %d\n", WEXITSTATUS(s));
}

int main()
{
	int pid, i, s, ret;
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigchld_handler;
	ret = sigaction(SIGCHLD, &sa, NULL);
	if(ret < 0)
	{
		perror("sigaction() failed");
		_exit(1);
	}

	pid = fork();
	if(pid == 0)
	{	// child
		for(i=1; i<=15; i++)
		{
			printf("child : %d\n", i);
			sleep(1);
		}
		_exit(4);
	}
	else
	{	// parent
		for(i=1; i<=30; i++)
		{
			printf("parent : %d\n", i);
			sleep(1);
		}	
	}
	return 0;
}


