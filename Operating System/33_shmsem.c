#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#define MAX	10
typedef struct cirque
{
	int arr[MAX];
	int front, rear;
	int cnt;
}cirque_t;

void cq_init(cirque_t *p);
void cq_push(cirque_t *p, int val);
int cq_pop(cirque_t *p);
int cq_empty(cirque_t *p);
int cq_full(cirque_t *p);

#define SHM_KEY	0x2809
int shmid;
cirque_t *ptr;

#define SEM_KEY 0x1602
int semid;
union semun 
{
	int val;  
	struct semid_ds *buf;
	unsigned short  *array;
	struct seminfo  *__buf;
};

void sigint_handler(int sig);

int main()
{
	int pid, num;
	int ret;
	struct sigaction sa;
	unsigned short ivals[] = { MAX, 1, 0 };
	union semun su;
	struct sembuf ops[2];

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	ret = sigaction(SIGINT, &sa, NULL);

	semid = semget(SEM_KEY, 3, IPC_CREAT | 0600);
	su.array = ivals;
	semctl(semid, 0, SETALL, su);

	shmid = shmget(SHM_KEY, sizeof(cirque_t), IPC_CREAT | 0600);
	ptr = (cirque_t*)shmat(shmid, NULL, 0);
	cq_init(ptr);

	pid = fork();
	if(pid == 0)
	{	// child -- consumer
		while(1)
		{
			// P(fil,mut);
			ops[0].sem_num = 2;
			ops[0].sem_op = -1;
			ops[0].sem_flg = 0;
			ops[1].sem_num = 1;
			ops[1].sem_op = -1;
			ops[1].sem_flg = 0;
			semop(semid, ops, 2);

			// remove from shm cq
			num = cq_pop(ptr);
			// print number
			printf("RD : %d\n", num);

			// V(mut,emp);
			ops[0].sem_num = 1;
			ops[0].sem_op = +1;
			ops[0].sem_flg = 0;
			ops[1].sem_num = 0;
			ops[1].sem_op = +1;
			ops[1].sem_flg = 0;
			semop(semid, ops, 2);
			sleep(1);
		}
	}
	else
	{	// parent -- producer
		while(1)
		{
			// P(emp,mut);
			ops[0].sem_num = 0;
			ops[0].sem_op = -1;
			ops[0].sem_flg = 0;
			ops[1].sem_num = 1;
			ops[1].sem_op = -1;
			ops[1].sem_flg = 0;
			semop(semid, ops, 2);

			// produce random number
			num = rand() % 100;
			// add into shm cq
			cq_push(ptr, num);
			printf("WR : %d\n", num);

			// V(mut,fil);
			ops[0].sem_num = 1;
			ops[0].sem_op = +1;
			ops[0].sem_flg = 0;
			ops[1].sem_num = 2;
			ops[1].sem_op = +1;
			ops[1].sem_flg = 0;
			semop(semid, ops, 2);
			sleep(1);
		}
	}
	return 0;
}

void cq_init(cirque_t *p)
{
	memset(p, 0, sizeof(cirque_t));
	p->cnt = 0;
	p->front = -1;
	p->rear = -1;
}
void cq_push(cirque_t *p, int val)
{
	p->rear = (p->rear + 1) % MAX;
	p->arr[p->rear] = val;
	p->cnt++;
}
int cq_pop(cirque_t *p)
{
	int val;
	p->front = (p->front + 1) % MAX;
	val = p->arr[p->front];
	p->cnt--;
	return val;
}
int cq_empty(cirque_t *p)
{
	return p->cnt == 0 ? 1 : 0;
}
int cq_full(cirque_t *p)
{
	return p->cnt == MAX ? 1 : 0;
}


void sigint_handler(int sig)
{
	// release shm
	shmdt(ptr);
	shmctl(shmid, IPC_RMID, NULL);
	// release sema
	semctl(semid, 0, IPC_RMID);
	printf("bye!\n");
	_exit(0);
}

