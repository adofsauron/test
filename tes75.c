#include 	<stdlib.h>
#include	<fcntl.h>
#include 	<errno.h>
#include 	<stdio.h>
#include 	<string.h>

#define		LINE			1024

int
main(int  argc, char **argv)
{
	int		readf, writef;

	int flag;
	
	char name[10];
	
	bzero(name, 10);
	snprintf(name, 10, "%ld.txt", (long) getpid());
	name[strlen(name)] = '\0';
		
//	flag =	mkfifo(name,  666 );
//	printf("flag: %d\n", flag);

	writef = open(name, O_WRONLY|O_CREAT);	
	readf = open(name, O_RDONLY|O_CREAT);	
	

	char *buff = argv[1];
	
	flag =  write(writef, buff, strlen(buff));
	printf("flag: %d, %s, %s\n", flag, buff, name);

	char tmp[100];
	int n = read(readf, tmp, sizeof(tmp));
	tmp[n] = '\0';
	printf("tmp:%s\n", tmp);

	
	close(writef);
	close(readf);
	
	execlp("rm", "rm","*txt" );

	return 0;
}
