#include <stdio.h>
#include <unistd.h>
int cnt = 0;
int main()
{
	int pid, i;
	pid = fork();
	if(pid == 0)
	{	// child
		for(i=0; i<10; i++)
		{
			cnt--;
			printf("child: %d\n", cnt);
			sleep(1);
		}
	}
	else
	{	// parent
		for(i=0; i<10; i++)
		{
			cnt++;
			printf("parent: %d\n", cnt);
			sleep(1);
		}
	}
	return 0;
}
