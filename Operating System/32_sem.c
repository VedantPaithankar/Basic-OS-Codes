#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEM_KEY 0x2835

union semun 
{
	int val;  
	struct semid_ds *buf;
	unsigned short  *array;
	struct seminfo  *__buf;
};

int main()
{
	int pid, s, i;
	int semid, ret;
	union semun su;
	struct sembuf ops[1];

	// create sema with single cntr.
	semid = semget(SEM_KEY, 1, IPC_CREAT | 0600);
	if(semid < 0)
	{
		perror("semget() failed");
		_exit(1);
	}

	// sem = 0;
	su.val = 0;
	semctl(semid, 0, SETVAL, su);

	pid = fork();
	if(pid == 0)
	{	// child
		char *str = "SUNBEAM ";
		
		// print SUNBEAM
		for(i=0; str[i]!='\0'; i++)
		{
			putchar(str[i]);
			fflush(stdout);
			sleep(1);
		}

		// V(sem);
		ops[0].sem_num = 0;
		ops[0].sem_op = +1;
		ops[0].sem_flg = 0;
		semop(semid, ops, 1);

		// do other task

	}
	else
	{	// parent
		char *str = "INFOTECH";

		// P(sem);
		ops[0].sem_num = 0;
		ops[0].sem_op = -1;
		ops[0].sem_flg = 0;
		semop(semid, ops, 1);

		// print INFOTECH
		for(i=0; str[i]!='\0'; i++)
		{
			putchar(str[i]);
			fflush(stdout);
			sleep(1);
		}

		// do other task

		waitpid(-1, &s, 0);

		// destroy sema
		semctl(semid, 0, IPC_RMID);
		printf("\n");
	}
	return 0;
}
