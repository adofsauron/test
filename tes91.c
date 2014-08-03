#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
main (void)
{
  char buf[1024];
  int ok;
  printf ("Welcome to goodie service!\n");
  fflush (stdout);
  ok = 0;
  do
    {
      while (fgets (buf, 1023, stdin) == NULL);
      if (strncasecmp (buf, "exit", 4) == 0)
			ok = 1;
      printf ("|%s", buf);
      
      fflush (stdout);
    }
  while (!ok);
}
