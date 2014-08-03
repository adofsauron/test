#include <stdio.h>
#include <stdlib.h>

union person
{
	char *name;
	int age;
};

int main()
{
	union person  myper;
	myper.name = "Jame";
	printf("%s\n", myper.name);
	myper.age = 17;
	printf("%d\n", myper.age);
	printf("%d\n", myper.name);
	return 0;
}
