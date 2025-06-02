/* Re-implementation of some features of stdio header using unix syscalls */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define EOF (-1)
#define BUFFER_SIZE 1024
#define MAX_FILES 20
#define PERMS 0666

typedef struct {
	unsigned short read : 1;
	unsigned short write : 1;
	unsigned short unbuf : 1;
	unsigned short eof : 1;
	unsigned short err : 1;
} flags;

typedef struct {
	int fd;
	short counter;
	char *p;
	char *buffer;
	flags _flags;	
} FILE;

FILE *fopen(char *name, char *mode);
char fillBuffer(FILE *fp);
char flushBuf(char c, FILE *fp);
char fflush(FILE *fp);
short fclose(FILE *fp);
short fseek(FILE *fp, long long mov, unsigned short origin);

FILE allFiles[MAX_FILES];

FILE *
fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;
	
	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	
	for (fp = allFiles;fp < allFiles + MAX_FILES;fp++)
		if (!fp->_flags.read && !fp->_flags.write)
			break;
	
	if (fp >= allFiles + MAX_FILES)
		return NULL;
	
	if (*mode == 'w') {
		fd = creat(name, PERMS);	
	} else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY)) < 0)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else {
		fd = open(name, O_RDONLY);
	}
	
	if (fd == -1)
		return NULL;
	
	fp->fd = fd;
	fp->counter = 0;
	fp->buffer = NULL;
	fp->_flags.read = (*mode == 'r');
	fp->_flags.write = !fp->_flags.read;
	fp->_flags.eof = fp->_flags.err = fp->_flags.unbuf = 0;

	return fp;
}

char
fillBuffer(FILE *fp)
{
	unsigned short size;
	
	if (!fp->_flags.read || fp->_flags.eof || fp->_flags.err)
		return EOF;

	size = (fp->_flags.unbuf) ? 1 : BUFFER_SIZE;
	
	if (fp->buffer == NULL)
		if ((fp->buffer = (char *) malloc(size)) == NULL)
			return EOF;
	
	fp->p = fp->buffer;
	fp->counter = read(fp->fd, fp->p, size);

	if (--fp->counter < 0) {
		if (fp->counter == -1)
			fp->_flags.eof = 1;
		else
			fp->_flags.err = 1;
		
		fp->counter = 0;
		return EOF;	
	}

	return fp->counter++;
}

char
flushBuf(char c, FILE *fp)
{
	unsigned short size;

	if (!fp->_flags.write || fp->_flags.eof || fp->_flags.err)
		return EOF;

	size = (fp->_flags.unbuf) ? 1 : BUFFER_SIZE;

	if (fp->buffer == NULL) {		
		if ((fp->buffer = (char *) malloc(size)) == NULL)
			return EOF;

		fp->p = fp->buffer;
		fp->counter = size;		
	}

	if (write(fp->fd, fp->buffer, size) != size) {
		return EOF;
	} else {
		fp->p = fp->buffer;
		*(fp->p)++ = c;
		fp->counter--;		
		return c;
	}	
}

char
fflush(FILE *fp)
{
	if (fp == NULL) {
		for (fp = allFiles;fp < allFiles + MAX_FILES;fp++)
			if (!fp->_flags.write || fflush(fp) < 0)
				break;
	} else {
		if (!fp->_flags.write) {
			return EOF;
		} else {
			if (flushBuf(0, fp) < 0) {
				fp->_flags.err = 1; 
				return EOF;
			} else {
				return 0;
			}
		}
	}

	return 0;
}

short
fclose(FILE *fp)
{
	int fd;
	free(fp->buffer);
	fp->counter = fp->_flags.write = fp->_flags.read = fp->_flags.eof = fp->_flags.err = fp->_flags.unbuf = 0;
	fp->p = fp->buffer = NULL;
	fd = fp->fd;
	fp->fd = 0;
	
	return (close(fd));
}

short
fseek(FILE *fp, long long mov, unsigned short origin)
{
	if (fp == NULL || (!fp->_flags.write && !fp->_flags.read))
		return -1;
	
	if (fp->_flags.write) {
		if (fflush(fp) < 0)
			return -1;	
	} else {
		fp->counter = 0;
		fp->p = fp->buffer;
	}
	
	return (lseek(fp->fd, mov, origin) >= 0);
}

int
main(void)
{
	return 0;
}
