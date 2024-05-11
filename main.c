#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "read.h"
#include "history.h"
#include "change.h"

#define MAX_ARGS 10

int main(int argc, char *argv[]){    
    char *args[MAX_ARGS +1];
    char command[100];
    char* history_path = get_history_file_path();
    FILE *history_file = fopen(history_path, "r");
    if(history_file != NULL)
    {
        char history_line[100];
        printf("Command history:\n");
        while(fgets(history_line, sizeof(history_line), history_file) != NULL)
        {
            printf("%s", history_line);
        }
        fclose(history_file);
    }
    else
    {
        perror("fopen");
    }
    while(1) 
    {
        printf(":) ");
        if(fgets(command, sizeof(command), stdin) == NULL )
        {
            printf("fgets returned NULL\n"); // Add a print statement to check if fgets returns NULL
            break;
        }
        command[strcspn(command, "\n")] = '\0';
        printf("Command entered: %s\n", command);
        com_history(command);
    }
    if (argc < 2) {
        fprintf(stderr, "Error 403 to few arguments. Use: %s file_name\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 1; i < argc; i++) {
        printf("Zawartość pliku %s:\n", argv[i]);
        printFileContent(argv[i]);
        printf("\n");
    }

    char *token = strtok(command, " ");
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
    args[i] = NULL;


    return EXIT_SUCCESS;
}