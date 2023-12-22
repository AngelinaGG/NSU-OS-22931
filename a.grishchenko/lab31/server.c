#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <ctype.h>

#define MAX_CLIENTS 20
#define SOCKET_PATH "/tmp/socket"

int main() {
    int client_sock, sockfd, activity, i;
    int client_sockets[MAX_CLIENTS];
    fd_set readfds;
    struct sockaddr_un address;
    char buffer[256];

    int server_sock = socket(AF_UNIX, SOCK_STREAM, 0);

    memset(&address, 0, sizeof(struct sockaddr_un));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, SOCKET_PATH, sizeof(address.sun_path) - 1);

    bind(server_sock, (struct sockaddr *)&address, sizeof(struct sockaddr_un));

    listen(server_sock, MAX_CLIENTS);

    for (i = 0; i < MAX_CLIENTS; i++) {
        client_sockets[i] = 0;
    }

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_sock, &readfds);

        sockfd = server_sock;

        for (i = 0; i < MAX_CLIENTS; i++) {
            if (client_sockets[i] > 0) FD_SET(client_sockets[i], &readfds);
            if (client_sockets[i] > sockfd) sockfd = client_sockets[i];
        }

        activity = select(sockfd + 1, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(server_sock, &readfds)) {
            client_sock = accept(server_sock, NULL, NULL);

            for (i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == 0) {
                    printf("\nClient %d connected\n", i);
                    client_sockets[i] = client_sock;
                    break;
                }
            }
        }

        for (i = 0; i < MAX_CLIENTS; i++) {
            if (FD_ISSET(client_sockets[i], &readfds)) {
                if ((read(client_sockets[i], buffer, 256)) == 0) {
                    getpeername(client_sockets[i], (struct sockaddr *)&address, (socklen_t *)&address);
                    printf("\nClient %d disconnected\n", i);
                    close(client_sockets[i]);
                    client_sockets[i] = 0;
                }

                else {
                    int lena = strlen(buffer);
                    for (int j = 0; j < lena; j++) buffer[j] = toupper(buffer[j]);

                    if (i == 0 && buffer[0] == '_' && buffer[1] == 'E' && buffer[2] == 'X'){
                        close(server_sock);
                        unlink(SOCKET_PATH);
                        printf("Connection closed\n");
                        return 0;
                    }
                    printf("Client %d: %s", i, buffer);
                }
            }
            memset(buffer, 0, 256);
        }
    }

    close(server_sock);
    unlink(SOCKET_PATH);
    return 0;
}