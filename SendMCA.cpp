//
// Created by Winter Cyan on 2020/5/26.
//

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
#include "SendMCA.hpp"
#include "RemoteQ.hpp"

using namespace std;

// should MCA run as a new thread?
[[noreturn]] void SendMCA::run(void) {
    cout<<owner->getName()<<" run invoked."<<endl;
    status = RUNNING;
    touchDaemon();
//    establishConn();
    for (;;) {
//        usleep(10000);
//        usleep(100000);
        owner->popMsg(); // get msg from queue
        deliverMsg(owner->msg); // deliver queue
    }
}

int SendMCA::deliverMsg(Msg *msg) {
    send(data_client_fd, msg->msgText, MSG_SZ, 0);
//    char* sig = "launch";
//    send(daemon_client_fd, sig, sizeof(sig), 0);
    cout<<"deliver "<<msg->msgText+20<<" to "<<owner->getName()<<endl;
}

SendMCA::SendMCA(RemoteQ* remoteQ) {
    owner = remoteQ;
    // init of socket params
//    srv_addr.sin_family = AF_INET;
//    srv_addr.sin_port = htons(PORT);
//    destIP = "127.0.0.1";
}

int SendMCA::establishDataConn(int port) {
    data_addr.sin_family = AF_INET;

    data_addr.sin_port = port; // different if use htons()
    destIP = "127.0.0.1";
    // establish TCP connection
    if (inet_pton(AF_INET, destIP.c_str(), &data_addr.sin_addr) <= 0) {
        perror("address err.");
        exit(EXIT_FAILURE);
    }
    if ((data_client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("create socket client failed.");
        exit(EXIT_FAILURE);
    }
    if (connect(data_client_fd, (struct sockaddr*)&data_addr, sizeof(data_addr)) < 0) {
        perror("connection err.");
        exit(EXIT_FAILURE);
    }
    cout<<"data connection with remote port "<<port<<" established."<<endl;
//    return data_client_fd;
}

void SendMCA::touchDaemon() {
    daemon_addr.sin_family = AF_INET;
    daemon_addr.sin_port = htons(PORT);
    destIP = "127.0.0.1";

    if (inet_pton(AF_INET, destIP.c_str(), &daemon_addr.sin_addr) <= 0) {
        perror("address err.");
        exit(EXIT_FAILURE);
    }
    if ((daemon_client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("create socket client failed.");
        exit(EXIT_FAILURE);
    }
    if (connect(daemon_client_fd, (struct sockaddr*)&daemon_addr, sizeof(daemon_addr)) < 0) {
        perror("connection err.");
        exit(EXIT_FAILURE);
    }
    cout<<"daemon connection established."<<endl;

    char* sig = "launch";
    send(daemon_client_fd, sig, sizeof(sig), 0);
    char buffer[BUFFER_SIZE] = {};
    while (read(daemon_client_fd, buffer, BUFFER_SIZE) > 0) {
        // when done, close daemon-connection
        if (memcmp(buffer,FIN_SIG,4)==0) {
            send(daemon_client_fd, new char*(FIN_SIG), sizeof(FIN_SIG), 0);
            close(daemon_client_fd);
            cout<<"daemon connection closed."<<endl;
            int port = stoi(buffer+4);
            ::sleep(1);
            establishDataConn(port);
        }
    }
}
