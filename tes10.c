#include <stdio.h>
#include <stdlib.h>

struct person
{
	char *name;
	int age;
};

int main()
{
	struct person *mp;

	char *nm = "Jame";
	char ag = 17;
	mp = container_of(nm, struct person, name);
	return 0;
}
