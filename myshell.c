#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80

void parse(char* args[MAX_LINE/2 + 1], char str[MAX_LINE]);

int main(void) {

    char* args[MAX_LINE/2 + 1];
    char str[MAX_LINE];
    char last_command[MAX_LINE] = {0};
    int should_run = 1;
    int pid;

    while (should_run) {
        printf("morsa>");
        fflush(stdout);

        fgets(str, MAX_LINE, stdin); 
        str[strcspn(str, "\n")] = 0;   // trim newline

        if (strcmp(str, "!!") == 0) {
            if (last_command[0] != 0) {
                sprintf(str, "%s", last_command);
                printf("%s\n", last_command);
            } else {
                printf("No commands in history\n");
                continue;
            }
        } else {
            sprintf(last_command, "%s", str);
        }

        parse(args, str);

        pid = fork();

        if (pid == 0) {
            execvp(args[0], args);
        } else {
            wait(NULL);
        }
    }

    return 0;
}

/*
    We should not declare str[] as a local variable here
    otherwise it dies on the stack return and produces a 
    leaky reference.
    One way to solve that is using malloc, but this way works 
    too and we don't have to deal with freeing memory.
*/
void parse(char* args[MAX_LINE/2 + 1], char str[MAX_LINE]) {

    char* p = strtok(str, " ");  

    int n_spaces = 0;

    while (p) {
        args[n_spaces++] = p;

        p = strtok(NULL, " ");
    }

    args[n_spaces] = NULL;   // end of array
}