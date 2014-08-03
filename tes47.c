#include <stdio.h>

int add(int a, int b)
{
	int x;
	__asm__(
		"addl %%ebx, %%eax\n\t"
		:"=a"(x)
		:"a"(a), "b"(b)
		
	);

	return x;
}

int main()
{
	printf("x: %d\n", add(3,4));
	return 0;
}
