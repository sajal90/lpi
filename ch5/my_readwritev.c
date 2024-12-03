#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../headers/tlpi_hdr.h"

struct iovec {
	void *iov_base;
	size_t iov_len;
};

void pexit(const char *fCall) {
	perror(fCall);
	exit(EXIT_FAILURE);
}


ssize_t _readv(int fd, const struct iovec *iov, int iovcnt) {
	int i;
	size_t memSize;
	ssize_t numCopied, numRead;
	void *buf;

	/* Calculates all the space that will be required */
	memSize = 0;
	for (i = 0; i < iovcnt; ++i) {
		memSize += iov[i].iov_len;
	}

	buf = malloc(memSize);
	if (buf == NULL) {
		pexit("malloc");
	}

	/* Reads all the data from the file into the buffer */
	numRead = read(fd, buf, memSize);
	if (numRead == -1) {
		return numRead;
	}

	/* Copies read that to the iovec structure */
	numCopied = 0;
	for (i = 0; i < iovcnt; ++i) {
		memcpy(iov[i].iov_base, buf + numCopied, iov[i].iov_len);
		numCopied += iov[i].iov_len;
	}

	free(buf);

	return numRead;
}

ssize_t _writev(int fd, const struct iovec *iov, int iovcnt) {
	int i;
	size_t memSize;
	ssize_t numCopied, numWritten;
	void *buf;

	/* Calculates all the space that will be required */
	memSize = 0;
	for (i = 0; i < iovcnt; ++i) {
		memSize += iov[i].iov_len;
	}

	buf = malloc(memSize);
	if (buf == NULL) {
		pexit("malloc");
	}

	/* Copies data to the buffer */
	numCopied = 0;
	for (i = 0; i < iovcnt; ++i) {
		memcpy(buf + numCopied, iov[i].iov_base, iov[i].iov_len);
		numCopied += iov[i].iov_len;
	}

	numWritten = write(fd, buf, memSize);
	free(buf);

	return numWritten;
}

int main(int argc, char *argv[])
{
		int fd;
		struct iovec iov[3];
		struct stat myStruct;
		/* First buffer */
		int x;
		/* Second buffer */
#define STR_SIZE 100
		char str[STR_SIZE];
		/* Third buffer */
		ssize_t numRead, totRequired;
		if (argc != 2 || strcmp(argv[1], "--help") == 0)
			usageErr("%s file\n", argv[0]);
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			errExit("open");
		totRequired = 0;
		iov[0].iov_base = &myStruct;
		iov[0].iov_len = sizeof(struct stat);
		totRequired += iov[0].iov_len;
		iov[1].iov_base = &x;
		iov[1].iov_len = sizeof(x);
		totRequired += iov[1].iov_len;
		iov[2].iov_base = str;
		iov[2].iov_len = STR_SIZE;
		totRequired += iov[2].iov_len;
		numRead = readv(fd, iov, 3);
		if (numRead == -1)
			errExit("readv");
		if (numRead < totRequired)
			printf("Read fewer bytes than requested\n");
		printf("total bytes requested: %ld; bytes read: %ld\n",
	 (long) totRequired, (long) numRead);
		exit(EXIT_SUCCESS);
}
