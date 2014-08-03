#include <stdio.h>
#include <stdlib.h>

unsigned char fun;

int main()
{
	fun = ~0;

	printf("%x, %d\n", fun, fun);
	
	return 0;
}
