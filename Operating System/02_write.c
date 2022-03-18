#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("hello world!\n");

	fprintf(stdout, "hello world!\n");
	
	fprintf(stderr, "hello world!\n");

	write(1, "hello world!\n", 13);
	return 0;
}
