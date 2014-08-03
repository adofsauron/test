#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void
htsend ( char *fmt, ...)
{
  char BUF[1024];
  va_list argptr;
  va_start (argptr, fmt);
  vsprintf (BUF, fmt, argptr);
  va_end (argptr);
  printf("%s\n", BUF);
}

int
main ()
{
	//htsend("waht:%s, %c", "abcd", 'A');
	printf("%d", '\n');
	return 0;
}
