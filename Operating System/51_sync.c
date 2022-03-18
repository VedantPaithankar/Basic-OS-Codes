#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t m;
int cnt = 0;

void* incr(void *param)
{
	int i, ret;
	for(i=1; i<=10; i++)
	{
		// lock mutex
		ret = pthread_mutex_lock(&m);
		if(ret != 0)
		{
			perror("lock() failed");
			_exit(1);
		}
		cnt++;
		printf("incr: %d\n", cnt);
		// unlock mutex
		ret = pthread_mutex_unlock(&m);
		if(ret != 0)
		{
			perror("lock() failed");
			_exit(1);
		}
		sleep(1);
	}
	return NULL;
}

void* decr(void *param)
{
	int i, ret;
	for(i=1; i<=10; i++)
	{
		// lock mutex
		ret = pthread_mutex_lock(&m);
		if(ret != 0)
		{
			perror("lock() failed");
			_exit(1);
		}
		cnt--;
		printf("decr: %d\n", cnt);
		// unlock mutex
		ret = pthread_mutex_unlock(&m);
		if(ret != 0)
		{
			perror("lock() failed");
			_exit(1);
		}
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t it, dt;
	pthread_mutexattr_t ma;
	printf("main() started!\n");
	// init mutex
	pthread_mutexattr_init(&ma);
	//pthread_mutexattr_settype(&ma, PTHREAD_MUTEX_ERRORCHECK);
	//pthread_mutexattr_settype(&ma, PTHREAD_MUTEX_NORMAL);
	pthread_mutexattr_settype(&ma, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m, &ma);
	pthread_create(&it, NULL, incr, NULL);
	pthread_create(&dt, NULL, decr, NULL);
	pthread_join(it, NULL);
	pthread_join(dt, NULL);
	printf("final count : %d\n", cnt);
	// destroy mutex
	pthread_mutex_destroy(&m);
	printf("main() completed!\n");
	return 0;
}




