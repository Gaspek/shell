#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define MAX_PATH_LENGTH 1024

char* get_bin_path() {
    char* path_env = getenv("PATH"); // Pobierz zmienną PATH
    if (path_env == NULL) {
        perror("getenv");
        return NULL;
    }

    char* path_copy = strdup(path_env); // Skopiuj zmienną PATH, aby nie zmieniać oryginału
    if (path_copy == NULL) {
        perror("strdup");
        return NULL;
    }

    char* token = strtok(path_copy, ":"); // Podziel ścieżki za pomocą dwukropka
    while (token != NULL) {
        char* bin_path = (char*)malloc(MAX_PATH_LENGTH); // Utwórz bufor na ścieżkę do folderu "bin"
        if (bin_path == NULL) {
            perror("malloc");
            free(path_copy);
            return NULL;
        }

        snprintf(bin_path, MAX_PATH_LENGTH, "%s/bin", token); // Sklej ścieżkę do folderu "bin"
        
        if (access(bin_path, F_OK) != -1) { // Sprawdź czy istnieje folder "bin"
            free(path_copy);
            return bin_path;
        }

        free(bin_path);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    fprintf(stderr, "Folder bin nie został znaleziony w zmiennej PATH.\n");
    return NULL;
}

void execute_program(char *program_name, char *args[]) {
    // Wywołanie funkcji execvp, która szuka programu w ścieżkach systemowych
    // i wykonuje go z podanymi argumentami
    if (execvp(program_name, args) == -1) {
        // Jeśli execvp zwróciło się z błędem, wyświetlamy komunikat o błędzie
        perror("execvp");
        // I kończymy działanie programu
        exit(EXIT_FAILURE);
    }
}