#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define con_off(ptr, type, member)({ \
	const typeof(((type *) 0)->member) *_mptr = (ptr); \
	(type *) (char *) _mptr-offsetof(type, member); }) 

struct Person
{
	char *name;
	int age;
	char *location;
};

int main()
{
	long x = offsetof(struct Person, location);
	
	struct Person personA, *personB;

	personA.name = "Jame";
	personA.age = 17;
	personA.location = "earth";

	
	personB = con_off(&personA.name, struct Person, name);
	printf("x: %d\n", x);

	printf("personB.name: %s\n", personB->name);
	return 0;
}




