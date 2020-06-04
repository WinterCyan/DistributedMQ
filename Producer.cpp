//
// Created by Winter Cyan on 2020/5/26.
//

#include "Producer.hpp"
#include <unistd.h>
#include <iostream>

#define DEFAULT_DEST_QM "QM2"

using namespace std;

[[noreturn]] void Producer::run() {
    while (true) {
        sleep(1);
        auto msg = produce();
        cout<<"message \""<<msg.content<<"\" sent..."<<endl;
        this->ownerQM.handleMsg(msg);
    }
}

// produce messages
Msg Producer::produce() {
    string msgCont = "Message content: ";
    auto i = random();
    msgCont.append(to_string(i));
    auto msg = Msg(DEFAULT_DEST_QM, T1, msgCont.c_str());
    return msg;
}

Producer::Producer(std::string name, QM ownerQM) : ownerQM(ownerQM){}
