//
// Created by d34d on 1/31/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// function for getting input
void get_input(char* buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}
void close_socket(int socket_fd) {
    if (close(socket_fd) < 0) {
        perror("close");
    }
}
void get_and_send_message(int client_fd, char* input, size_t size) {
    // our buffer
    if (send(client_fd, input, size, 0) < 0) {
        perror("send");
    }
    printf("[SERVER]: message sent\n");
}

int read_message(int client_fd, char* buffer, size_t size) {
    memset(buffer, 0, size);
    ssize_t valread = read(client_fd, buffer, size -1);
    if (valread < 0) {
        perror("read");
        exit(1);
    } else if (valread == 0) {
        printf("[CLIENT]: connection closed\n");
        return -1;
    } else {
        printf("[CLIENT]: %s\n", buffer);
        return 0;
    }

}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }
    char buffer[1024] = {0};

    // get port from arg
    long port = strtol(argv[1], NULL, 10);

    //opening socket
    printf("Opening socket to port %ld\n", port);
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    //validating
    if (client_fd < 0) {
        perror("socket");
        exit(1);
    }
    printf("socket created\n");

    // creating socket struct for address info
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // connecting and validating
    int status = connect(client_fd, (struct sockaddr *)&addr, sizeof(addr));
    if (status < 0) {
        perror("connect");
        exit(1);
    }
    printf("Connected\n");

    //get_and_send_message(client_fd);
    //read_message(client_fd, buffer, sizeof(buffer));
    char input[1024] = {0};
    int pipp =0;

    while (1) {
        printf("What would you like to send?:\n");
        get_input(input, sizeof(input));
        if (strcmp(input, "quit") == 0 ||pipp == -1 ) {
            break;
        }
        get_and_send_message(client_fd, input, strlen(input));
        pipp = read_message(client_fd, buffer, sizeof(buffer));



    }
    close_socket(client_fd);


    return 0;
}
