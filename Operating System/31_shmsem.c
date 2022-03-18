#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define SHM_KEY	0x8324
#define SEM_KEY 0x2832

union semun 
{
	int val;  
	struct semid_ds *buf;
	unsigned short  *array;
	struct seminfo  *__buf;
};

int main()
{
	int pid, i, shmid, s, semid;
	int *ptr;
	union semun su;
	struct sembuf ops[1];

	// create sema with single counter.
	semid = semget(SEM_KEY, 1, IPC_CREAT | 0600);
	if(semid < 0)
	{
		perror("semget() failed");
		_exit(1);
	}

	// sem = 1.
	su.val = 1;
	semctl(semid, 0, SETVAL, su);

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
			// P(sem);
			ops[0].sem_num = 0;
			ops[0].sem_op = -1;
			ops[0].sem_flg = 0;
			semop(semid, ops, 1);

			(*ptr)--;
			printf("child: %d\n", *ptr);

			// V(sem);
			ops[0].sem_num = 0;
			ops[0].sem_op = +1;
			ops[0].sem_flg = 0;
			semop(semid, ops, 1);
			
			sleep(1);
		}
		// release shm rgn ptr from child
		shmdt(ptr);
	}
	else
	{	// parent
		for(i=0; i<10; i++)
		{
			// P(sem);
			ops[0].sem_num = 0;
			ops[0].sem_op = -1;
			ops[0].sem_flg = 0;
			semop(semid, ops, 1);

			(*ptr)++;
			printf("parent: %d\n", *ptr);

			// V(sem);
			ops[0].sem_num = 0;
			ops[0].sem_op = +1;
			ops[0].sem_flg = 0;
			semop(semid, ops, 1);
			
			sleep(1);
		}
		// wait for completion of child
		waitpid(-1, &s, 0);
		printf("final count : %d\n", *ptr);
		// release shm rgn ptr from parent
		shmdt(ptr);
		// destroy shm rgn/obj
		shmctl(shmid, IPC_RMID, NULL);
		// destroy sema
		semctl(semid, 0, IPC_RMID);
	}
	return 0;
}

