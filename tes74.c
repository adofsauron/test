#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	
	char str[10];
	while(1)
	{
		bzero(str, sizeof(str));
		fgets(str, 10, stdin);
		int n;
		if((n=strncmp(str, "fuck", 4)) ==0)
		{
			printf("before if\n");
			continue;
			printf("if\n");
		}	
		else
		{
			printf("else\n");
		}
		
		printf("over\n");
		
	}	
		
		
	return 0;
}
