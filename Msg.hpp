//
// Created by Winter Cyan on 2020/5/26.
//

#ifndef DISTRIBUTEDMQ_MSG_HPP
#define DISTRIBUTEDMQ_MSG_HPP

#include <string>

enum MsgType {T1, T2, T3};
struct Msg {
    std::string destQMName;
    const MsgType msgType;
    const char* content;
    Msg(std::string name, const MsgType type = T1, const char *cont = "")
        :destQMName(name),msgType(type),content(cont){};
};


#endif //DISTRIBUTEDMQ_MSG_HPP
