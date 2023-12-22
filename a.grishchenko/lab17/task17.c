#define ERASE '\x7F'  // Backspace
#define KILL 0x15     // Ctrl-U
#define CTRL_W 0x17   // CTRL-W
#define CTRL_D 0x04   // CTRL-D
#define CTRL_G '\x07' // TUDUDUM!!!! mya he he he
#define MAX_LENGTH 40

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    char line[MAX_LENGTH + 1];
    int curr = 0;

    while(1){
        char symb;
        symb = getchar();

        switch (symb){
        case ERASE:
            if (curr > 0){
                curr -= 1;
                line[curr] = '\0';
                printf("\b \b");
            }
            else{
                printf("\a");
            }  
        case KILL:
            while (curr > 0){
                curr -= 1;
                line[curr] = '\0';
                printf("\b \b");
            }
        case CTRL_W:
            while (curr > 0 && line[curr - 1] == ' '){
                curr -= 1;
                line[curr] = '\0';
                printf("\b \b");
            }

            while (curr > 0 && line[curr - 1] != ' '){
                curr -= 1;
                line[curr] = '\0';
                printf("\b \b");
            }
        case CTRL_D:
            if (curr == 0) {
                break;
            }
            else printf("\a");

        default:
            if (symb >= 32 && symb <= 126){
                line[curr] = symb;
                curr += 1;
                line[curr] = '\0';
                printf("%c", symb);
            }
            else{
                printf("\a%c", CTRL_G);
            }
        }
        fflush(stdout);
    }

    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}