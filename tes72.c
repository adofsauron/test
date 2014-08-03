#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	DIR *dp;
	struct dirent *dirp;		

	char *path = argv[1];
	dp = opendir(path);

	char buff[1024];
	char *ptr;
	
	ptr = buff;

	bzero(buff, sizeof(buff));
	while((dirp=readdir(dp))!=NULL)
	{
//		printf("dirp->d_name: %s\n", dirp->d_name);
		if(strcmp(dirp->d_name, ".")==0 || strcmp(dirp->d_name, "..")==0)
			continue;
		else
		{
			int n = strlen(dirp->d_name);
			strcpy(ptr, dirp->d_name);
			ptr +=n;
			*ptr = '\n';
			ptr ++;
			
		}
	}

	printf("buff: %s\n", buff);
	return 0;
}
