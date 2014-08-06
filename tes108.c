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

struct recv
{
	char header[256];
	char data[1024];
};

struct sock_operations
{
	int (*get_sockfd)(const char *domain, int port);
	int (*setNoneBlocking)(int fd);
	void (*add_eventfd)(int epollfd, int fd);
	void *(*work)(void *fd);
	void (*pth_work)(pthread_t *pid,void *fd);
	
};

struct  Recv_sock
{
	struct recv recvdata;
	struct sock_operations operations;
};


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

int get_sockfd(const char *domain, int port)
{
	int sd;
	struct sockaddr_in addr;
	
	sd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	const char *ip = domain;
	inet_pton(AF_INET, ip, &addr.sin_addr);
	addr.sin_port = port;	
	int res = bind(sd, (struct sockaddr *)&addr, sizeof(addr));
	
	sd = res>=0?sd:-1;
	
	return sd;
	
}

struct sock_operations  operations = 
{
	.get_sockfd =  get_sockfd,
	.setNoneBlocking = setNoneBlocking,
	.add_eventfd = addfd,
	.work = work,
	.pth_work = pth_work
};

struct  Recv_sock * init(void)
{
	struct  Recv_sock *recv_sock = (struct Recv_sock *) malloc (sizeof(struct Recv_sock));
	recv_sock->operations = operations;
	
	return recv_sock=recv_sock==NULL?NULL:recv_sock;
}

int main(int argc, char **argv)
{
	struct Recv_sock *recv_sock = init();
	
	int sd, rd;
	
	sd = recv_sock->operations.get_sockfd(argv[1], atoi(argv[2]));
	
	printf("sd: %d\n", sd);
	
	listen(sd, 5);
	
	struct epoll_event events[EVENTS_NOMBER];
	int epollfd = epoll_create(5);
	
	recv_sock->operations.add_eventfd(epollfd, sd);

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
				recv_sock->operations.add_eventfd(epollfd, connfd);
			}
			else if(events[i].events == EPOLLIN)
			{
				recv_sock->operations.pth_work(&pid,&retfd);
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
