#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 80 /* The maximum length command */

int parseArgs(char *command, char *args[]);

void addToArgs(char buf[], char *args[], int argc, int count);

int main(void){
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    while (should_run) {
        int pid = getpid();
        printf("mason%d>", pid);
        fflush(stdout);

        char command[100];

        fgets(command, MAX_LINE, stdin);

        if(!strcmp(command, "exit")){
            printf("exiting\n");
            should_run = 0;
            return 0;
            break;
        }

        char *args[MAX_LINE/2];

        int w = parseArgs(command, args);

        /**
        * After reading user input, the steps are:
        * (1) fork a child process using fork()
        * */

        pid = fork();

        if(pid == 0) {      //(2) the child process will invoke execvp()
            printf("child was created! wooooo!\n");
            printf("%s\n", command);
            execvp(args[0], args);
            exit(0);
        }

        else if(pid > 0) {      //(3) if command included &, parent will invoke wait()
            printf("parent is still executing! woooo!\n");

            if(w){
                printf("parent waiting\n");
                wait();
            }
        }

        else if (pid == -1){
            printf("something went wrong. fuck.\n");
        }
    }

    return 0;
}

int parseArgs(char *command, char *args[]){        //example input: ""
    char buf[MAX_LINE];

    int stop = 0;
    int count = 0;
    int argc = 0;
    int rt = 0;

    for(int i = 0; i < MAX_LINE; i++){
        if(command[i] != ' ' && command[i] != '\0'){
            stop = 0;
            buf[count] = command[i];
            count++;
        }

        if(stop){
            break;
        }

        if(command[i] == ' ' || command[i] == '\0'){
            if(!strcmp(buf, "&")){
                rt = 1;
                stop = 1;
                continue;
            }
            //add buf to args, increment argc
            addToArgs(buf, args, argc, count);
            argc++;

            //clear buf and reset count;
            count = 0;
            strcpy(buf, "");

            //finally, set stop to 1;
            stop = 1;
        }
    }

    return rt;
}


void addToArgs(char buf[], char *args[], int argc, int count){
    char *buffer;

    buffer = (char *) malloc(count * sizeof(char));

    for(int i = 0; i < count; i++){
        buffer[i] = buf[i];
    }

    args[argc] = buffer;
    return;
}