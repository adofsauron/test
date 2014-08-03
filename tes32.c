#include <stdio.h>
#include <stdlib.h>

union 
{
	char *name;
	int age;
	char *local;
}person;

struct PER
{
//	char *name:"Jame";
	int age:17;
}per;

void change(void *con)
{
	int *x=con;

	*x = (*x)*(*x);
}

int main(int argc, char **argv)
{
	person.name = "Jame";
	printf("%s\n", person.name);
	person.age = 17;
	printf("%d\n", person.name);

	char c = 0x65;
	printf("c: %c\n", c);

	printf("age: %d\n", per.age);
#if 0
	printf("fuck\n");
#endif

	unsigned long active, act;
	active = ~0;
	act = ~0;
	act += act;
	printf("active: %x, act: %x\n", active, act);
	
	return 0;
}
