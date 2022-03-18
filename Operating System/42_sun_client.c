#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERV_ADDR "desd_sock"

// server
int main()
{
	int cfd;
	char buf[64];
	struct sockaddr_un serv_addr;
	socklen_t socklen = sizeof(struct sockaddr_un);
	//4. socket()
	cfd = socket(AF_UNIX, SOCK_STREAM, 0);
	printf("client socket created.\n");

	//5. connect()
	memset(&serv_addr, 0, socklen);
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, SERV_ADDR);
	
	connect(cfd, (struct sockaddr*)&serv_addr, socklen);
	printf("client socket connected to server address.\n");

	do
	{
		//7. write()
		printf("client : ");
		gets(buf);
		write(cfd, buf, strlen(buf) + 1);

		//10. read()
		read(cfd, buf, sizeof(buf));
		printf("server : %s\n", buf);
	}while(strcmp(buf, "bye") != 0);

	//11. close()
	close(cfd);
	return 0;
}


