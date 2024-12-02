#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "../headers/tlpi_hdr.h"

int main(int argc, char *argv[]) {
	int fd;

	if(argc<2) {
		usageErr("%s [filename]", argv[0]);
	}

	errno = 0;
	fd = open(argv[1], O_WRONLY | O_APPEND);
	if(fd == -1) {
		fprintf(stderr, "%s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	if((lseek(fd, 0, SEEK_SET)) == -1) {
		errExit("lseek");
	}

	if((write(fd, "hello", 5)) != 5) {
		errExit("write");
	}

	close(fd);
	exit(EXIT_SUCCESS);
}
