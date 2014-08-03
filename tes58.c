#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	char *file[100];

	snprintf(file, 100, "./%ld.txt", (long)getpid());
	int flag = mkfifo(file, 666);

	int fd = open(file, O_RDWR);

	write(fd, argv[2], strlen(argv[2]));

	char buf[100];
	read(fd, buf, sizeof(buf));
	
	printf("buf: %s\n", buf);
		
	close(fd);

	unlink(file);
	return 0;
}
