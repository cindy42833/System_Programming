#include <sys/inotify.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

// #define BUF_LEN (1000 * (sizeof(struct inotify_event) + NAME_MAX + 1))

void printTime(struct stat *, char *);


int main(int argc, char **argv) {
	int fd, num, file_len;
	char* ptr;
	char filename[1024], buf[4096], file_buf[1024];
    long int last_touch_time, now_get_time;
    strcpy(filename, argv[1]);

    /* Opne file and get status */
    FILE* file = fopen(filename, "r");
    struct stat stat_buf;
    stat(filename, &stat_buf);
    last_touch_time = stat_buf.st_ctime;

    /* Print file status and content */
    strncat(buf, "Last modify time: ", 1024);
    strncat(buf, ctime(&stat_buf.st_mtime), 1024);
    fseek(file, 0, SEEK_SET);
    fseek(file, 0, SEEK_END);
    file_len = ftell(file);
    fseek(file, 0, SEEK_SET);
    fread(file_buf, file_len, 1, file);
    file_buf[file_len] = '\0';  // null terminated
    strncat(buf, file_buf, 1024);
	printf("%s", buf);
    printf("-----------------------------\n");
    fclose(file);

    /* Trace if the file is modified */
	while(1) {
        now_get_time = stat(filename, &stat_buf);
        now_get_time = stat_buf.st_ctime;

        if(last_touch_time != now_get_time) {
            usleep(1000);
            printTime(&stat_buf, filename);
            last_touch_time = now_get_time;
        }
    }
}

void printTime(struct stat *stat_buf, char *filename) {
    int file_len = 0;
	char buf[4096], file_buf[1024];
    buf[0] = '\0';
    file_buf[0] = '\0';    

    FILE *input_file = fopen(filename, "r");
    strncat(buf, "Last modify time: ", 1024);
    strncat(buf, ctime(&stat_buf->st_mtime), 1024);
    strncat(buf, "Last inode modify time: ", 1024);
    strncat(buf, ctime(&stat_buf->st_ctime), 1024);
    fseek(input_file, 0, SEEK_END);
    file_len = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    fread(file_buf, file_len, 1, input_file);
    file_buf[file_len] = '\0';  // null terminated
    strncat(buf, file_buf, 1024);
	printf("%s", buf);
    printf("-----------------------------\n");
    fclose(input_file);
}