#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

union 
{
	int value;
	char bytes[sizeof(int)];
}test;

int main()
{
	test.bytes[0] = 0x01;
	test.bytes[1] = 0x02;
	test.bytes[2] = 0x03;
	test.bytes[3] = 0x04;

	printf("%x\n", test.value);
	return 0;
}
