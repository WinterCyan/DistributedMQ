//
// Created by Winter Cyan on 2020/5/26.
//

#ifndef DISTRIBUTEDMQ_Q_HPP
#define DISTRIBUTEDMQ_Q_HPP

//#include "SendMCA.hpp"
#include "Msg.hpp"
#include <string>

#define PERMS 0644

class Q {
private:
    std::string name;
    key_t key;
    int id;
    int msgNum = 0;

public:
    Msg *inMsg;
    Msg *outMsg;

    Q(std::string);
    int getId();
    int getMsgNum();
    std::string getName();

    virtual int putMsg(Msg *msg);
    void popMsg();
};


#endif //DISTRIBUTEDMQ_Q_HPP
