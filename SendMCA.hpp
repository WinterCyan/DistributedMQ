//
// Created by Winter Cyan on 2020/5/26.
//

#ifndef DISTRIBUTEDMQ_SENDMCA_HPP
#define DISTRIBUTEDMQ_SENDMCA_HPP

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "Msg.hpp"
#include "param.hpp"
class RemoteQ;

class SendMCA {
private:
    RemoteQ* owner;
    int daemon_client_fd;
    int data_client_fd;
    struct sockaddr_in daemon_addr;
    struct sockaddr_in data_addr;
    char buffer[BUFFER_SIZE] = {};
    std::string destIP;
    int establishDataConn(int);
    void touchDaemon();
    void start();
    void sleep();
    int deliverMsg(Msg*);

public:
    MCA_STATUS status = STOPPED;
    SendMCA(RemoteQ*);

    [[noreturn]] void run();

};


#endif //DISTRIBUTEDMQ_SENDMCA_HPP
