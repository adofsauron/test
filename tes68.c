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
	
	msg.type = atoi(argv[1]);
	
	while(1)
	{
		int n;
		n = msgrcv(msgid, &msg.type, sizeof(msg.buff), msg.type, 0);
		msg.buff[n] = '\0';
		printf("n: %d\tbuff: %s\n", n, msg.buff);
		
		memset(msg.buff, 0, sizeof(msg.buff));
	}
	
	return 0;
}
