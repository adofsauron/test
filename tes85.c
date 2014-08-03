#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>\

void show(int x);

int main (int argc, char *argv[])
{
	struct hostent *h;
	/* ����������еĲ����Ƿ���� */
	if (argc != 2) { 
	  /* ���û�в���������ʹ�÷��� */
	  printf ("usage: getip address\n");
	  /* Ȼ���˳� */
	  exit(1);
	}
	
	/* ȡ��������Ϣ */
	if ((h=gethostbyname(argv[1])) == NULL){
		/* ���gethostbynameʧ�ܣ������������Ϣ */
		herror("gethostbyname");
		/* Ȼ���˳� */
		exit(1);
	}
	/* ��ӡ����ȡ�õ���Ϣ */
	printf("h_name: %s\n", h->h_name);
	printf("h_aliases: %s\n", h->h_aliases[0]);
	printf("h_addrtype: %d\n", h->h_addrtype);
	printf("h_length: %d\n", h->h_length);
	struct in_addr *inaddr;
	inaddr = (struct in_addr *)h->h_addr;
	printf("IP Address: %x\n",inaddr->s_addr);
	
	
	show(inaddr->s_addr);
	/* ���� */
	return 0;
}


void show(int x)
{
	int a, b, c, d;
	a = x&0xff000000;
	a = a>>24;
	b = x&0x00ff0000;
	b = b>>16;
	c = x&0x0000ff00;
	c = c>>8;
	d = x&0x000000ff;
	
	printf("%x %x %x %x\n", a, b, c, d);	
}


