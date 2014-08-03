#include <stdlib.h>
#include <stdio.h>

enum
{
	one=11, two
};

typedef enum bool
{
	false, true
}bool;

int main()
{
//	enum STU stu;
	printf("%d\t%d\n",one,two);

	bool sign;

	sign = false;
	if(sign)
	{
		printf("true\n");
	}

	return 0;
}
