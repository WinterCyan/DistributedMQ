// listen & accept connection
// standard C
#include <cstdio>
#include <cstdlib>
// others
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include "../param.hpp"

#define PORT 9090
#define BUFFER_SIZE 1024
extern void createNewDataSock(int);
extern void runningDataSocket(int, struct sockaddr*, socklen_t*);
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
        new std::thread(createNewDataSock, new_socket);
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
void createNewDataSock(int new_socket) {
    char buffer[BUFFER_SIZE] = {};
    while (read(new_socket, buffer, BUFFER_SIZE)>0) {
        if (strcmp(buffer,LAUNCH_SIG)==0) {
            // create new data socket
            struct sockaddr_in data_sock_addr;
            data_sock_addr.sin_family = AF_INET;
            data_sock_addr.sin_addr.s_addr = INADDR_ANY;
            data_sock_addr.sin_port = 0;
            int data_addr_len = sizeof(data_sock_addr);
            int data_sock_fd;
            if ((data_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
                perror("create server socket failed.");
                exit(EXIT_FAILURE);
            }
            if (bind(data_sock_fd, (struct sockaddr *)&data_sock_addr, sizeof(data_sock_addr)) < 0) {
                perror("bind failed.");
                exit(EXIT_FAILURE);
            }
            if (listen(data_sock_fd, 1) < 0) {
                perror("listen failed.");
                exit(EXIT_FAILURE);
            }
            struct sockaddr* pAddr = (sockaddr*)&data_sock_addr;
            socklen_t* pLen = (socklen_t*)&data_addr_len;
            new std::thread(runningDataSocket, data_sock_fd, pAddr, pLen);
            sleep(1);
//            runningDataSocket(data_sock_fd,pAddr,pLen);
//            auto s = socket(AF_INET,SOCK_STREAM,0);
//            bind(s, (struct sockaddr*)&data_sock_addr, sizeof(data_sock_addr));
//            if (listen(s, 1) < 0) {
//                perror("listen failed.");
//                exit(EXIT_FAILURE);
//            }
            socklen_t sz = sizeof(data_sock_addr);
            getsockname(data_sock_fd, (struct sockaddr*)&data_sock_addr, &sz);
            auto p = (int)data_sock_addr.sin_port;
            // send back port number
            auto port_info = FIN_SIG + std::to_string(p);
            std::cout << "port number: " << port_info.c_str()+4 << std::endl;
            send(new_socket, port_info.c_str(), sizeof(port_info), 0);
        }
        if (strcmp(buffer,FIN_SIG)==0) { // finish create-connection and terminate the thread
            std::cout<<"daemon connection closed."<<std::endl;
            return;
        }
    }
}

void runningDataSocket(int fd, struct sockaddr* addr, socklen_t* len) {
    int new_socket;
    std::cout<<"data socket listening, ";
    while ((new_socket = accept(fd, addr, len))>=0) {
        char buffer[BUFFER_SIZE] = {};
        while (read(new_socket, buffer, BUFFER_SIZE)>0) {
            std::cout<<"data socket rcv msg: "<<buffer+20<<std::endl;
        }
    }
}
