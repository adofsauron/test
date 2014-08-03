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
	printf("flag: %d\n", flag);
	flag = listen(sockfd, 5);
	printf("flag: %d\n", flag);
	struct sockaddr_in new_address;


	while(1)
	{
	
		bzero(&new_address, sizeof(new_address));
		int len = sizeof(new_address);
		int new_sockfd = accept(sockfd, (struct sockaddr *)&new_address, &len);

		printf("accept...\n");
		
		close(new_sockfd);
	}
	


	close(sockfd);
	return 0;
}


