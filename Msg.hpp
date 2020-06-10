//
// Created by Winter Cyan on 2020/5/26.
//

#ifndef DISTRIBUTEDMQ_MSG_HPP
#define DISTRIBUTEDMQ_MSG_HPP

#include <string>
#include <iostream>
#include "param.hpp"

struct Msg {
    long msgType;
    char msgText[MSG_SZ] = {};
};

//Msg::Msg(long type, std::string destQM, char *text) {
//    msgType= type;
//    destQMName = destQM;
//    strcpy(msgText, text);
//}

//Msg::Msg(long type, std::string destQM) {
//    msgType= type;
//    destQMName = destQM;
//}

//enum MsgType {T1, T2, T3};
//struct Msg {
//    std::string destQMName;
//    const MsgType msgType;
//    char content[20];
//
//    Msg(std::string name, const MsgType type = T1)
//        :destQMName(name),
//        msgType(type) { };
//
//    Msg(Msg *tempMsg):
//        destQMName(tempMsg->destQMName),
//        msgType(tempMsg->msgType) {} // copy control?
//
//    ~Msg(){
//        std::cout<<"Msg destroyed"<<std::endl;
//    }
//};


#endif //DISTRIBUTEDMQ_MSG_HPP
