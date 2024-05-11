#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "read.h"
#include "history.h"
#include "change.h"
#include "execute.h"

#define MAX_ARGS 100

int main(int argc, char *argv[]) {    
    char* history_path = get_history_file_path();
    char *args[MAX_ARGS+1];
    char input[BUFSIZ];
    while(printf("%s> ", print_prompt()) && fgets(input, BUFSIZ, stdin) != NULL) {
        if(input[0] == 'h') {
            print_history(history_path);
        }
        input[strcspn(input, "\n")] = '\0';
        printf("Command entered: %s\n", input);
        
        // Add the entered command to the history
        com_history(input);
        
        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
            if(i >= MAX_ARGS) {
                break;
            }
        }
        args[i] = NULL;

        // Check if the command is "cd"
        if (strcmp(args[0], "cd") == 0) {
            change_dir(args);
            continue;
        }
        
        // Add code to handle other commands
    }
    return EXIT_SUCCESS;
}
