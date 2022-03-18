#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// if param is 3, fibo series: 1 1 2 & sum will be 4.
// if param is 6, fibo series: 1 1 2 3 5 8 & sum will be 20.

void* fibo(void *param)
{
	long cnt = (long)param;
	long sum = 0;
	int a = 1, b = 1, c, i;
	for(i=1; i <= cnt; i++)
	{
	//	printf("%d\n", a);
		sum = sum + a;
		c = a + b;
		a = b;
		b = c;
		sleep(1);
	}
	//return (void*)sum;
	pthread_exit((void*)sum);
}

int main()
{
	pthread_t t1;
	void *res1;
	printf("main started.\n");
	pthread_create(&t1, NULL, fibo, (void*)6L);
	printf("main thread is waiting for t1 thread.\n");
	pthread_join(t1, &res1);	
	printf("result : %ld\n", (long)res1);
	printf("main completed.\n");
	return 0;
}



