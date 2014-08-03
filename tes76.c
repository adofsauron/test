#include	<stdlib.h>
#include 	<stdio.h>
#include	<unistd.h>
#include	<errno.h>
#include	<sys/stat.h>
#include	<fcntl.h>

#define		LINE	1024
#define 	FILE_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define		SERV_FIFO  "/tmp/fifo.serv"
int
main()
{
	int	readf, writef;
	size_t	len;
	size_t	n;
	char	*ptr, fifoname[LINE], buff[LINE], tmp[LINE];
	pid_t	pid;

	pid = getpid();
	snprintf(fifoname, sizeof(fifoname), "tmp/fifo.%d", (long)pid);
	
	if ((mkfifo(fifoname, FILE_MODE) < 0) && (errno != EEXIST))
		printf("can't create %s", fifoname);

	snprintf(buff, sizeof(buff), "%ld", (long)pid);
	len = strlen(buff);
	ptr = buff + len;
	fgets(ptr, LINE - len, stdin);
	len = strlen(buff);
	
	printf("buf: %s\n", buff);
	
	writef = open(SERV_FIFO, O_WRONLY|O_CREAT, 0);
	int flag = write(writef, buff, len);
	printf("flag: %d\n", flag);
	close(writef);
	
	
	readf = open(SERV_FIFO, O_RDONLY|O_CREAT, 0);
	n = read(readf, tmp, LINE);
//	printf("tmp: %s, %d\n", tmp, n);
	write(STDOUT_FILENO, tmp, n);
	
	
	close(readf);
	unlink(fifoname);
	
	exit(0);
}
