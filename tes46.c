#include <stdio.h>

typedef void (*work)(void);

char shellcode[] = "\x55\x48\x89\xe5\xbf\x00\x00\x00\x00\xb8\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x5d\xc3";

void say()
{
	printf("say what?\n");
}

int main()
{

/*	char *addr;

	addr = shellcode;
//	((void (*)(void))addr)();

	((void (*)(void)) addr)();

	
	work fun;
	fun = say;

	fun();
*/


	asm volatile
	(
		"call %0\n"
		:
		:"a"(say)
	);
	return 0;
}
