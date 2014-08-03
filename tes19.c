#include <stdlib.h>
#include <stdio.h>

int
Fib(int N)
{
	int i, Last, NextToLast, Answer;

	if(N<=1)
	{
		return 1;
	}
	
	Last = NextToLast = 1;

	for(i=2; i<=N; i++)
	{
		Answer = Last + NextToLast;
		NextToLast = Last;
		Last = Answer;
	}

	return Answer;
}

int main(int argc, char **argv)
{
	int N = atoi(argv[1]);

	printf("%d\n", Fib(N));
	return 0;
}
