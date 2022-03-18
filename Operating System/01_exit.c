#include <unistd.h>

int main()
{
	//exit(1); // stdlib.h -- C library fn
	_exit(1); // unistd.h -- unix syscall
	return 0;
}


