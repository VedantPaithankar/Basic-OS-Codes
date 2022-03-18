#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* print_table(void *param)
{
	long num = (long)param;
	long i;
	for(i=1; i<=10; i++)
	{
		printf("%ld * %ld = %ld\n", num, i, num * i);
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t t1, t2, t3;
	printf("main() started.\n");
	pthread_create(&t1, NULL, print_table, (void*)11L);
	pthread_create(&t2, NULL, print_table, (void*)23L);
	pthread_create(&t3, NULL, print_table, (void*)27L);
	getchar(); // main will halt here
	printf("main() complted.\n");
	return 0;
}



