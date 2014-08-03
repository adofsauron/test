#include <stdio.h>
#include <stdlib.h>

typedef enum tower
{
	A='X',
	B='Y',
	C='Z'
}tower;

void move(int n, tower x, tower y)
{
	printf("disk %d is moved from %c to %c\n", n, x, y);
}

void han(int n, tower x, tower y, tower z)
{
	if(n)
	{

		han(n-1, x, z, y);
		move(n, x, y);
		han(n-1, z, y, x);
	}
}

int main(int argc, char **argv)
{
	int n = atoi(argv[1]);

	han(n, A, B, C);
	return 0;
}
