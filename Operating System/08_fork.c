#include <stdio.h>
#include <unistd.h>

// concurrent execution of parent and child

int main()
{
	int pid, i;
	printf("program started!\n");
	pid = fork();
	printf("fork() returned : %d\n", pid);
	if(pid == 0)
	{	// child process
		for(i=0; i<30; i++)
		{
			printf("child : %d\n", i);
			sleep(1);
		}
	}
	else
	{	// parent process
		for(i=0; i<30; i++)
		{
			printf("parent : %d\n", i);
			sleep(1);
		}	
	}
	printf("program finished!\n");
	return 0;
}


