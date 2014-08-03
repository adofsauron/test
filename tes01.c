#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/ipc.h>


struct person
{
	char *name;
	int age;
};

struct person MyPerson = 
{
	.name = "Jame",
	.age = 19,
};


int main(int argc, char **argv)
{
	int msgid;
	msgid = msgget(ftok("fuck", 0), IPC_CREAT|777);
	
	char *str01 = "the A message.";
	char *str02 = "the B message.";
	char *str03 = "the C message.";
	char buff[1024];
	
	msgsnd(msgid, str01, strlen(str01), 0);
	msgsnd(msgid, str02, strlen(str02), 0);
	msgsnd(msgid, str03, strlen(str03), 0);
	
	int n, i;
	for(i=0; i<3; i++)
	{
		n = msgrcv(msgid, buff, sizeof(buff), 0, 0);
		buff[n] = '\0';
		printf("n:%d buff: %s\n",n,  buff);
	}	
	return 0;
} 

