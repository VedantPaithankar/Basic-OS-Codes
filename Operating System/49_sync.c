#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// mutual exclusion using semaphore

sem_t s;
int cnt = 0;

void* incr(void *param)
{
	int i;
	for(i=1; i<=10; i++)
	{
		// P(sem)
		sem_wait(&s);
		cnt++;
		printf("incr: %d\n", cnt);
		// V(sem)
		sem_post(&s);
		sleep(1);
	}
	return NULL;
}

void* decr(void *param)
{
	int i;
	for(i=1; i<=10; i++)
	{
		// P(sem)
		sem_wait(&s);
		cnt--;
		printf("decr: %d\n", cnt);
		// V(sem)
		sem_post(&s);
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t it, dt;
	printf("main() started!\n");
	// create semaphore & init to 1
	sem_init(&s, 0, 1);
	pthread_create(&it, NULL, incr, NULL);
	pthread_create(&dt, NULL, decr, NULL);
	pthread_join(it, NULL);
	pthread_join(dt, NULL);
	printf("final count : %d\n", cnt);
	// destroy semaphore
	sem_destroy(&s);
	printf("main() completed!\n");
	return 0;
}




