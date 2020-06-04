// listen & accept connection
// standard C
#include <cstdio>
#include <cstdlib>
// others
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9090
#define BUFFER_SIZE 1024
int main() {
    int server_fd, new_socket;
    char buffer[BUFFER_SIZE] = {};
    struct sockaddr_in addr;
    int addr_len = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("create server socket failed.");
        exit(EXIT_FAILURE);
    }
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind failed.");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 5) < 0) {
        perror("listen failed.");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr*) &addr, (socklen_t*)&addr_len)) < 0) {
        perror("accept failed.");
        exit(EXIT_FAILURE);
    }
    while ((read(new_socket, buffer, BUFFER_SIZE))>0) {
        printf("rcv: %s\n", buffer);
        char hi[] = "hi, i rcved your msg.";
        send(new_socket, hi, sizeof(hi), 0);
        printf("snd: %s\n", hi);
    }
}