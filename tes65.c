#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MSG_FILE "tmp.txt"
#define BUFFER 255
#define PERM S_IRUSR|S_IWUSR

struct msgtype
{
	long mtype;
	char buff[BUFFER+1];
};

int main(int argc, char **argv)
{
	struct msgtype msg;

	key_t key;
	int msgid;
	
	key = ftok(MSG_FILE, 'a');
	msgid = msgget(key, IPC_CREAT);
	
	
	while(1)
	{
		int n;
		n =msgrcv(msgid, &msg, 256, atoi(argv[1]), 0);
		if(n>0)
			printf("recv: %s\n", msg.buff);
		//msg.mtype = 2;
		//msgsnd(msgid, &msg, sizeof(struct msgtype), 0);
		//printf("n: %d\n", n);
	}
	return 0;
}

