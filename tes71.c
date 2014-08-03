#include <unistd.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define  file  "tmp.txt"

int main(int argc, char **argv)
{
	int fd;
	fd = fork();
	
	char *r, *w;	
	int shmid;
	shmid = shmget(ftok(file, 0), 1024, IPC_CREAT);

	char str[1024];

	if(fd>0)
	{
		w = shmat(shmid, 0, 0);
		int i;
		for(i=1;  i<argc; i++)
		{
			bzero(str, sizeof(str));
			
			strcpy(str, argv[i]);
			str[strlen(str)] = '\t';

			strcpy(w, str);
			w = w+strlen(w);
		}
	}
	else if(fd==0)
	{
		r = shmat(shmid, 0, 0);
		printf("r: %s\n",r);
		exit(0);
	}

	wait(0);
	return 0;
}
