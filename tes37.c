#include <stdio.h>
#include <stdlib.h>

typedef int (*fun)();

int say()
{
	printf("say\n");
	return 0;
}

int main()
{
	fun work;
	work = &say;

	work();
}
