#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <unistd.h>

#define  MAXSIZE   1024*4
 
int getfd(char *name); 
int readio(int fd, char *back);
char *getpath(char *src, char *path);

int main(int argc, char **argv)
{
	if(argc<3)
	{
		printf("error!\n");
		exit(0);
	}

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

	flag = listen(sockfd, 5);

	struct sockaddr_in new_address;

	char buf[MAXSIZE];
	
	char *str = "fuck you!";
	char back[MAXSIZE];
	
	int n=0;
	while(1)
	{
		int len = sizeof(new_address);
		int new_sockfd = accept(sockfd, (struct sockaddr *)&new_address, &len);

		int size = recv(new_sockfd, buf, sizeof(buf), 0);
		buf[size] = '\0';
		int x = n++;
		printf("[%d]start---------------------------------------------------------------------------\n\n\n", x);
		printf("buf: %s\n", buf);
		char remote[INET_ADDRSTRLEN];
		char *new_ip;
		new_ip = inet_ntop(AF_INET, &new_address.sin_addr, remote, INET_ADDRSTRLEN);
		printf("new_ip: %s\n", new_ip);
		printf("new_port: %d\n", ntohs(new_address.sin_port));
		
		printf("[%d]over---------------------------------------------------------------------------\n\n\n", x);
		
		bzero(back, sizeof(back));
		char path[128];
		bzero(path, sizeof(path));
		getpath(buf, path);
		if(strcmp(path, "favicon.ico") == 0)
		{
				continue;
		}
		
		int fd = getfd(path);
		if(fd<0)
		{
				strcpy(back, "no this page!!!"); 
		}
		else
		{
			readio(fd, back);
		}
	//	sprintf(back, "[%d], %s", x, buf);
		write(new_sockfd, back, strlen(back));
		close(new_sockfd);
		printf("path: %s\n", path);
	}
//	printf("flag: %d\n", flag);
	
	close(flag);
	return 0;
}


int getfd(char *name)
{
	int fd;
	fd = open(name, O_RDONLY);
	return fd;
}

int readio(int fd, char *back)
{
	
		char buff[MAXSIZE];
		bzero(buff, sizeof(buff));
		int n = read(fd, buff, sizeof(buff));
		
		strncpy(back, buff, n);
		close(fd);
		
		return n;
		
		
}



char *getpath(char *src, char *path)
{
		char *p = strchr(src, '/');
		p++;
		char *end = strchr(p, ' ');
		int n = end-p;
		
		
		strncpy(path, p, n);
		
		return path;
		
}
