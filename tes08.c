#include <stdio.h>
#include <stdlib.h>

struct person
{
	char *name;
	union
	{
		char *one;
		char *two;
	};

	struct
	{
		char *father;
		char *mother;
	};
};

int main()
{
	struct person mp;
	mp.name = "Jame";
	mp.one = "one";
	mp.two = "two";

	mp.father = "father";
	mp.mother = "mother";

	printf("name: %s, one: %s, two: %s\n", mp.name, mp.one, mp.two);
	printf("father: %s, mother: %s\n", mp.father, mp.mother);
	return 0;
}
