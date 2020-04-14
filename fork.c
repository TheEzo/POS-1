#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED 1 /* XPG 4.2 - needed for WCOREDUMP() */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void init_print(char *);
void exit_print(char *, int, int);

/* ARGSUSED */
int main(int argc, char **argv)
{
    char *label_gp = "grandparent";
    char *label_p = "parent";
    char *label_c = "child";
    int status_c;
    int status_p;
    init_print(label_gp);
    int pid_c;
    int pid_p;

    if((pid_p = fork()) == 0){
        init_print(label_p);
        if((pid_c = fork()) == 0){
            init_print(label_c);
//            execv("ll", []);
            exit(1);
        }
        else{
            wait(&status_c);
            exit_print(label_p, status_c, pid_c);
        }
    }
    else{
        wait(&status_p);
    }
    return 0;
}

void init_print(char *label){
    printf("%s identification: \n", label); /*grandparent/parent/child */
    printf("\tpid = %d,\tppid = %d,\tpgrp = %d\n", getpid(), getppid(), getpgrp());
    printf("\tuid = %d,\tgid = %d\n", getuid(), getgid());
    printf("\teuid = %d,\tegid = %d\n", geteuid(), getegid());
}

void exit_print(char *label, int status, int pid){
    printf("%s exit (pid = %d):", label, pid); /* and one line from */
    if(WIFEXITED(status)) {
        printf("\tnormal termination (exit code = %d)\n", WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status)) {
        if(WCOREDUMP(status))
            printf("\tsignal termination with core dump (signal = %d)\n", WTERMSIG(status));
        else
            printf("\tsignal termination (signal = %d)\n", WTERMSIG(status));
    }
    else {
        printf("\tunknown type of termination\n");
    }
}
