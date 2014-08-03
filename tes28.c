#include <stdio.h>
#include <stdlib.h>

#define p(a, b) a##b

#define ab  "HELLOi"

//typedef (void *fun)(char *) fun;

typedef  void  (*fun)(char *);

void say(char *str)
{
	printf("say: %s\n", str);
}

void pf(char *str)
{
	printf("%s\n", str);
}

int main(int argc, char **argv)
{
	char *a = argv[1];
	char *b = argv[2];

	printf("%s\n", p(a, b));

	fun work[]={say, pf};

	work[0](a);
	work[1](a);
	return 0;
}
