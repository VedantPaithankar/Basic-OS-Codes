#include <stdio.h>
#include <unistd.h>

int main()
{
	int i = 1;
	while(1)
	{
		printf("running : %d\n", i);
		i++;
		sleep(1);
	}
	return 0;
}


