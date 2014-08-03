#include <stdlib.h>
#include <stdio.h>


int
Fib(int N)
{
	if(N<=1)
		return 1;
	else
		return Fib(N-1) + Fib(N-2);
}

int main(int argc, char **argv)
{
	int N = atoi(argv[1]);

	printf("%d\n", Fib(N));
	return 0;
}
