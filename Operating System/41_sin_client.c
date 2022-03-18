#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define SERV_ADDR "127.0.0.1"
#define SERV_PORT 2809

// server
int main()
{
	int cfd;
	char buf[64];
	struct sockaddr_in serv_addr;
	socklen_t socklen = sizeof(struct sockaddr_in);
	//4. socket()
	cfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("client socket created.\n");

	//5. connect()
	memset(&serv_addr, 0, socklen);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_aton(SERV_ADDR, &serv_addr.sin_addr);
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


