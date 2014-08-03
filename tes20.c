#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	printf("uid: %d\n", getuid());
	printf("eudi: %d\n", geteuid());
	printf("gid: %d\n", getgid());
	printf("egid: %d\n", getegid());
	printf("pgid: %d\n", getpgid(getpid()));
	return 0;
}
