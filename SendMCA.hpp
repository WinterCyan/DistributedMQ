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
    int client_socket_fd;
    char buffer[BUFFER_SIZE] = {};
    struct sockaddr_in srv_addr;
    std::string destIP;
    int establishConn();
    void start();
    void sleep();
    int deliverMsg(Msg*);

public:
    MCA_STATUS status = STOPPED;
    SendMCA(RemoteQ*);

    [[noreturn]] void run();

};


#endif //DISTRIBUTEDMQ_SENDMCA_HPP
