#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> 
#include <errno.h>



//char str[128];
char buf[128];

int main(int argc, char **argv)
{
	int  sd;
	struct sockaddr_in sdaddr;
	
	sd = socket(AF_INET, SOCK_STREAM, 0);
	sdaddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &sdaddr.sin_addr);
	sdaddr.sin_port = atoi(argv[2]);
	
	int res = connect(sd, (struct sockaddr *)&sdaddr, sizeof(sdaddr));
	printf("res: %d, errno: %d, %s\n", res, errno, strerror(errno));
	
	//sprintf(str, "%s", "send....");
	
	char *str = "send...";
	
	
	send(sd, str, strlen(str), 0);
	printf(str);
	
	bzero(buf, sizeof(buf));
	res = recv(sd, buf, sizeof(buf), 0);
	printf("res: %d\n", res);
	
	printf(buf);
	
	return 0;
}
