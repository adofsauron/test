#include	<sys/msg.h>
#include	<sys/ipc.h>
#include	<stdio.h>

#define MAXMESGDATA     1000
#define SVMSG_MODE      777

struct mymesg {
        long        mesg_len;       /* #bytes in mesg_data, can be 0 */
        long        mesg_type;      /* message type, must be > 0 */
        char        mesg_data[MAXMESGDATA];
};

	
size_t
msg_send(int id, struct mymesg *mptr)
{
	        return(msgsnd(id, &(mptr->mesg_type), mptr->mesg_len, 0));
}
/* end mesg_send */
size_t
mesg_recv(int id, struct mymesg *mptr)
{
	        ssize_t n;

		n = msgrcv(id, &(mptr->mesg_type), MAXMESGDATA, mptr->mesg_type, 0);
		mptr->mesg_len = n;             /* return #bytes of data */
		
		return(n);                              /* -1 on error, 0 at EOF, else >0 */
}

#define file  "./tmp.txt"

int
main()
{
	int		msgid;
	size_t		len;
	ssize_t 	n;
	char		*ptr;
	struct mymesg	mesg;
	key_t  key;
	
	key = ftok(file, 'a');
	printf("key: %d\n", key);

	msgid = msgget(key, IPC_CREAT);	/* 打开消息队列 */
	 
	printf("msgid: %d\n", msgid);
	
	char *str = "hello world";
	snprintf(mesg.mesg_data, MAXMESGDATA, "%s", str);
	/*
	len = strlen(mesg.mesg_data);
	ptr = mesg.mesg_data + len;
	fgets(ptr, MAXMESGDATA - len, stdin); /* 读入路径名 */
	
	len = strlen(mesg.mesg_data);
	if (mesg.mesg_data[len-1] == '\n')
		len--;
	mesg.mesg_len = len;
	mesg.mesg_type = 1;
	msg_send(msgid, &mesg);				/* 将路径名写入消息队列 */
//	mesg.mesg_type = getpid();			/* 以自己的进程号做为消息类型 */
	
	printf("while...\n");
	while((n = mesg_recv(msgid, &mesg)) > 0)		/* 从消息队列中读回服务进程返回的消息*/
		printf("n:%d\tdata: %s\n", n, mesg.mesg_data);	/* 将获得的文件内容写到标准输出 */
		
	write(stdout, "over....\n");	
	exit(0);
}
