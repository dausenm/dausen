/*
    TODO:
        fix order of !! command
        general bug testing
*/
/*
Written by Dausen Mason.
CWID: 11955307
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>
#define MAX_LINE 80 /* The maximum length command */

void parseArgs(char *command, char *args[]);

void addToArgs(char buf[], char *args[], int argc, int count);

void addToHist(char *hist[], char command[], int hCount);

void printHistory(char *hist[], int hCount);

int main(void){
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    char *hist[MAX_LINE];
    int hCount = 0;
    while (should_run) {
        int pid = getpid();
        printf("mason%d>", pid);
        fflush(stdout);

        char command[100];

        fgets(command, MAX_LINE, stdin);

        if(!strcmp(command, "exit\n")){
            printf("exiting\n");
            should_run = 0;
            return 0;
            break;
        }

        char *args[MAX_LINE/2];

        char *a;

        a = strstr(command, "&");

        if(strcmp(command, "history\n") &&  command[0] != '!'){
            addToHist(hist, command, hCount);
            hCount++;
        }

        if(!strcmp(command, "history\n")){
            printHistory(hist, hCount);
        }

        int hFunc = 0;

        if(command[0] == '!'){
            hFunc = 1;
            if(command[1] == '!'){
                printf("you're here\n");
                if(hCount < 10){
                    addToHist(hist, hist[hCount - 1 % 10], hCount);
                    hCount++;
                    parseArgs(hist[hCount - 1 % 10], args);
                }
                else{
                    addToHist(hist, hist[hCount % 10], hCount);
                    hCount++;
                    parseArgs(hist[hCount % 10], args);
                }
            }
            else if(isdigit(command[1])){
                printf("hey bruh that's a digit\n");
                char c = command[1];
                int i = c - '0' ;
                printf("i = %d", i);
                addToHist(hist, hist[i - 1], hCount);
                hCount++;
                parseArgs(hist[i - 1], args);
            }
            else{
                hFunc = 0;
            }
        }
        if(!hFunc){
            parseArgs(command, args);
        }
        /**
        * After reading user input, the steps are:
        * (1) fork a child process using fork()
        * */

        pid = fork();

        if(pid == 0) {      //(2) the child process will invoke execvp()
            execvp(args[0], args);
            exit(0);
        }

        else if(pid > 0) {      //(3) if command included &, parent will invoke wait()
            if(!a){
                wait(NULL);
            }
        }

        else if (pid == -1){
            printf("something went wrong. fuck.\n");
        }
    }

    return 0;
}

void parseArgs(char *command, char *args[]){        //example input: ""
    printf("pa: command: %s\n", command);

    char buf[MAX_LINE];

    int stop = 0;
    int count = 0;
    int argc = 0;
    

    for(int i = 0; i < MAX_LINE; i++){
        if(command[i] != ' ' && command[i] != '\0' && command[i] != '\n' && command[i] != '&'){
            stop = 0;
            buf[count] = command[i];
            count++;
        }

        if(stop){
            break;
        }

        if(command[i] == ' ' || command[i] == '\0' || command[i] == '\n'){
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

    args[argc] = NULL;

    return;
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

void addToHist(char *hist[], char command[], int hCount){

    char *buffer;

    buffer = (char *) malloc(MAX_LINE * sizeof(char));

    strcpy(buffer, command);

    hist[hCount % 10] = buffer;
    return;
}

void printHistory(char *hist[], int hCount){
    if(hCount < 10){
        for(int i = 0; i < hCount; i++){
            printf("%d %s\n", i + 1, hist[i]);
        }
    }
    else{
        printf("else\n");
        for(int i = 0; i < 10; i++){
            printf("%d %s\n", 10 - i, hist[(hCount + i) % 10]);
        }
    }

    return;
}