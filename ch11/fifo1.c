#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char buf[200];

int main(int argc, char **argv) {
	int fd;
	mkfifo("./tmp", 0666);
	fd = open("./tmp",O_RDWR);
	write(fd, "hello", strlen("hello")+1);
	read(fd, buf, 200);
	printf("%s\n", buf);
	close(fd);
	getchar();
	unlink("./tmp");
	return 0;
}

