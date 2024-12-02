#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "../headers/tlpi_hdr.h"

#define _LARGEFILE64_SOURCE 64

int main(int argc, char *argv[]) {
	off_t off;
	int fd;
	char buf[] = "Hello world";
	int buf_size = sizeof(buf)/sizeof(buf[0]);
	
	if(argc < 2) {
		usageErr("%s [filename] [offset]", argv[0]);
	}

	fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		errExit("error opening file");
	}

	off = atoll(argv[2]);

	if((lseek(fd, off, SEEK_END)) == -1) {
		errExit("lseek");
	}

	if((write(fd, buf, buf_size)) != buf_size) {
		errExit("write");
	}

	exit(EXIT_SUCCESS);
}
