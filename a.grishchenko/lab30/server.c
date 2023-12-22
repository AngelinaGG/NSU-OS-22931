#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <ctype.h>

#define SOCKET_PATH "/tmp/socket5"

int main() {
    int server_fd, client_fd;
    socklen_t len;
    struct sockaddr_un server_addr, client_addr;
    char buffer[256];

    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_un);

    listen(server_fd, 1);

    len = sizeof(struct sockaddr_un);

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
    while(1){
        memset(buffer, 0, 256);
        recv(client_fd, buffer, sizeof(buffer), 0);

        int lena = strlen(buffer);
        for (int i = 0; i < lena; i++) buffer[i] = toupper(buffer[i]);

        if (strcmp("_EXIT", buffer) == 0){
            printf("Connection closed\n");
            break;
        }
        else printf("Received message: %s\n", buffer);
    }

    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH);

    return 0;
}
