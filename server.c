#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
    // check if arguments are passed
    if (argc != 2) {
        printf("Usage: ./socket <port>\n");
        return 1;
    }


    long port = strtol(argv[1], NULL, 10);
    printf("Opening socket to port %ld\n", port);

    // create socket file description and validate
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        printf("socket creation failed\n");
        return -1;
    }
    printf("socket successfully created\n");

    // struct for an ipv4 socket description
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;           // ipv4
    addr.sin_addr.s_addr = INADDR_ANY;   // anyone
    addr.sin_port = htons(port);         // port 8080

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind failed");
        close(server_fd);
        return 1;
    }
    printf("bind successful\n");

    listen(server_fd, 5);
    printf("Listening for incoming connections on port %ld\n", port);

    int client_fd = accept(server_fd, NULL, NULL);
    printf("accepted fd: %d\n", client_fd);


    // validate closing socket
    if (close(server_fd) == -1) {
        printf("close failed\n");
    }
    printf("socket successfully closed\n");
    return 0;
}