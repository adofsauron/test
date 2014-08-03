#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char **argv)
{
	int shmid;
	shmid = shmget(ftok(argv[1], 0), 0, 0);
	char *p;
	p = shmat(shmid, NULL, 0);
	
	printf("p: %s\n", p);
	return 0;
}
