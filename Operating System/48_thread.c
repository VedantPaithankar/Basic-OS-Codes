#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// race condition
// may get unexpected result

int cnt = 0;

void* incr(void *param)
{
	int i;
	for(i=1; i<=10; i++)
	{
		cnt++;
		printf("incr: %d\n", cnt);
		sleep(1);
	}
	return NULL;
}

void* decr(void *param)
{
	int i;
	for(i=1; i<=10; i++)
	{
		cnt--;
		printf("decr: %d\n", cnt);
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t it, dt;
	printf("main() started!\n");
	pthread_create(&it, NULL, incr, NULL);
	pthread_create(&dt, NULL, decr, NULL);
	pthread_join(it, NULL);
	pthread_join(dt, NULL);
	printf("final count : %d\n", cnt);
	printf("main() completed!\n");
	return 0;
}




