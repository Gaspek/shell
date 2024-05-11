#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


void change_dir(char *args[]) {
    if(strcmp(args[0], "cd") == 0) {
        if(args[1] != NULL) {
            if(chdir(args[1]) != 0) {
                perror("chdir");
            }
        } else {
            chdir(getenv("HOME"));
        }
    }
}

char* print_prompt() {
    char* cwd = malloc(1024 * sizeof(char)); // Dynamically allocate memory for cwd
    if (cwd == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if (getcwd(cwd, 1024) != NULL) {
        return cwd;
    } else {
        perror("getcwd");
        free(cwd); // Free allocated memory in case of error
        return NULL;
    }
}