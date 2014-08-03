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
#include <pthread.h>

#define EVENTS_NOMBER 1024

char recvbuf[1024];
char sendbuf[1024];

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

void *work(void  *fd)
{
		int *retfd = fd;
		bzero(recvbuf, sizeof(recvbuf));
		bzero(sendbuf, sizeof(sendbuf));
		
		int len = recv(*retfd, recvbuf, sizeof(recvbuf), 0);
		printf("recvbuf: %s\n", recvbuf);
		
		sprintf(sendbuf, "len: %d, data:%s\n", len, recvbuf);
		send(*retfd, sendbuf, sizeof(sendbuf), 0);
}

void pth_work(pthread_t *pid,void *fd)
{
	pthread_create(pid, NULL, work, fd);
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

	pthread_t pid;	
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
				//work(&retfd);					
				pth_work(&pid,&retfd);
				pthread_join(pid, NULL);
			}
			else
			{
				//printf("something happen...\n");
			}
		}
	}
	
	
	return 0;
}
