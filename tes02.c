#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char **argv)
{
	int shmid;
	shmid = shmget(ftok(argv[1], 0), 4096,IPC_CREAT|IPC_EXCL);
	
	char *p;
	p = shmat(shmid, NULL, 0);
	
	strcpy(p, argv[2]);
	shmdt(p);
	
	
	return 0;
}
