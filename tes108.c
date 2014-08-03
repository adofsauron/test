#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> 
#include <sys/epoll.h>
#include <fcntl.h>

#define EVENTS_NOMBER 1024

int setNoneBlocking(int fd)
{
	int old = fcntl(fd, F_GETFL);
	int new = old|O_NONBLOCK;
	fcntl(fd, F_SETFL, new);
	return old;
}

void addfd(int epollfd, int fd)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setNoneBlocking(fd);
}

int main(int argc, char **argv)
{
	int sd, rd;
	struct sockaddr_in addr, rdaddr;
	struct hostent *h;
	
	sd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	char *ip = argv[1];
	inet_pton(AF_INET, ip, &addr.sin_addr);
	addr.sin_port = atoi(argv[2]);

	
	int res = bind(sd, (struct sockaddr *)&addr, sizeof(addr));
	printf("res: %d\n", res);
	
	listen(sd, 5);
	
	struct epoll_event events[EVENTS_NOMBER];
	int epollfd = epoll_create(5);
	
	addfd(epollfd, sd);
	/*
	while(1)
	{
		char buf[128];
		bzero(buf, sizeof(buf));
		int rdaddrlen;
		rd = accept(sd, (struct sockaddr *)&rdaddr, &rdaddrlen);
		int len = recv(rd, buf, sizeof(buf), 0);
		buf[len] = '\0';
		printf("%s\n", buf);
		
		char str[128];
//		sprintf(str,RESPONSE_PLAIN, len, "data....");
//		char *str = RESPONSE_PLAIN;
		send(rd, str, strlen(str), 0);
		printf(str);
		
	}
	*/
	
	char recvbuf[1024];
	char sendbuf[1024];
	while(1)
	{
		bzero(recvbuf, sizeof(recvbuf));
		bzero(sendbuf, sizeof(sendbuf));
		
		int ret = epoll_wait(epollfd, events, EVENTS_NOMBER, -1);
		int i;
		for(i=0;i<ret; i++)
		{
			int retfd = events[i].data.fd;
			
			if(retfd==sd)
			{
				struct sockaddr_in client_address;
				socklen_t client_addrlength = sizeof(client_address);
				int connfd = accept(sd, (struct sockaddr*)&client_address, &client_addrlength);
				addfd(epollfd, connfd);
			}
			else if(events[i].events == EPOLLIN)
			{
				bzero(recvbuf, sizeof(recvbuf));
				bzero(sendbuf, sizeof(sendbuf));
				
				int len = recv(retfd, recvbuf, sizeof(recvbuf), 0);
				printf("recvbuf: %s\n", recvbuf);
				
				sprintf(sendbuf, "len: %d, data:%s\n", len, "send...");
				send(retfd, sendbuf, sizeof(sendbuf), 0);
			}
			else
			{
				//printf("something happen...\n");
			}
		}
	}
	
	
	return 0;
}
