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
		//err = execl("./16_child.out", "16_child.out", "ek", "do", "teen", NULL);

		char *args[] = { "16_child.out", "ek", "do", "teen", NULL };
		err = execv("./16_child.out", args);
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

