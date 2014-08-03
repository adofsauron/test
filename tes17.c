#include <stdio.h>
#include <stdlib.h>

unsigned int
Gcd(unsigned int M, unsigned int N)
{
	unsigned int Rem;

	while(N>0)
	{
		Rem = M%N;
		M = N;
		N = Rem;
	}

	return M;
}

int 
main(int argc, char **argv)
{
	int M = atoi(argv[1]);
	int N = atoi(argv[2]);

	printf("%d\n", Gcd(M, N));
	return 0;	
}
