#include <stdio.h>
#include <unistd.h>

// child -- orphan process

int main()
{
	int pid, i;
	pid = fork();
	if(pid == 0)
	{	// child
		for(i=1; i<=30; i++)
		{
			printf("child : %d\n", i);
			sleep(1);
		}
	}
	else
	{	// parent
		for(i=1; i<=15; i++)
		{
			printf("parent : %d\n", i);
			sleep(1);
		}	
	}
	return 0;
}


