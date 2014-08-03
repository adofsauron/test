#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/eventfd.h>

//#include <unistd.h>
 
//#define HIDDEN   

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

#define RESPONSE_PLAIN \
    "HTTP/1.1 200 OK\r\n" \
    "Connection: keep-alive\r\n" \
    "Content-Type: text/plain\r\n" \
    "Content-Length: %d\r\n" \
    "\r\n" \
    "%s\n"


#define  MAXSIZE   1024*4
char back[MAXSIZE];
char buf[MAXSIZE];

int save(char *msg)
{
	int  fd = open("log.txt", O_RDWR|O_CREAT|O_APPEND);
	write(fd, msg, sizeof(msg));
	close(fd);
}

int main(int argc, char **argv)
{
	if(argc<3)
	{
		printf("error!\n");
		exit(0);
	}
	
	struct epoll_event events[1024];
	int epollfd = epoll_create(5);
	

	char *ip = argv[1];
	int port = atoi(argv[2]);
		
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in  address;
	bzero(&address, sizeof(address));

	address.sin_family = AF_INET;
	inet_pton(AF_INET,ip, &address.sin_addr );
	address.sin_port = htons(port);

	int flag;
	
	flag = bind(sockfd, (struct sockaddr *)&address, sizeof(address));
	printf("flag: %d\n", flag);
	flag = listen(sockfd, 5);
	printf("flag: %d\n", flag);
	struct sockaddr_in new_address;

	addfd(epollfd,sockfd );

	
	while(1)
	{
		int ret = epoll_wait(epollfd, events, 1024, -1);
		int i;
		for(i=0; i<ret; i++)
		{
			int retfd = events[i].data.fd;
			if(retfd==sockfd)
			{
				struct sockaddr_in client_address;
				socklen_t client_addrlength = sizeof(client_address);
				int connfd = accept(sockfd, (struct sockaddr*)&client_address, &client_addrlength);
				addfd(epollfd, connfd);
			}
			else if(events[i].events == EPOLLIN)
			{
				bzero(back, sizeof(back));
				bzero(buf, sizeof(buf));
		
				int size = recv(retfd, buf, sizeof(buf), 0);
				buf[size] = '\0';

//				save(buf);
				printf("%s\n", buf);

				printf("size: %d\n\r\n", size);

				sprintf(back, "size: %d, value: %s\n\r\n", size, "data....");
			
				send(retfd, back, strlen(back), 0);

				close(retfd);
				
			}
			else
			{
				printf("something  happen...\n");
			}
		}
	} 
	
	close(sockfd);
	return 0;
}


