//
// Created by Winter Cyan on 2020/5/26.
//

#ifndef DISTRIBUTEDMQ_MSG_HPP
#define DISTRIBUTEDMQ_MSG_HPP

#include <string>
#include <iostream>

enum MsgType {T1, T2, T3};
struct Msg {
    std::string destQMName;
    const MsgType msgType;
    const size_t contLength;
    const char* content;

    Msg(std::string name, const MsgType type = T1, size_t length = 0, const char *cont = "")
        :destQMName(name),msgType(type),contLength(length),content(cont){};

    Msg(Msg *tempMsg):
        destQMName(tempMsg->destQMName),
        msgType(tempMsg->msgType),
        contLength(tempMsg->contLength),
        content(tempMsg->content) {} // copy control?

    ~Msg(){
        std::cout<<"Msg destroyed"<<std::endl;
    }
};


#endif //DISTRIBUTEDMQ_MSG_HPP
