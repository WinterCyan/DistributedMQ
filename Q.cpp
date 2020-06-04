//
// Created by Winter Cyan on 2020/5/26.
//

#include <iostream>
#include "Q.hpp"

using namespace std;

int Q::putMsg(Msg msg) {
    //TODO

    cout<<"put msg into q "<<this<<endl;
    cout<<"-------------------------------"<<endl;
    return 0;
}

Msg Q::popMsg() {
    //TODO

}

int Q::getId() {
    return id;
}

std::string Q::getName() {
    return name;
}

Q::Q(std::string qName) {
    name = qName;
    //TODO: init queue with "ftok" and "msgget"

}

