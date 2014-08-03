#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <linux/sysctl.h>

int _sysctl(struct __sysctl_args *args);

#define OSNAMESZ 100

int main()
{
	struct __sysctl_args args;
	
	char osname[OSNAMESZ];
	size_t osnamelth;
	int name[] = {CTL_KERN, KERN_OSTYPE};
	
	memset(&args, 0, sizeof(struct __sysctl_args));
	args.name = name;
	args.nlen = sizeof(name)/sizeof(name[0]);
	args.oldval = osname;
	args.oldlenp = &osnamelth;

	osnamelth = sizeof(osname);

	syscall(SYS__sysctl, &args);
/*	{
		perror("sysctl");
		exit(EXIT_FAILURE);
	}
*/	
	printf("runing: %*s\n", osnamelth, osname);
	
	printf("CTL_KERN: %d\tKERN_OSTYPE: %d\n", CTL_KERN, KERN_OSTYPE);
	return 0;
}
