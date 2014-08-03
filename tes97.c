#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define  forfun(a, b)  (a##b)
#define p(s) printf(#s)

bool test(int x)
{
	if(x<0)
		return false;
	else
		return true;
}

void fun(char *str)
{
	printf("str: %s\n", str);
}

int main()
{
	static char *str = "fuck you!";
	if(test(-1))
		printf("%s\n", str);


	char ws[250]="";
	strcat(ws, "fuck\r\n");
	strcat(ws, "you\r\n");

	printf("ws: %s\n", ws);

	char *a = "a";
	char *b = "b";
	char *cd = "ab";

	fun(forfun(c, d));	

	p(hello world\n);
	return 0;
}
