#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>


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
    // check if arguments are passed
    if (argc != 2) {
        printf("Usage: ./socket <port>\n");
        exit(1);
    }
    char buffer[1024] = { 0 };
    int opt = 1;


    long port = strtol(argv[1], NULL, 10);
    printf("Opening socket to port %ld\n", port);

    // create socket file description and validate
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        printf("socket creation failed\n");
        return -1;
    }
    printf("socket successfully created\n");

    // all i know is that i can use my port back2back
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
                   }

    // struct for an ipv4 socket description
    struct sockaddr_in addr = {0};
    socklen_t addr_len = sizeof(addr);
    addr.sin_family = AF_INET;           // ipv4
    addr.sin_addr.s_addr = INADDR_ANY;   // anyone
    addr.sin_port = htons(port);         // port 8080

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind failed");
        close(server_fd);
        exit(1);
    }
    printf("bind successful\n");

    listen(server_fd, 5);
    printf("Listening for incoming connections on port %ld\n", port);
    int new_socket = accept(server_fd, (struct sockaddr*)&addr, &addr_len);
    printf("accepted fd: %d\n", new_socket);
    char input[1024] = {0};

    while (1) {
        int status = read_message(new_socket, buffer, sizeof(buffer));
        printf("What would you like to send?:\n");
        get_input(input, sizeof(input));
        if (strcmp(input, "quit") == 0 ||status == -1 ) {
            break;
        }
        get_and_send_message(new_socket, input, strlen(input));
    }


    // validate closing socket
    close_socket(server_fd);
    close_socket(new_socket);
    return 0;
}