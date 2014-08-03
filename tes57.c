#include <stdio.h>
#include <stdlib.h>

int main()
{
	char  buf[100];

	fgets(buf, 100, stdin);

	printf("buf: %s\n", buf);

	char  snp[100];

	snprintf(snp, sizeof(snp),"buf is: %s\n", buf);
	printf("snp: %s\n", snp);
	return 0;
}
