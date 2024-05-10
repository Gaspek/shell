#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void printFileContent(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error 404");
        exit(EXIT_FAILURE);
    }

    unsigned char buffer[32];
    ssize_t bytes_read;
    int i;

    do {
        bytes_read = read(fd, buffer, sizeof(buffer));
        for (i = 0; i < bytes_read; ++i) {
            if (buffer[i] >= 32 && buffer[i] <= 126)
                printf("%c", buffer[i]);
            else if (buffer[i]=='\n')
                printf("\n"); 
            else
                printf("#ERROR#");
        }
    } while (bytes_read > 0);
    printf("\n");

    close(fd);
}