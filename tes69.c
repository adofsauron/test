#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

#define file "./tmp.txt"

int main(int argc, char **argv)
{
	char *p, *c;
	int shmid;
	key_t key;
	
	key = ftok(file, 'a');
	shmid = shmget(key, 1024, IPC_CREAT);
	
	while(1)
	{
		p = shmat(shmid, 0, 0);
		memset(p, '\0', 1024);
		fgets(p, 1024, stdin);
		
		c = shmat(shmid, 0, 0);
		printf("c_data: %s\n", c);
		
		
		printf("IPC_CREAT: %x\n", IPC_CREAT);
		printf("p:%ld\nc:%ld\n", p, c);
	
	}	
	
	
	return 0;
}
