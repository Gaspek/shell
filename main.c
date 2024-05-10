#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "read.h"

int main(int argc, char *argv[]){	
    if (argc < 2) {
        fprintf(stderr, "Error 403 to few arguments. Use: %s file_name\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 1; i < argc; i++) {
        printf("Zawartość pliku %s:\n", argv[i]);
        printFileContent(argv[i]);
        printf("\n");
    }

    return EXIT_SUCCESS;
}

