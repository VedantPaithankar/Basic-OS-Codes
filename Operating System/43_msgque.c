#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MQ_KEY	0x2132

#define MSG_SIZE 32

typedef struct msg
{
	long type;
	char data[MSG_SIZE];
}msg_t;

int main()
{
	int pid, mq_id, s;

	mq_id = msgget(MQ_KEY, IPC_CREAT | 0600);

	pid = fork();
	if(pid == 0)
	{	// child -- sender
		msg_t m1;
		printf("child: enter data : ");
		gets(m1.data);
		m1.type = 101;
		msgsnd(mq_id, &m1, MSG_SIZE, 0);
	}
	else
	{	// parent -- receiver
		msg_t m2;
		printf("parent: waiting for message.\n");
		msgrcv(mq_id, &m2, MSG_SIZE, 101, 0);
		printf("parent: msg received : %s\n", m2.data);

		waitpid(-1, &s, 0);
	}
	return 0;
}

