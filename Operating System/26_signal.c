#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void sigint_handler(int sig, siginfo_t *si, void *param)
{
	printf("SIGINT sender=%d, cur process=%d.\n", si->si_pid, getpid());
}

int main()
{
	int i = 1, ret;
	struct sigaction sa1, sa2;
	printf("main process pid : %d\n", getpid());
	
	memset(&sa2, 0, sizeof(sa2));
	memset(&sa1, 0, sizeof(sa1));
	sa1.sa_sigaction = sigint_handler;
	sa1.sa_flags = SA_SIGINFO;
	ret = sigaction(SIGINT, &sa1, &sa2);
	if(ret < 0)
	{
		perror("sigaction() failed");
		_exit(1);
	}
	
	while(1)
	{
		printf("running : %d\n", i);
		i++;
		sleep(1);
	}
	return 0;
}


