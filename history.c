#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include "read.h"

#define MAX_COMMANDS 20
#define MAX_LINE_LENGTH 100

char* get_home_path() {
    char* home_dir = getenv("HOME");
    if (home_dir == NULL) {
        fprintf(stderr, "Error: HOME environment variable not set.\n");
        exit(EXIT_FAILURE);
    }
    return home_dir;
}

char* get_history_file_path() {
    char* home_dir = get_home_path();
    char* history_path = malloc(strlen(home_dir) + strlen("/history_log.txt") + 1);
    if (history_path == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    sprintf(history_path, "%s/history_log.txt", home_dir);
    return history_path;
}

void print_history(){
    char* history_path = get_history_file_path();
    printf("Command history:\n");
    printFileContent(history_path);
}

void com_history(char *command) {
    char* history_path = get_history_file_path();
    FILE *file = fopen(history_path, "r+");
    if(file != NULL) 
    {
        char lines[MAX_COMMANDS][MAX_LINE_LENGTH];
        int count = 0;
        
        // Read existing commands into memory
        while (fgets(lines[count], sizeof(lines[count]), file) != NULL) {
            count++;
            if (count >= MAX_COMMANDS) // limit reached
                break;
        }
        
        // Truncate the file if it contains more than 20 commands
        if (count >= MAX_COMMANDS) {
            FILE *temp_file = fopen("temp_history_log.txt", "w");
            if (temp_file == NULL) {
                perror("fopen");
                fclose(file);
                free(history_path);
                return;
            }
            
            // Write the last 20 commands to the temporary file
            for (int i = 1; i < count; i++) {
                fprintf(temp_file, "%s", lines[i]);
            }
            
            // Add the new command to the temporary file
            fprintf(temp_file, "%s\n", command);
            
            // Close both files
            fclose(file);
            fclose(temp_file);
            
            // Replace the original file with the temporary file
            remove(history_path);
            rename("temp_history_log.txt", history_path);
        }
        else {
            // Add the new command to the original file
            fseek(file, 0, SEEK_END);
            fprintf(file, "%s\n", command);
            fclose(file);
        }
    }
    else perror("fopen");
    free(history_path);
}