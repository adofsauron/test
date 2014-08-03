#include <stdio.h>
#include <stdlib.h>

typedef int (*fun)(char *);


int say(char *str)
{
	printf("say, %s\n", str);
	return 0;
}

int very(char *str)
{
	printf("very, %s\n", str);
	return 0;
}

int main(int argc, char **argv)
{
	fun work[] = {say, very};
	work[0](argv[1]);
	work[1](argv[2]);

	return 0;
}

