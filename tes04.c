#include <stdio.h>

void say(char *s)
{
	printf("%s\n", s);
}__attribute__ ((packed))

int main()
{
	char *str = "hello world";
	say(str);
	return 0;
}
