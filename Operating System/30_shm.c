#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_KEY	0x8324

int main()
{
	int pid, i, shmid, s;
	int *ptr;

	// create shm obj
	shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0600);
	if(shmid < 0)
	{
		perror("shmget() failed");
		_exit(1);
	}

	// get ptr to shm rgn
	ptr = (int*) shmat(shmid, NULL, 0);
	if(ptr == (void*)-1)
	{
		perror("shmat() failed");
		_exit(2);
	}
	*ptr = 0;

	// create child process
	pid = fork();
	// child process will have shmid & ptr to shm rgn (copy from parent).
	if(pid == 0)
	{	// child
		for(i=0; i<10; i++)
		{
			(*ptr)--;
			printf("child: %d\n", *ptr);
			sleep(1);
		}
		// release shm rgn ptr from child
		shmdt(ptr);
	}
	else
	{	// parent
		for(i=0; i<10; i++)
		{
			(*ptr)++;
			printf("parent: %d\n", *ptr);
			sleep(1);
		}
		// wait for completion of child
		waitpid(-1, &s, 0);
		printf("final count : %d\n", *ptr);
		// release shm rgn ptr from parent
		shmdt(ptr);
		// destroy shm rgn/obj
		shmctl(shmid, IPC_RMID, NULL);
	}
	return 0;
}

