#include <stdio.h>
#include <stdlib.h>

void fun(void (*test)(int a), int x)
{
		test(x);
}

void work(int x)
{
		printf("x: %d\n", x);
}

int main()
{
		fun(work, 3);
		return 0;
}
