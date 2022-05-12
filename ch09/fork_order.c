#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main() {

    printf("Head\n");
    int pid = vfork();

    if(pid == 0) {
        // execlp("ls", "-alh", "-R", "/", NULL);
        char *argv[]={"ls","-alh", "-R", "/",NULL};//傳遞給執行檔案的引數陣列，這裡包含執行檔案的引數 
        char *envp[]={0,NULL};//傳遞給執行檔案新的環境變數陣列
        execve("/bin/ls",argv,envp);
        // while(1) {
        //     printf("child\n");
        // }
    }
    else {
        // int status;
        // wait(&status);
        while(1) {
            printf("=================\n");
        }
    }

    return 0;
}