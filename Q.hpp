//
// Created by Winter Cyan on 2020/5/26.
//

#ifndef DISTRIBUTEDMQ_Q_HPP
#define DISTRIBUTEDMQ_Q_HPP

//#include "SendMCA.hpp"
#include "Msg.hpp"
#include <string>


class Q {
private:
    std::string name;
    int key; // ftok key
    int id; // msgget id

public:
    Q(std::string);
    int getId();
    std::string getName();
    int putMsg(Msg msg);
    Msg popMsg();
};


#endif //DISTRIBUTEDMQ_Q_HPP
