#include <stdio.h>

int
main ()
{
  FILE *file;
  file = fopen ("tmp.txt", "r");

  char line[100];
  fgets (line, 100, file);

  int x;
  fscanf (file, "%d", &x);

  fclose (file);

  printf ("line: %s\n x: %d\n", line, x);

  return 0;
}
