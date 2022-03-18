#include <stdio.h>
#include <unistd.h>

int main()
{
	// 	|
	fork();
	//	|	|
	fork();
	//	| |	| |
	fork();
	//	||||||||
	printf("god bless you!\n");
	return 0;
}


