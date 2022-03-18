#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* func1(void *param);
void* func2(void *param);
int main()
{
	int i, ret;
	pthread_t t1, t2;
	ret = pthread_create(&t1, NULL, func1, NULL);
	ret = pthread_create(&t2, NULL, func2, NULL);
	for(i=0; i<60; i++)
	{
		printf("main : %d\n", i);
		sleep(1);
	}
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

// gcc 45_thread.c -o 45_thread.out -lpthread

// gcc 45_thread.c -o 45_thread.out -lpthread

