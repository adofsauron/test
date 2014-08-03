#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>

void show(int x)  
{  
    int a, b, c, d;  
    a = x&0xff000000;  
    a>>=24;  
    b = x&0x00ff0000;  
    b>>=16;  
    c = x&0x0000ff00;  
    c>>=8;  
    d = x&0x000000ff;  
      
    printf("%d %d %d %d\n", d, c, b, a);      
}  

void showHostent(struct hostent *h)
{
  printf ("h_name: %s\n", h->h_name);
  printf ("h_aliases: %s\n", h->h_aliases[0]);
  printf ("h_addrtype: %d\n", h->h_addrtype);
  printf ("h_length: %d\n", h->h_length);
  struct in_addr *inaddr;
  inaddr = (struct in_addr *) h->h_addr;
  printf ("IP Address: %x\n", inaddr->s_addr);
  
  show(inaddr->s_addr);
}

int main(int argc, char **argv)
{
	const char *domain = argv[1];
	struct hostent *h;
	h = gethostbyname(domain);

	showHostent(h);
	return 0;
}
