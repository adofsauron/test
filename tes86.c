#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

void change(int x, char *str);


int
main (int argc, char *argv[])
{
  struct in_addr addr1, addr2;
  ulong l1, l2;
  l1 = inet_addr ("192.168.0.74");
  l2 = inet_addr ("211.100.21.179");
  memcpy (&addr1, &l1, 4);
  memcpy (&addr2, &l2, 4);
  printf ("%s : %s\n", inet_ntoa (addr1), inet_ntoa (addr2));	//注意这一句的运行结果
  printf ("%s\n", inet_ntoa (addr1));
  printf ("%s\n", inet_ntoa (addr2));
  
  printf("%x\n", addr1.s_addr);
  change(addr1.s_addr, NULL);
  return 0;
}

void change(int x, char *str)
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
