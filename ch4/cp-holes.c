#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../headers/tlpi_hdr.h"

#define MAX_READ 4096

int main(int argc, char *argv[]) {
	int source_fd, des_fd;
	char buf[MAX_READ];
	int buf_size;
	

	if(argc < 3) {
		usageErr("%s [source] [destination]", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	errno = 0;
	source_fd = open(argv[1], O_RDONLY);
	if(source_fd == -1) {
		fprintf(stderr, "Opening source failed: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	errno = 0;
	des_fd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(des_fd == -1) {
		fprintf(stderr, "Opening des failed: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}

	while((buf_size = read(source_fd, buf, MAX_READ)) != 0) {
		errno = 0;
		if(write(des_fd, buf, buf_size) != buf_size) {
			fprintf(stderr, "Error: %s", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}

	close(source_fd);
	close(des_fd);
	exit(EXIT_SUCCESS);
}
