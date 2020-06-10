//
// Created by Winter Cyan on 2020/5/26.
//

#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "Q.hpp"
#include "param.hpp"

using namespace std;

int Q::putMsg(Msg *msg) {
    struct Msg buf;
    buf.msgType = 1;
    memset(buf.msgText, 0, MSG_SZ);
    memcpy(buf.msgText, msg->msgText, MSG_SZ);
    cout<<"put msg: "<<buf.msgText+20<<endl;
    if(msgsnd(id, (void*)&buf, MSG_SZ, 0) == -1) {
        perror("msgsnd");
        return -1;
    }
    msgNum++;
    return 0;
}

// every invoke, retrieve a msg and return; kinda slow
void Q::popMsg() { // return a char* ?
    struct Msg buf;
    if (msgrcv(id, &buf, MSG_SZ, 0, 0) == -1) {
        perror("msgrcv");
        return ;
    }
    msgNum--;
    inMsg->msgType = buf.msgType;
    memcpy(inMsg->msgText, buf.msgText, MSG_SZ);
    cout << "pop msg: " << inMsg->msgText + 20 << endl;
}

int Q::getId() {
    return id;
}

int Q::getMsgNum() {
    return msgNum;
}

std::string Q::getName() {
    return name;
}

Q::Q(std::string qName): name(qName), inMsg(new Msg()) {
    key = ftok((name+".txt").c_str(),'B');
    if (key == -1) {
        perror("ftok err");
        exit(1);
    }
    id = msgget(key, PERMS|IPC_CREAT);
    if (id == -1) {
        perror("msgget err");
        exit(1);
    }
    cout<<"queue name, key, id: "<<qName<<" "<<key<<" "<<id<<";"<<endl;
}
