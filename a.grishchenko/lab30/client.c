#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/socket5"

int main() {
    int client_fd;
    struct sockaddr_un server_addr;
    char message[256];

    (client_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    connect(client_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_un);

    while(strcmp("_exit", message) != 0){
        memset(message, 0, 256);
        scanf("%s", message);
        if (send(client_fd, message, strlen(message), 0) == -1){
            perror("send");
            exit(EXIT_FAILURE);
        }
    }
    close(client_fd);

    return 0;
}
