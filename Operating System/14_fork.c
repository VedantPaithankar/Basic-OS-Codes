#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// create 5 child processes from single parent.
// each child doing same task -- count 1, 2, 3.

int main()
{
	int i, t, s;
	int pid[5];

	printf("parent started!\n");

	for(i=0; i<5; i++)
	{
		pid[i] = fork();
		if(pid[i] == 0)
		{	// i'th child process
			for(t=1; t<=3; t++)
			{
				printf("child%d -- %d\n", i, t);
				sleep(1);
			}
			_exit(0);
		}
	}

	for(i=0; i<5; i++)
		waitpid(pid[i], &s, 0);
	
	printf("parent completed!\n");
	return 0;
}

