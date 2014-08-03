#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> 

#define RESPONSE_PLAIN \
    "GET / HTTP/1.0\r\n" \
    "Connection: keep-alive\r\n" \
    "Host: www.baidu.comm\r\n" \
    "\r\n" \
    "%s\n"

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
	printf("res: %d\n", res);
	
	sprintf(str, RESPONSE_PLAIN, "send....");
	
	send(sd, str, strlen(str), 0);
	
	bzero(buf, sizeof(buf));
	res = recv(sd, buf, sizeof(buf), 0);
	if(res)
	{
		printf("%s\n", buf);
	}
	return 0;
}
