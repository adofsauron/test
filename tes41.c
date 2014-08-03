#include <stdio.h>
#include <stdlib.h>

void fun(int n)
{
	printf("%d\n", n%10);
	
	if(n>=10)
	{
		fun(n/10);
	}
}

int main(int argc, char **argv)
{
	int x = atoi(argv[1]);

	fun(x);


	return 0;
}
