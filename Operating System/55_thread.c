#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/syscall.h>

void* func1(void *param);
void* func2(void *param);

void sigint_handler(int sig)
{
	int tid = syscall(__NR_gettid);
	printf("SIGINT caught in thread : %d\n", tid);
	if(tid != getpid())
		pthread_exit(NULL);
}

int main()
{
	int i, ret;
	pthread_t t1, t2;
	struct sigaction sa;
	// signal handlers are process-wide.
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);

	ret = pthread_create(&t1, NULL, func1, NULL);
	ret = pthread_create(&t2, NULL, func2, NULL);
	printf("press enter to send signal to thread1.\n");
	getchar();
	pthread_kill(t1, SIGINT);
	getchar();
	printf("press enter to exit.\n");
	printf("bye!\n");
	return 0;
}

void* func1(void *param)
{
	int i;
	for(i=0; i<60; i++)
	{
		printf("func1: %d\n", i);
		sleep(1);
	}
	return NULL;
}

void* func2(void *param)
{
	int i;
	for(i=0; i<60; i++)
	{
		printf("func2: %d\n", i);
		sleep(1);
	}
	return NULL;
}


