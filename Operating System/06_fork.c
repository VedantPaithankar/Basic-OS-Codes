#include <stdio.h>
#include <unistd.h>

int main()
{
	int pid;
	printf("program started!\n");
	pid = fork();
	printf("fork() returned : %d\n", pid);
	printf("program finished!\n");
	return 0;
}


