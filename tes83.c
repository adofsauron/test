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
	
	ret = connect(listenfd, (struct sockaddr *)&address, sizeof(address));
	
	char str[1024];
	while(1)
	{
		memset(str, '\0', sizeof(str));
		scanf("%s", str);
		send(listenfd, str, strlen(str), 0);
	}
	
	close(listenfd);
	return 0;
}
