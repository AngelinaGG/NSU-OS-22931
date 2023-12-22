#define CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>

#define SOCKET_PATH "/tmp/socket"

int main() {
    int client_fd;
    struct sockaddr_un server_addr;
    char message[256];

    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    connect(client_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_un));

    while(message[0] != '_' || message[1] != 'e' || message[2] != 'x'){
        time_t tim;
        memset(message, 0, 256);
        gets(message);
        tim = time(NULL);
        strcat(message, "    _time: ");
        strcat(message, asctime(localtime(&tim)));
        send(client_fd, message, strlen(message), 0);
    }
    close(client_fd);

    return 0;
}
