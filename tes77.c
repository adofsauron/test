#include <stdio.h>

void say(int a, int b)
{
	printf("say a b\n");
}

void say_(int a)
{
	printf("say a\n");
}

int main()
{
	say_(1);
	say(1, 2);
	return 0;
}
