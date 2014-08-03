#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h> 
#include <stdlib.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

int setnon(int fd)
{
	int old = fcntl(fd, F_GETFL);
	int new = old|O_NONBLOCK;
	fcntl(fd, F_SETFL, new);
	return old;
}

int main(int argc, char **argv)
{
	if(argc<3)
	{
		printf("tes82.bin <ip> <port>\n");
		exit(0);
	}
	
	const char *ip = argv[1];
	int port = atoi(argv[2]);
	
	int ret=0;
	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET, ip, &address.sin_addr);
	
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
//	setnon(listenfd);
	
	ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
	ret = listen(listenfd, 5);
	
	struct sockaddr_in client_addr;
	int client_length = sizeof(client_addr);
	
//	int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_length);

	
	
	char buf[1024];
	fd_set read_fds;
	fd_set exception_fds;
	FD_ZERO(&read_fds);
	FD_ZERO(&exception_fds);
	
	int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_length);
	
	setnon(connfd);
	
//	printf("before while....\n");
	while(1)
	{
//		printf("before accept...\n");
//		int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_length);
//		printf("after acccept...\n");
	
		
		memset(buf, '\0', sizeof(buf));
		
		FD_SET(connfd, &read_fds);
		FD_SET(connfd, &exception_fds);
		
		ret = select(connfd+1, &read_fds, NULL, &exception_fds, NULL);
		
		if(FD_ISSET(connfd, &read_fds))
		{
			ret = recv(connfd, buf, sizeof(buf)-1, 0);
			printf("buf: %s\n", buf);
		}
		else if(FD_ISSET(connfd, &exception_fds))
		{
			printf("exception");
		}
		
		
	}
	close(connfd);
	
	close(listenfd);
	return 0;
}
