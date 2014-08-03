#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 80
#define SERV_PORT 1234

int main()
{
	const char *ip = "127.0.0.1";
	
	struct sockaddr_in seraddr, cliaddr;
	
	socklen_t cliaddr_len;
	int listenfd, connfd;
	char buff[MAXLINE];
	char str[INET_ADDRSTRLEN];
	
	int i, n;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&seraddr, sizeof(seraddr));
	
	seraddr.sin_family = AF_INET;
//	seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, ip, &seraddr.sin_addr);
	seraddr.sin_port = htons(SERV_PORT);
	
	bind(listenfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
	
	listen(listenfd, 20);
	printf("begin acceptting...\n");
	
	while(1)
	{
		cliaddr_len = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
		
		recvfrom(connfd, buff, sizeof(buff), 0, NULL, NULL);
		printf("%s\n", buff);
		
		close(connfd);
	}
	
	close(listenfd);
	return 0;
}
