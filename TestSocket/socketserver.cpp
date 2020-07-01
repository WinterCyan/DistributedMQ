// listen & accept connection
// standard C
#include <cstdio>
#include <cstdlib>
// others
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <iostream>
#include <string>

#define PORT 9090
#define BUFFER_SIZE 1024
extern void execute_socket(int);
extern int launch_new();
int main() {
    int server_fd, new_socket;
//    char buffer[BUFFER_SIZE] = {};
    struct sockaddr_in addr;
    int addr_len = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
//    addr.sin_port = 0;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("create server socket failed.");
        exit(EXIT_FAILURE);
    }
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind failed.");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 4) < 0) {
        perror("listen failed.");
        exit(EXIT_FAILURE);
    }
//    socklen_t size = sizeof(addr);
//    auto p = getsockname(server_fd, (struct sockaddr *)&addr, &size);
//    std::cout<<"port: "<<addr.sin_port<<std::endl;
    while ((new_socket = accept(server_fd, (struct sockaddr*) &addr, (socklen_t*)&addr_len))>=0) {
        new std::thread(execute_socket, new_socket);
        std::cout<<"invoke new thread to launch new server("<<new_socket<<")."<<std::endl;
    }
//    if ((new_socket = accept(server_fd, (struct sockaddr*) &addr, (socklen_t*)&addr_len)) < 0) {
//        perror("accept failed.");
//        exit(EXIT_FAILURE);
//    }
//    while ((read(new_socket, buffer, BUFFER_SIZE))>0) {
//        printf("rcv: %s\n", buffer);
//        printf("rcv: %s\n", buffer+20);
//        char hi[] = "hi, i rcved your msg.";
//        send(new_socket, hi, sizeof(hi), 0);
//        printf("snd: %s\n", hi);
//    }
}
void execute_socket(int new_socket) {
    char buffer[BUFFER_SIZE] = {};
    while (read(new_socket, buffer, BUFFER_SIZE)>0) {
        printf("rcv: %s\n", buffer);
        if (strcmp(buffer,"launch")==0) {
//            launch_new();
            std::cout<<"launch new server..."<<std::endl;

            // create new server socket
            struct sockaddr_in new_srv_addr;
            int addr_len = sizeof(new_srv_addr);
            new_srv_addr.sin_family = AF_INET;
            new_srv_addr.sin_addr.s_addr = INADDR_ANY;
            new_srv_addr.sin_port = 0;
            auto s = socket(AF_INET,SOCK_STREAM,0);
            bind(s, (struct sockaddr*)&new_srv_addr, sizeof(new_srv_addr));
            socklen_t sz = sizeof(new_srv_addr);
            getsockname(s, (struct sockaddr*)&new_srv_addr, &sz);
            auto p = (int)new_srv_addr.sin_port;

            // send back port number
            auto doneinfo = std::to_string(p)+", done";
            send(new_socket,doneinfo.c_str(),4,0);
        }
        if (strcmp(buffer,"done")==0) { } // finish create-connection and terminate the thread
    }
}

int launch_new() {
}
