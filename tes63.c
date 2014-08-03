#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>

struct mymesg
{
	long mesg_len;
	long mesg_type;
	char mesg_data[100];
};

size_t
msg_send(int id, struct mymesg *mptr)
{
	return (msgsnd(id, &(mptr->mesg_type), mptr->mesg_len, 0));
}

size_t
msg_recv(int id, struct mymesg *mptr)
{
	ssize_t n;
	n = msgrcv(id, &(mptr->mesg_type), 256, mptr->mesg_type, 0);
	mptr->mesg_len = n;

	return (n);
}

int main()
{
	int msgid;
	size_t len;
	char *ptr;
	struct mymesg mesg;
	
	msgid = msgget(43217, 0);
	
	while(1) 
	{
		int n;
		if((n=msg_recv(msgid, &mesg))>0)
			printf("data: %s\n", mesg.mesg_data);
	}
	return 0;
}
