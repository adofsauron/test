#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> 
#include <errno.h>



char str[128];
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
	printf("res: %d, errno: %d\n", res, errno);
	
	sprintf(str, "%s", "send....");
	
	send(sd, str, strlen(str), 0);
	
	return 0;
}
