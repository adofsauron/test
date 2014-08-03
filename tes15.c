#include <stdio.h>

void byteorder()
{
	union
	{
		short value;
		char union_bytes[sizeof(short)];
	}test;

	test.value = 0x0102;
	
	if( (test.union_bytes[0] == 1) && (test.union_bytes[2] == 2)  )
	{
		printf("big\n");
	}
	else if( (test.union_bytes[0] == 2) && (test.union_bytes[1] == 1)  )
	{
		printf("little\n");
	}
	else
	{
		printf("unknown\n");
	}
	
}

int main()
{
	byteorder();
	return 0;
}


