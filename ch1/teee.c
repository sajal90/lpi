/*
 	The tee command reads its standard input until end-of-file, writing a copy of the input
	to standard output and to the file named in its command-line argument. (We show
	an example of the use of this command when we discuss FIFOs in Section 44.7.)
	Implement tee using I/O system calls. By default, tee overwrites any existing file with
	the given name. Implement the –a command-line option (tee –a file), which causes tee
	to append text to the end of a file if it already exists. (Refer to Appendix B for a
	description of the getopt() function, which can be used to parse command-line
	options.)
*/

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

	if(argc > 1) {
		fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
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
