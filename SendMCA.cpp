//
// Created by Winter Cyan on 2020/5/26.
//

#include <iostream>
#include <unistd.h>
#include <thread>
#include "SendMCA.hpp"
#include "RemoteQ.hpp"

using namespace std;

// should MCA run as a new thread?
[[noreturn]] void SendMCA::run(void) {
    cout<<owner->getName()<<" run invoked."<<endl;
    status = RUNNING;
    launchRemoteServer();
//    establishConn();
    for (;;) {
//        usleep(10000);
//        usleep(100000);
        owner->popMsg(); // get msg from queue
//        deliverMsg(owner->msg); // deliver queue
    }
}

int SendMCA::deliverMsg(Msg *msg) {
//    send(client_socket_fd, msg->msgText, MSG_SZ, 0);
    char* sig = "launch";
    send(client_socket_fd, sig, sizeof(sig), 0);
    cout<<"deliver "<<msg->msgText+20<<" to "<<owner->getName()<<endl;
}

SendMCA::SendMCA(RemoteQ* remoteQ) {
    owner = remoteQ;
    // init of socket params
//    srv_addr.sin_family = AF_INET;
//    srv_addr.sin_port = htons(PORT);
//    destIP = "127.0.0.1";
}

int SendMCA::establishConn() {
    // establish TCP connection
    if (inet_pton(AF_INET, destIP.c_str(), &srv_addr.sin_addr)<=0) {
        perror("address err.");
        exit(EXIT_FAILURE);
    }
    if ((client_socket_fd = socket(AF_INET,SOCK_STREAM,0)) == 0) {
        perror("create socket client failed.");
        exit(EXIT_FAILURE);
    }
    if (connect(client_socket_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr))<0) {
        perror("connection err.");
        exit(EXIT_FAILURE);
    }
    cout<<"TCP connection of "<<owner->getName()<<"'s sendMCA established."<<endl;
    return 0;
}

void SendMCA::launchRemoteServer() {
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(PORT);
    destIP = "127.0.0.1";

    if (inet_pton(AF_INET, destIP.c_str(), &srv_addr.sin_addr)<=0) {
        perror("address err.");
        exit(EXIT_FAILURE);
    }
    if ((client_socket_fd = socket(AF_INET,SOCK_STREAM,0)) == 0) {
        perror("create socket client failed.");
        exit(EXIT_FAILURE);
    }
    if (connect(client_socket_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr))<0) {
        perror("connection err.");
        exit(EXIT_FAILURE);
    }

    char* sig = "launch";
    send(client_socket_fd, sig, sizeof(sig), 0);
    cout<<"send launch sig of "<<owner->getName()<<endl;
    char buffer[BUFFER_SIZE] = {};
    while (read(client_socket_fd, buffer, BUFFER_SIZE)>0) {
//         when done, close create-connection
//        if (strcmp(buffer,"done")==0) {
        if (memcmp(buffer,"done",4)==0) {
            close(client_socket_fd);
            cout<<"new socket server created, create-connection closed."<<endl;
            return;
        }
    }
}
