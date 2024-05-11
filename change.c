#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


void change_dir(char *args[]) {
    if(strcmp(args[0], "!") == 0) {
        if(args[1] != NULL) {
            if(chdir(args[1]) != 0) {
                perror("chdir");
            }
        } else {
            chdir(getenv("HOME"));
        }
    }
}