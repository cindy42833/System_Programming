//usage: pipe4-3 killgrp或 pipe4-3 killproc
//結果相當於執行： ls | sort
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <wait.h>

int pid1, pid2;

void signal_ctr_c(int signum) {
    fprintf(stderr, "kill process group %d\n", -1*pid1);
    //殺掉process group
    kill(-1*pid1, signum);
    //parent結束離開
    _exit(0);
}

int main(int argc, char **argv) {
    int pipefd[2];

    if (argc != 2) {
        printf("./fileCount path\n");
        exit(0);
    }
    int tid = tcgetpgrp(STDIN_FILENO);
    printf("tid= %d\n", tid);
    pipe(pipefd);
    pid1 = fork();   //產生第一個child
    if (pid1==0) {
        setpgid(0, 0);  //將第一個child設定為新的group
        printf("first child group: %d\n", getpgrp());
        close(1);   //關閉stdout
        dup(pipefd[1]); //將pipefd[1]複製到stdout
        close(pipefd[1]);   //將沒用到的關閉
        close(pipefd[0]);   //將沒用到的關閉
        execlp("ls", "ls", "-R", argv[1], NULL);//執行ls，ls會將東西藉由stdout輸出到pipefd[1]
    } 
    else {    
        pid2 = fork();  //產生第二個child
        if (pid2==0) { 
            setpgid(0, pid1);   //第二個child加入第一個child的group
            close(0);   //關閉stdin
            printf("second child group: %d\n", getpgrp());
            dup(pipefd[0]); //將pipefd[0]複製到stdin
            close(pipefd[1]);   //將沒用到的關閉
            close(pipefd[0]);   //將沒用到的關閉
            execlp("wc", "wc", "-l", NULL);   //執行wc，wc將透過stdin從pipefd[0]讀入資料
        }
        else {
            /*parent註冊signal handler*/
            signal(SIGINT, signal_ctr_c); 
            
            //parent一定要記得關掉pipe不然wc不會結束（因為沒有接到EOF）
            close(pipefd[0]); 
            close(pipefd[1]);
            
            int status;
            printf("parent group: %d\n", getpgrp());
            waitpid(pid1, &status, 0);
            waitpid(pid2, &status, 0);
        }
    }
    
    return 0;
}