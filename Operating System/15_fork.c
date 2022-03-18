#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// create 3 child processes.
// parent --> child1 --> child2 --> child3
// each child doing different task.

int main()
{
	int i, t, s;
	int pid;

	printf("parent started!\n");

	pid = fork();
	if(pid == 0)
	{
		// child1
		pid = fork();
		if(pid == 0)
		{	// child2
			pid = fork();
			if(pid == 0)
			{	// child3
				// ... child3
				_exit(0);
			}
			// ... child2
			waitpid(-1, &s, 0); // cleanup child3
			_exit(0);
		}
		// ... child1
		waitpid(-1, &s, 0); // cleanup child2
		_exit(0);
	}
	// ... parent
	waitpid(-1, &s, 0); // cleanup child1
	printf("parent completed!\n");
	return 0;
}

