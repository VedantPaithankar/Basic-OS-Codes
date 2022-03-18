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
	int mfd, cfd;
	char buf[64];
	struct sockaddr_un serv_addr, cli_addr;
	socklen_t socklen = sizeof(struct sockaddr_un);
	//1. socket()
	mfd = socket(AF_UNIX, SOCK_STREAM, 0);
	printf("server socket created.\n");

	//2. bind()
	memset(&serv_addr, 0, socklen);
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, SERV_ADDR);
	bind(mfd, (struct sockaddr*)&serv_addr, socklen);
	printf("server socket bind to address.\n");

	//3. listen()
	listen(mfd, 5);

	printf("server waiting for client connection.\n");
	//6. accept()
	memset(&cli_addr, 0, socklen);
	cfd = accept(mfd, (struct sockaddr*)&cli_addr, &socklen);
	printf("client connection accepted.\n");

	do
	{
		//8. read()
		read(cfd, buf, sizeof(buf));
		printf("client : %s\n", buf);

		//9. write()
		printf("server : ");
		gets(buf);
		write(cfd, buf, strlen(buf) + 1);
	}while(strcmp(buf, "bye") != 0);

	//12. close()
	close(cfd);

	//13. shutdown()
	shutdown(mfd, SHUT_RDWR);
	return 0;
}


