//
// Created by Winter Cyan on 2020/5/26.
//

#ifndef DISTRIBUTEDMQ_SENDMCA_HPP
#define DISTRIBUTEDMQ_SENDMCA_HPP

#include "Msg.hpp"
#include "param.hpp"
class RemoteQ;

class SendMCA {
private:
    RemoteQ* owner;
    int establishConn();
    void start();
    void sleep();
    int deliverMsg(Msg*);

public:
    MCA_STATUS status = STOPPED;
    SendMCA(RemoteQ*);
    void run();

};


#endif //DISTRIBUTEDMQ_SENDMCA_HPP
