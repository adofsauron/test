#include <stdio.h>
#include <stdlib.h>

void fun(int* x)
{
	printf("%d\n", x);
}

int main()
{

	char **x;
	x = malloc(sizeof(char *)*2);
	x[0] = "hello";
	x[1] = "world";

	int i;
	for(i=0; x[i]; x++)
	{
		printf("%s\n", x[i]);
	}
	return 0;
}

