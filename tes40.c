#include <stdio.h>
#include <netdb.h>

void show(struct hostent *hen)
{
	printf("h_name: %s\n", hen->h_name);
	printf("h_aliases: %s\n", hen->h_aliases);
	printf("h_addrtype: %d\n", hen->h_addrtype);
	printf("h_length: %d\n", hen->h_length);
	printf("h_addr: %s\n", inet_ntoa(*((struct in_addr *)hen->h_addr)));
}

int main(int argc, char **argv)
{
	struct hostent  *hen;
	
	hen = gethostbyname(argv[1]);

	if(hen == NULL)
	{
		printf("hen error!\n");
	}
	show(hen);
	return 0;
}
