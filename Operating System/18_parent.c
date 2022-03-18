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
		//// /bin/ls -l -a /home 
		//err = execl("/bin/ls", "ls", "-l", "-a", "/home", NULL);

		//// /usr/bin/cal -y 2020
		//err = execl("/usr/bin/cal", "cal", "-y", "2020", NULL);

		//err = execlp("firefox", "firefox", "http://sunbeaminfo.com", NULL);

		char *args[] = { "firefox", "http://www.kernel.org", NULL };
		err = execvp("firefox", args);
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

