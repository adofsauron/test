#include <stdio.h>
#include <stdlib.h>

enum stu
{
	one=7, 
	two, 
	three
};

int main()
{
	enum stu mst;

	mst = two;

	printf("mst: %d\n", mst);
	return 0;
}
