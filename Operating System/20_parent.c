#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
	int pid, s, err;
	printf("parent started!\n");
	pid = fork();
	if(pid == 0)
	{
		char *envps[] = { "INSTITUTE=sunbeam", "COURSE=desd", "BATCH=feb19", NULL };
		err = execle("./19_child.out", "19_child.out", NULL, envps);
		if(err < 0)
		{
			perror("exec() failed");
			_exit(1);
		}
	}
	waitpid(-1, &s, 0);
	printf("child exit stauts : %d\n", WEXITSTATUS(s));
	printf("parent completed!\n");
	return 0;
}

