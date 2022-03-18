#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// step1: implement signal handler
void sigint_handler(int sig)
{
	printf("signal handled : %d\n", sig);
}

void sigterm_handler(int sig)
{
	printf("SIGTERM signal caught!\n");
}

int main()
{
	int i = 1;
	// step2: register signal handler
	signal(2, sigint_handler);
	signal(SIGTERM, sigterm_handler);
	while(1)
	{
		printf("running : %d\n", i);
		i++;
		sleep(1);
	}
	return 0;
}


