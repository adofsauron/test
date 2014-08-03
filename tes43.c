#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum=0;
void perm(char *a, int k, int n)
{
	if(k == (n-1))
	{
		int i;
		for(i=0; i<n; i++)
		{
			printf("%c ", a[i]);
		}
		printf("\n");
		sum++;
	}
	else
	{
		int i;
		for(i=k; i<n; i++)
		{
			char t;
			t = a[k];
			a[k] = a[i];
			a[i] = t;

			perm(a, k+1, n);

			t = a[k];
			a[k] = a[i];
			a[i] = t;
		}
	}

}

int main(int argc, char **argv)
{
	char *a = argv[1];
	int n = strlen(a);

	perm(a, 0, n);
	printf("n: %d\nsum: %d\n", n,sum);
	return 0;
}
