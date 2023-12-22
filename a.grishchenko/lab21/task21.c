#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int counter = 0;

void sigint() {
    printf("\tTUDUDUM!!!!!!\a\n");
    counter++;
}

void sigquit() {
    printf("\nTotal TUDUDUMs count: %d\n", counter);
    exit(0);
}

int main() {
    while (1) {
        signal(SIGINT, sigint);
        signal(SIGQUIT, sigquit);
    }
    return 0;
}