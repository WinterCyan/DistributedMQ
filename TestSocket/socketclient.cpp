// client: establish connection
#include <cstdio>
#include <cstdlib>
#include <string>
#include <time.h>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9090
#define BUFFER_SIZE 1024
int main() {
    int client_fd;
    char buffer[BUFFER_SIZE] = {};
    struct sockaddr_in srv_addr;
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &srv_addr.sin_addr)<=0){
        perror("address error.");
        exit(EXIT_FAILURE);
    }
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("create client socket failed.");
        exit(EXIT_FAILURE);
    }
    if (connect(client_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr)) < 0) {
        perror("connection failed.");
        exit(EXIT_FAILURE);
    }
    char* hello = "hello, i am client";
    while (true) {
        send(client_fd, hello, strlen(hello), 0);
        printf("snd: %s\n", hello);
        read(client_fd, buffer, sizeof(buffer));
        printf("rcv: %s\n", buffer);
        sleep(3);
    }
}