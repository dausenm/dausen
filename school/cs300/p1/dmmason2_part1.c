#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX_LINE 80 /* The maximum length command */

char **parseArgs(char *command);

int main(void){
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    while (should_run) {
        int pid = getpid();
        printf("mason%d>", pid);
        fflush(stdout);

        char command[100];
    /**
    * After reading user input, the steps are:
    * (1) fork a child process using fork()
    * */
    fgets(command, MAX_LINE, stdin);

    //parse args func to get args[][]?

    char **args = parseArgs(command);

    printf("returned from parseArgs\n");

    pid = fork();

    //free(args);

    int w = 1;


    if(pid == 0) {
        printf("child was created! wooooo!\n");
        printf("%s\n", command);
    }

    else if(pid > 0) {
        printf("parent is still executing! woooo!\n");

        if(w){
            printf("parent waiting\n");
            wait();
        }
    }

    else if (pid == -1){
        printf("something went wrong. fuck.\n");
    }


   /*
    * (2) the child process will invoke execvp()

    */

   /*
    * (3) if command included &, parent will invoke wait()
    */
    }

    return 0;
}

char **parseArgs(char *command){
    printf("in parseArgs\n");
    char **rt;

    //rt[0][0] = 'a';

    printf("exiting\n");

    return rt;
}