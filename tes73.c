#include	<stdio.h>
#include	<unistd.h>
#include	<dirent.h>
#include	<limits.h>

#define		bufflen		1024
void server(), client();

char buff[1024];

typedef int pid_t;

int
main(int argc, char **grav)
{
	int	n, pipe1[2], pipe2[2];
	pid_t	childpid;
	
	
	
	if (pipe(pipe1) < 0)
		printf("pipe error\n");
	if (pipe(pipe2) < 0)
		printf("pipe error\n");

	if ( (childpid = fork()) < 0)
		exit(0);
	if (childpid > 0) {
		close(pipe1[0]);
		close(pipe2[1]);
		client(pipe2[0], pipe1[1]);
		waitpid(childpid, NULL, 0);
		exit(0);
	}
	else {
		close(pipe1[1]);
		close(pipe2[0]);
		server(pipe1[0], pipe2[1]);
		exit(0);
	}
}

void
server(int readfd, int writefd)
{
/*	
	bzero(buff, sizeof(buff)); 
	int n;
	if((n = read(readfd, buff, sizeof(buff)))>0)
		printf("ser, buff: %s\n", buff);
*/
	char *str = "server";
	write(writefd, str, strlen(str));
		
}


void
client(int readfd, int writefd)
{
	
	bzero(buff, sizeof(buff));
	int n;
	if((n = read(readfd, buff, sizeof(buff)))>0)
		printf("client, buff: %s\n", buff);
/*	
	char *str = "client";
	write(writefd, str, strlen(str));
*/
}

