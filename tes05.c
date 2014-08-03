#include <stdio.h>
#include <stdlib.h>

#define NUM 3
#define A  __attribute__((__section__(".A.data")))  NUM
//#define A 1
#define B __attribute__((__section__("B.data"))) 2

#define C __attribute__((__section__(".fuck")))

int main() 
{
	printf("A: %d\n", NUM);
	printf("sure\n");
	return 0;
} __attribute__((__section__(".A.data")));
