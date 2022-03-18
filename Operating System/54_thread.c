#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

void* func1(void *param);
void* func2(void *param);
int main()
{
	int i, ret;
	pthread_t t1, t2;
	ret = pthread_create(&t1, NULL, func1, NULL);
	ret = pthread_create(&t2, NULL, func2, NULL);
	printf("t1 id : %ld\n", t1);
	printf("t2 id : %ld\n", t2);
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
	pthread_t ptid = pthread_self();
 	int tid = syscall(__NR_gettid);
	printf("T1 : POSIX id = %ld, Thread id = %d\n", ptid, tid);
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
	pthread_t ptid = pthread_self();
 	int tid = syscall(__NR_gettid);
	printf("T2 : POSIX id = %ld, Thread id = %d\n", ptid, tid);
	for(i=0; i<60; i++)
	{
		printf("func2: %d\n", i);
		sleep(1);
	}
	return NULL;
}
