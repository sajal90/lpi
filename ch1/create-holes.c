#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OFFSET 100000

int main() {
	int fd;

	errno = 0;
	fd = open("file.hole", O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR);
	if(fd == -1) {
		fprintf(stderr, "%s",strerror(errno));
		exit(EXIT_FAILURE);
	}

	errno = 0;
	if((write(fd, "Hello, world", 12)) == -1) {
		fprintf(stderr, "%s",strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	errno = 0;
	if((lseek(fd, OFFSET, SEEK_CUR)) == -1) {
		fprintf(stderr, "%s",strerror(errno));
		exit(EXIT_FAILURE);
	}

	errno = 0;
	if((write(fd, "bye, world", 10)) == -1) {
		fprintf(stderr, "%s",strerror(errno));
		exit(EXIT_FAILURE);
	}

	close(fd);
	return 0;
}
