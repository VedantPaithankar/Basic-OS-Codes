#include <stdio.h>
#include <signal.h>
#include <string.h>

void sigint_handler(int sig)
{
	printf("SIGINT received.\n");
}

int main()
{
	sigset_t set;
	struct sigaction sa;
	
	// register sigint handler
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);

	printf("hi!\n");

	// wait for SIGINT signal.
	sigfillset(&set);
	sigdelset(&set, SIGINT);
	sigsuspend(&set);
	
	printf("bye!\n");
	return 0;
}



