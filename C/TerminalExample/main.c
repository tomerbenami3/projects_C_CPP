#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>


void read_command(char* command, char* param) {

    // char* str = command;
    printf("%s", command);
}
int main() {

    char command[20];
    char parameters[120];
    int status;
    char delimiter[2] = " ";
    char* token;
    char* str[10];
    int i = 0;

while(true) {

        printf("Type command: ");
        fgets(parameters, 120, stdin);

    if (fork() != 0) {
        /* Parent Code */
        waitpid(-1, &status, 0);
    } else {
        token = strtok(parameters, delimiter);

        while(token != NULL) {
            token = strtok(NULL, delimiter);
            *str[i++] = *token;
        }

        execvp(command,str);

        if(status == -1) {
            printf("invalid command\n");
        }
    }
}
    return 0;
}

