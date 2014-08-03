#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdarg.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 

void show(char *domain)
{
	struct hostent *site;
	site = gethostbyname(domain);
	int i;
	for(i=0; site->h_aliases[i]!=NULL; i++)
	{
			printf("%s\n", site->h_aliases[i]);
	}	
	printf("h_name: %s\n", site->h_name);
	struct in_addr  *addr;
	addr = (struct in_addr  *)site->h_addr_list[0];
	printf("h_addr: %x\n", addr->s_addr);
}

int main(int argc, char **argv)
{
	show(argv[1]);
	return 0;
}
