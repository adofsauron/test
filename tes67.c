#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>

#define SIZE 100
#define file "tmp.ipc"

struct mymsg
{
	long len;
	long type;
	char buff[SIZE];
};

int main(int argc, char **argv)
{
	long len;
	long type;
	key_t key;
	int msgid;
	
	struct mymsg msg;
	
	key = ftok(file, 'a');
	msgid = msgget(key, IPC_CREAT);
	
	while(1)
	{
		fgets(msg.buff, sizeof(msg.buff), stdin);
		msg.len = strlen(msg.buff);
		msg.buff[msg.len] = '\0';
		msg.type = atoi(argv[1]);
		
		msgsnd(msgid, &msg.type, msg.len, 0);
		
		//memset(&msg, 0, sizeof(struct mymsg));
		bzero(msg.buff, sizeof(msg.buff));
	}
	
	return 0;
}
