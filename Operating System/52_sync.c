#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t m;
pthread_cond_t c;

void* sunbeam(void *param)
{
	char *s = "SUNBEAM ";
	int i;
	pthread_mutex_lock(&m);
	for(i=0; s[i]!='\0'; i++)
	{
		putchar(s[i]);
		fflush(stdout);
		sleep(1);
	}
	pthread_mutex_unlock(&m);
	pthread_cond_signal(&c);
	return NULL;
}

void* infotech(void *param)
{
	char *s = "INFOTECH";
	int i;
	pthread_mutex_lock(&m);
	pthread_cond_wait(&c, &m);
	for(i=0; s[i]!='\0'; i++)
	{
		putchar(s[i]);
		fflush(stdout);
		sleep(1);
	}
	pthread_mutex_unlock(&m);
	return NULL;
}

int main()
{
	pthread_t st, it;
	pthread_mutex_init(&m, NULL);
	pthread_cond_init(&c, NULL);
	pthread_create(&it, NULL, infotech, NULL);
	pthread_create(&st, NULL, sunbeam, NULL);
	pthread_join(st, NULL);
	pthread_join(it, NULL);
	pthread_mutex_destroy(&m);
	pthread_cond_destroy(&c);
	printf("\n");
	return 0;
}

