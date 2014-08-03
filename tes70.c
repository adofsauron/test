#include <unistd.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	int pipek[2];
	int fd;

	char buff[256];
	pipe(pipek);

	fd = fork();

	if(fd>0)
	{
		close(pipek[0]);
		int i;
		char str[1024];

		printf("father: %d\n", getpid());
		for(i=1; i<argc; i++)
		{	
			strcpy(str, argv[i]);
			printf("befor: %d\n", strlen(str));
			str[strlen(str)] = '\t';
			printf("after: %d\n", strlen(str));
			write(pipek[1], str, strlen(str));
			bzero(str, sizeof(str));	
		}
	}
	else if(fd==0)
	{
		close(pipek[1]);
		
		printf("child: %d\n", getpid());
		int n=read(pipek[0],buff, sizeof(buff));
		
		buff[n] = '\0';
		printf("buf: %s\n", buff);
		exit(0);
	}

	wait(0);
	printf("flag: %d\n", getpid());
//	wait(0);
	return 0;
}
