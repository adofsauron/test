#include <stdlib.h>
#include <stdio.h>

int main()
{
	long res;
	char buf[50];

	res =  getcwd(buf, sizeof(buf));

//	printf("res: %ld\n", res);
	printf("buf: %s\n",buf);
	
	char *path = "/usr/include/";
	chdir(path);
	
	getcwd(buf, sizeof(buf));
	printf("buf: %s\n", buf);
	return 0;
}
