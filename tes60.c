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
	ssize_t n;
	char *ptr;
	struct mymesg mesg, mesg2;

	msgid = msgget(43217, 0);	

	snprintf(mesg.mesg_data, 100, "say it by %ld", (long)getpid());

	len = strlen(mesg.mesg_data);

	mesg.mesg_len = len;
	mesg.mesg_type = 11;

	msg_send(msgid, &mesg);
	
	
	return 0;
}


