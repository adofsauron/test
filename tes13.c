#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main()
{
	int fd;
	fd = open("fuck.txt", O_RDWR|O_CREAT);
	
	char *str;
	str = "hello world";

	write(fd, str, strlen(str));
	close(fd);
	return 0;
}
