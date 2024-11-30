#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../headers/tlpi_hdr.h"

#define MAX_SIZE 1024

int main(int argc, char *argv[])
{
	int fd = -1;
	char *buff[MAX_SIZE];
	int buf_size;
	int file_idx = 1;
	int flags = 0;

	char opt;
	if((opt = getopt(argc, argv, ":a") != -1)) {
		printf("i am here\n");
		file_idx = optind;
		flags = O_APPEND;
	}

	if(argc > 1) {
		flags |= O_RDWR | O_CREAT;
		fd = open(argv[file_idx] ,flags, S_IRUSR | S_IWUSR);
		if(fd < 0) {
			fprintf(stderr, "open: %s", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}

	errno = 0;
	while((buf_size = read(STDIN_FILENO, buff, MAX_SIZE)) != 0) {
		if(buf_size < 0) {
			fprintf(stderr, "read: %s", strerror(errno));
			exit(EXIT_FAILURE);
		}

		errno = 0;
		if(fd != -1) {
			if((write(fd, buff, buf_size)) != buf_size) {
				fprintf(stderr, "write: %s",strerror(errno)); 
				exit(EXIT_FAILURE);
			}
		}

		if((write(STDOUT_FILENO, buff, buf_size)) != buf_size) {
			fprintf(stderr, "write: %s",strerror(errno)); 
			exit(EXIT_FAILURE);
		}


	}
	return 0;
}
