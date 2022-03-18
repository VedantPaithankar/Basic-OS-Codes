#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	DIR *dp;
	struct dirent *e;
	if(argc != 2)
	{
		fprintf(stderr, "syntax: %s <dir path>\n", argv[0]);
		_exit(1);
	}

	dp = opendir(argv[1]);
	if(dp == NULL)
	{
		perror("opendir() failed");
		_exit(2);
	}

	while( (e = readdir(dp)) != NULL )
	{
		printf("%8ld - %s\n", e->d_ino, e->d_name);
	}

	closedir(dp);
	return 0;
}

