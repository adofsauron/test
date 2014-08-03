#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 80
#define PORT 1234


int main(int argc, char **argv)
{
	const char *ip = "127.0.0.1";
	
	struct sockaddr_in seraddr;
	char buf[MAXLINE];
	int sockfd, n;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	seraddr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &seraddr.sin_addr);
	seraddr.sin_port = htons(PORT);

	connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));

	char *str = argv[1];
	strcpy(buf, str);

	sendto(sockfd, buf, sizeof(buf), 0, NULL, NULL);	
	close(sockfd);
	return 0;
}
