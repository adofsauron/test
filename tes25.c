#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	char *str = argv[1];

	int i;
	char x;
	for(i=0; i<strlen(str); i++)
	{
		x = str[i];
		printf("0x%x\t%c\n", x, x);	

	}
	return 0;
}
