#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> 

#define RESPONSE_PLAIN \
    "HTTP/1.1 200 OK\r\n" \
    "Connection: keep-alive\r\n" \
    "Content-Type: text/plain\r\n" \
    "Content-Length: %d\r\n" \
    "\r\n" \
    "%s\n"

//char  *str = "HTTP/1.0 200 OK\r\nServer: BWS/1.0\r\n";
//char *str = RESPONSE_PLAIN;
char buf[128];

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
	
	while(1)
	{
		bzero(buf, sizeof(buf));
		int rdaddrlen;
		rd = accept(sd, (struct sockaddr *)&rdaddr, &rdaddrlen);
		int len = recv(rd, buf, sizeof(buf), 0);
		buf[len] = '\0';
//		printf("%s\n", buf);
		
		char str[128];
		sprintf(str,RESPONSE_PLAIN, len, "data....");
//		char *str = RESPONSE_PLAIN;
		send(rd, str, strlen(str), 0);
		
	}
	
	
	
	return 0;
}
