#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "../headers/error_functions.h"

int main(int argc, char *argv[])
{
	int fd;
	long num_bytes;
	int flags, x_flag;

	if(argc < 3) {
		usageErr("%s [filename] [bytes] {x}");
		exit(EXIT_FAILURE);
	}
	if(argc >=4 && argv[3][0] ==  'x') {
		x_flag = 1;
	}

	flags = O_RDWR | O_CREAT;
	if(x_flag) flags |= O_APPEND;

	fd = open(argv[1], flags, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		errExit("open");
	}
	

	num_bytes = atol(argv[2]);
	for(int i=0; i<num_bytes; ++i) {
		if(x_flag) {
			if(lseek(fd, 0, SEEK_END) == -1){
				errExit("lseek");
			}
		}
		if(write(fd, "a", 1) == -1) {
			errExit("write");
		}
	}

	if(close(fd) == -1)
		errExit("close");

	exit(EXIT_SUCCESS);
}
