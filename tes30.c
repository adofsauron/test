#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("char: %d\n", sizeof(char));
	printf("short: %d\n", sizeof(short));
	printf("int: %d\n", sizeof(int));
	printf("long: %d\n", sizeof(long));

	char x[] = {0x01, 0x02, 0x03};

	printf("%x\n", *x);

	short a = 0x0201;
	printf("%x\n", a);
	return 0;
}
