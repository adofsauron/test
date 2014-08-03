#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void say()
{
	printf("say\n");
}

int main()
{
	long *addr;
//	strcpy((char *)addr, say);
	
	addr = say;
	((void (*)(void))addr)();
	
	return 0;
}
