#include <stdlib.h>
#include <syslog.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
	char *str = argv[1];

	openlog(str, LOG_PID, 0);
	return 0;
}
