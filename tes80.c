#include <stdio.h>
#include <string.h>

#define JSONP_RESPONSE_PLAIN \
    "HTTP/1.1 200 OK\r\n" \
    "Connection: keep-alive\r\n" \
    "Content-Type: application/x-javascript; charset=utf-8\r\n" \
    "X-XSS-Protection: 0\r\n" \
    "Content-Length: %d\r\n" \
    "\r\n" \
    "%s\n"

int main()
{
	char headStr[250] = "abcdefg\n";

    strcat(headStr, "HTTP/1.1 200 OK\r\n");

    strcat(headStr, "Content-Type: application/x-javascript; charset=utf-8\r\n");

    strcat(headStr, "Connection: keep-alive\r\n");

    strcat(headStr, "X-XSS-Protection: 0\r\n");

    strcat(headStr, "\r\n");

	//printf("%s", JSONP_RESPONSE_PLAIN);
	
	char *test = "abcd\r\nefg";

	printf("%s\n", test);
	return 0;
}
