#include <stdio.h>
#include <string.h>

int main()
{
	char *str = "abcdefgh";
	char *p;
	char buff[100];

	bzero(buff, 100);
	
	strcpy(buff, str);
	
	
	p = strchr(buff, 'd');
	*p++=0;

	printf("p: %s\n", p);

	int i;
	for(i=0; buff[i]!='\0'; i++)
	{
		printf("%d\n", buff[i]);
	}
	printf("%d\n", '\0');

	char buff01[100];
	char buff02[100];
	char *str01 = "abcdefg";
	char *str02 = "higk";

	strcpy(buff01, str01);
	strcpy(buff02, str02);	

	memmove(buff01, buff02, strlen(buff02));

	printf("buff01: %s\n", buff01);
	printf("buff02: %s\n", buff02);

	return 0;
}
