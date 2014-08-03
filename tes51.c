#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	in_addr_t x = inet_addr(argv[1]);

	printf("%x\n", x);

	struct in_addr inp;
	inet_aton(argv[0], &inp);
	
	printf("inp.s_addr: %x\n", inp.s_addr);
	return 0;
}
