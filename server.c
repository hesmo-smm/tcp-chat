#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

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

    //f*ck em up dis my port
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
        return 1;
    }
    printf("bind successful\n");

    listen(server_fd, 5);
    printf("Listening for incoming connections on port %ld\n", port);
    int new_socket = accept(server_fd, (struct sockaddr*)&addr, &addr_len);
    printf("accepted fd: %d\n", new_socket);

    // reading. must remove last for \0
    ssize_t valread = read(new_socket, buffer, 1024 - 1);
    printf("%s\n", buffer);
    printf("read returned %ld\n", valread);
    char* hello = "Hello from server";
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");




    // validate closing socket
    if (close(server_fd) == -1) {
        printf("close failed\n");
    }
    if (close(new_socket) == -1) {
        printf("close failed: new_socket\n");
    }
    return 0;
}