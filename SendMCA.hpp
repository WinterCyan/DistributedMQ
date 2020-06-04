//
// Created by Winter Cyan on 2020/5/26.
//

#ifndef DISTRIBUTEDMQ_SENDMCA_HPP
#define DISTRIBUTEDMQ_SENDMCA_HPP


#include "RemoteQ.hpp"

class SendMCA {
private:
    RemoteQ* owner;
    int establishConn();
    void start();
    void sleep();
    int deliverMsg();

public:
    SendMCA();
    void run();

};


#endif //DISTRIBUTEDMQ_SENDMCA_HPP
