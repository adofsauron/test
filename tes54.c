#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define contain_of(value, type, member) ({ \
	const typeof(((type *)0)->member) *_mptr = value; \
	(type *) (char *) _mptr-offsetof(type, member) ; })

struct Person
{
  char *name;
  int age;
};

int
main ()
{
  struct Person perA, *perB;
  perA.name = "tom";

  perB = contain_of (&perA.name, struct Person, name);


  printf ("perB->name: %s\n", perB->name);
  return 0;
}
