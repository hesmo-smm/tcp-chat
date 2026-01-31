//
// Created by d34d on 1/31/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>  // für inet_addr()


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }
    char buffer[1024] = {0};

    long port = strtol(argv[1], NULL, 10);
    printf("Opening socket to port %ld\n", port);
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("socket created\n");
    if (client_fd < 0) {
        perror("socket");
        exit(1);
    }
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int status = connect(client_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (status < 0) {
        perror("connect");
        exit(1);
    }
    printf("Connected\n");

    char* hello = "Hello from Client";
    send(client_fd, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    ssize_t valread = read(client_fd, buffer, 1024 - 1);
    printf("read returned %ld\n", valread);
    printf("%s\n", buffer);
    if (close(client_fd) < 0) {
        perror("close");
    }
    return 0;
}
