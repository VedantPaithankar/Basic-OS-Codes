#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t m;
int cnt = 0;

void* incr(void *param)
{
	int i;
	for(i=1; i<=10; i++)
	{
		// lock mutex
		pthread_mutex_lock(&m);
		cnt++;
		printf("incr: %d\n", cnt);
		// unlock mutex
		pthread_mutex_unlock(&m);
		sleep(1);
	}
	return NULL;
}

void* decr(void *param)
{
	int i;
	for(i=1; i<=10; i++)
	{
		// lock mutex
		pthread_mutex_lock(&m);
		cnt--;
		printf("decr: %d\n", cnt);
		// unlock mutex
		pthread_mutex_unlock(&m);
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t it, dt;
	printf("main() started!\n");
	// init mutex
	pthread_mutex_init(&m, NULL);
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




