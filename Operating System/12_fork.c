#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// avoid zombie -- wait() syscall

int main()
{
	int pid, i, s;
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
			if(i == 15)
			{
				wait(&s);
				printf("child exit : %d\n", WEXITSTATUS(s));
			}
		}	
	}
	return 0;
}


