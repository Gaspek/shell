#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_ARGS 10

char* get_history_file_path() {
    char* home_dir = getenv("HOME");
    if (home_dir == NULL) {
        fprintf(stderr, "Error: HOME environment variable not set.\n");
        exit(EXIT_FAILURE);
    }
    char* history_path = malloc(strlen(home_dir) + strlen("/history_log.txt") + 1);
    if (history_path == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    sprintf(history_path, "%s/history_log.txt\n", home_dir);
    printf("%s", history_path);
    return history_path;
}

void com_history(char *command) {
    char* history_path = get_history_file_path();
    FILE *file = fopen(history_path, "a");
    if(file != NULL) 
    {
        fprintf(file, "%s\n", command);
        printf("Command added to history: %s\n", command);
        fclose(file);
    }
    else
    {
        perror("fopen");
    }
    free(history_path);
}