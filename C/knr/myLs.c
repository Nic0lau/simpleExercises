/* Re-implementation of ls command */

#include <sys/stat.h>
#include <sys/types.h>

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH 1024

void printDir(char *name, void (*fn)(char *name));
void printInfo(char *name);

void
printDir(char *name, void (*fn)(char *name))
{
	char dirName[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;
	
	if ((dfd = opendir(name)) == NULL) {
		perror(name);
		return;	
	}

	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
			continue;
		
		if ((strlen(name) + strlen(dp->d_name) + 3) > sizeof(dirName)) {
			fprintf(stderr, "%s/%s is too much long!", name, dp->d_name);
		} else {
			sprintf(dirName, "%s/%s", name, dp->d_name);
			(*fn)(dirName);
		}
	}

	closedir(dfd);
}

void
printInfo(char *name)
{
	struct stat bufst;
	
	if (stat(name, &bufst) == -1) {
		perror(name);
		return;	
	}

	if (S_ISDIR(bufst.st_mode))
		printDir(name, printInfo);
	
	printf("%d %ld %ld %s\n", bufst.st_uid, bufst.st_ino, (long) bufst.st_size, name);
}

int
main(int argc, char **argv)
{
	if (argc == 1) 
		printInfo(".");
	else
		while (--argc > 0)
			printInfo(*++argv);

	return 0;
}
