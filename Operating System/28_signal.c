#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void sigint_handler(int sig)
{
	printf("SIGINT received.\n");
}

int main()
{
	sigset_t set;
	struct sigaction sa;
	
	// mask all signals other than SIGINT
	sigfillset(&set);
	sigdelset(&set, SIGINT);
	sigprocmask(SIG_SETMASK, &set, NULL);
	
	// register sigint handler
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);

	while(1)
	{
		printf("running!\n");
		sleep(1);	
	}

	printf("bye!\n");
	return 0;
}



