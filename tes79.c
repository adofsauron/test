#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>


void work(int n,char *fmt, ...)
{
	char buff[100];
	bzero(buff, sizeof(buff));
	va_list argptr;
	va_start(argptr, fmt);
	vsprintf(buff, fmt, argptr);

	int i;
	char *x;
	for(i=0; i<n; i++)
	{
		x = va_arg(argptr, char *);
		printf("i:%d, x: %s\n", i,x);
	}
	va_end(argptr);

	
}

int main()
{
	
	work(2,"one", "two", "three");

	char *str = "abcdef";
	
	char buff[256];
	bzero(buff, 256);
	//strcpy(buff, str);
	int x =  10;
	sprintf(buff, "%s, %d\n", str, x);
	write(STDOUT_FILENO, buff, strlen(buff));
//	printf("buff: %s\n", buff);
	
	return 0;
}
