#include <stdio.h>
#include <string.h>

#define MAX 512

void work (char *_buf, int len, FILE *stream)
{
	fgets(_buf, len, stream);
}

int main(int argc, char **argv)
{
/*
	char buf[MAX];

	work(buf, MAX, stdin);
	
	printf("buf: %s\n", buf);
*/

	char *dest;
	char *src;
	src = argv[1];
	memcpy(dest, src, strlen(src));
	
	printf("dest: %s\n", dest);
	return 0;
}
