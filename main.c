// main.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h> // Include this for chdir
#include "read.h"
#include "history.h"
#include "change.h"
#include <signal.h> // Include this for signal handling

#define MAX_ARGS 10

void print_prompt() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s> ", cwd);
    } else {
        perror("getcwd");
    }
}



int main(int argc, char *argv[]) {    
    char *args[MAX_ARGS + 1];
    char command[100];
    char *history_path = get_history_file_path();
    FILE *history_file = fopen(history_path, "r");
    
    if (history_file != NULL) {
        char history_line[100];
        printf("Command history:\n");
        
        while (fgets(history_line, sizeof(history_line), history_file) != NULL) {
            printf("%s", history_line);
        }
        
        fclose(history_file);
    }
    
    while (1) {
        printf(":) ");
        print_prompt();        
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("fgets returned NULL\n");
            break;
        }
        
        command[strcspn(command, "\n")] = '\0';
        printf("Command entered: %s\n", command);
        
        // Update command history
        com_history(command);
        
        // Tokenize command
        char *token = strtok(command, " ");
        int i = 0;
        
        while (token != NULL) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
            
            if (i >= MAX_ARGS) {
                break;
            }
        }
        
        args[i] = NULL;
        
        // Check if the command is "cd"
        if (strcmp(args[0], "!") == 0) {
            change_dir(args); // Call the change_dir function
            continue; // Skip the rest of the loop
        }
        
        // Add code to handle other commands
    }
    
    return EXIT_SUCCESS;
}
