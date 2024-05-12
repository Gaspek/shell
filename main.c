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

// Signal handler function for SIGQUIT
void sigquit_handler(int signum) {
    if (signum == SIGQUIT) {
        printf("Received SIGQUIT signal. Printing entire history:\n");
        print_history();
    }
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]){	
    char *clear[0];
    clear[0] = "clear";
    execute(clear, 0); 
    char* history_path = get_history_file_path();
    char *args[MAX_ARGS+1];
    char input[BUFSIZ];
    // Set up signal handler for SIGQUIT
    signal(SIGQUIT, sigquit_handler);
    while(printf("%s> ", print_prompt()) && fgets(input, BUFSIZ, stdin) != NULL){ //Get input and print out FOR NOW PLACEHOLDER TO CHANGE
        if (input[0] == '\n' || input[0] == ' ') {
            continue; // Empty command
        }
        input[strcspn(input, "\n")] = '\0';
        //printf("Command entered: %s\n", input);  //Testing confirmation
        com_history(input);
        
        char *token = strtok(input, " ");
        int i = 0;
        
        while (token != NULL) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
            if(i >= MAX_ARGS) 
            {
                break;
            }
        }
        if(strcmp(args[0], "history") == 0){
            print_history();
            continue;
        }
        if(strcmp(args[0], "exit") == 0) {
            break;
        }
        args[i] = NULL;
        int j = 0;
        int background = 0;
        char *output_file = NULL;
        char *pipeline[MAX_ARGS];
        int num_commands = 0;
        while(args[j] != NULL){
            if (strcmp(args[j], "&") == 0){
                background = 1;
                args[j] = NULL;
                if(args[j+1] != NULL){
                    fprintf(stderr, "Syntax error\n");
                    break;
                }
            }
            else if(strcmp(args[j], ">") == 0){
                if(args[j+1] == NULL){
                    fprintf(stderr, "Syntax error\n");
                    break;
                }
                output_file = args[j+1];
                args[j] = NULL;
                args[j+1] = NULL;
                redirect_output(args, output_file);
                break;
            }
            else if(strcmp(args[j], ">>") == 0){
                if(args[j+1] == NULL){
                    fprintf(stderr, "Syntax error\n");
                    break;
                }
                output_file = args[j+1];
                args[j] = NULL;
                args[j+1] = NULL;
                redirect_output_append(args, output_file);
                break;
            }
            j++;
        }
        if (output_file == NULL) {
            execute(args, background);
        }
        
        // Check if the command is "cd"
        if (strcmp(args[0], "cd") == 0) {
            if(i < 2){
                fprintf(stderr, "cd: missing argument\n");
            }
            change_dir(args); // Call the change_dir function
            continue; // Skip the rest of the loop
        }
        
        // Add code to handle other commands

        //execute_program(args[0],args[1]);
    }
    return EXIT_SUCCESS;
}

