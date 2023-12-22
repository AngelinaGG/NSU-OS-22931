#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void write_pipe(int file){
    FILE *stream;
    FILE *test;
    stream = fdopen(file, "w");

    test = fopen("test25.txt", "r");
    if (!test) {
        fprintf(stderr, "Error opening test file");
        exit(0);
    }

    char buffer[256];
    while (fgets(buffer, 256, test)){
        fprintf(stream, "%s", buffer);
    }

    fclose(test);
    fclose(stream);
}

void read_pipe(int file){
    FILE* stream;
    int c;
    stream = fdopen(file, "r");
    while ((c = fgetc(stream)) != EOF){
        putchar(toupper(c));
    }
    fclose(stream);
}

int main() {
    int filedes[2];
    if (pipe(filedes)){
        printf("anything is bad :(");
        return EXIT_FAILURE;
    }
    pid_t pid = fork();
    switch (pid) {
    case -1:
        fprintf(stderr, "anythig is bad\n");
        return EXIT_FAILURE;
    case 0:
        read_pipe(filedes[0]);
        return 0;
    default:
        write_pipe(filedes[1]);
        return 0;
    }
    return 0;
}