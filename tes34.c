#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("%*s\n", 30, "abcdefg");
	
	int i;
	for(i=0; i<30; i++)
	{
		printf("0");
	}
	printf("\n");
	return 0;
}
