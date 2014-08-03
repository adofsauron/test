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
	long len;
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
	
	msg.len = 256;
	msg.mtype = atoi(argv[1]);
	strncpy(msg.buff, argv[2], BUFFER);

	msgsnd(msgid, &msg.mtype, 256, 0);
	
	
	//memset(&msg, '\0', sizeof(struct msgtype));
	//msgrcv(msgid, &msg, sizeof(struct msgtype), 2, 0 );
	
	//fprintf("recv: %s\n", msg.buff);
	
	printf("%d\n", 'a');
	return 0;
}
