#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>



void execute(char *args[], int background) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        if (background) {
            setpgid(0, 0);
        }
        execvp(args[0], args);
        perror("exec");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        if (!background) {
            waitpid(pid, NULL, 0);
        }
    }
}

void redirect_output(char *args[], char *output_file) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (fd < 0) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        // Redirect stdout to the file
        if (dup2(fd, STDOUT_FILENO) < 0) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(fd);
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else { // Parent process
        waitpid(pid, NULL, 0);
    }
}

void redirect_output_append(char *args[], char *output_file) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        int fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
        if (fd < 0) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        // Redirect stdout to the file
        if (dup2(fd, STDOUT_FILENO) < 0) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(fd);
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else { // Parent process
        waitpid(pid, NULL, 0);
    }
}