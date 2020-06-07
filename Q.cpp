//
// Created by Winter Cyan on 2020/5/26.
//

#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "Q.hpp"

using namespace std;

int Q::putMsg(Msg *msg) {
    cout<<"putMsg() invoked."<<endl;
    // should or not store pointers ???
    // TODO: parse msg content into chars, and store them into queue
    msgNum++;
    return msgsnd(id, msg->content, msg->contLength, 0); // put content(char[]) only
//    return msgsnd(id, msg, sizeof(Msg), 0); // put the whole Msg
}

// every invoke, retrieve a msg and return; kinda slow
Msg Q::popMsg() { // return a char* ?
    cout<<"popMsg() invoked."<<endl;
    // here, use 200 as single msg's size
    msgNum--;
    msgrcv(id, (void*)tempMsg->content, 200, 0, 0); // how can I know the size of every single msg?
    cout<<"-------------"<<endl;
    return Msg(tempMsg);
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

Q::Q(std::string qName) {
    name = qName;
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
