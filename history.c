#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_HISTORY 20

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
    return history_path;
}

void com_history(char *command) {
    char* history_path = get_history_file_path();
    FILE *file = fopen(history_path, "r+");
    if (file != NULL) {
        // Read existing history
        char history[MAX_HISTORY][100];
        int count = 0;
        while (fgets(history[count % MAX_HISTORY], sizeof(history[0]), file) != NULL) {
            count++;
        }
        // Move to the beginning of the file
        rewind(file);
        // Write the new command and the latest 19 commands
        fprintf(file, "%s\n", command);
        int i;
        for (i = 0; i < MAX_HISTORY && i < count; i++) {
            fprintf(file, "%s", history[(count - i) % MAX_HISTORY]);
        }
        fclose(file);
    } else {
        perror("fopen");
    }
    free(history_path);
}