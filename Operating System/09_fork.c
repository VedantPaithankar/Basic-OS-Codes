#include <stdio.h>
#include <unistd.h>

// getpid() & getppid()

int main()
{
	int pid;
	printf("program started!\n");
	pid = fork();
	printf("fork() returned : %d\n", pid);
	if(pid == 0)
	{	// child 
		printf("child pid : %d\n", getpid());
		printf("child's parent pid : %d\n", getppid());
	}
	else
	{	// parent
		printf("parent pid : %d\n", getpid());
		printf("parent's parent pid : %d\n", getppid());	
	}
	printf("program finished!\n");
	return 0;
}


