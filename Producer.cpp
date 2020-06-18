//
// Created by Winter Cyan on 2020/5/26.
//

#include "Producer.hpp"
#include <unistd.h>
#include <iostream>
#include "param.hpp"

using namespace std;

[[noreturn]] void Producer::run() {
    for (;;) {
        auto msg = produce();
        usleep(10000); // sleep for a little while
        cout<<"produce "<<msg->msgText+20<<endl;
        ownerQM->handleMsg(msg);
    }
    sleep(5);
}

// produce messages
Msg *Producer::produce() {
    char s[MSG_SZ-1] = {};
    for (int i = 0; i < 10; ++i)
        s[i] = CHAR_SET[rand() % (sizeof(CHAR_SET) - 1)];
    msg->msgType = 1;
    memcpy(msg->msgText, &DEST_QM_ARRAY[rand()%DEST_QM_SIZE], sizeof(DEFAULT_DEST_QM));
    memcpy(msg->msgText+QM_NAME_SZ, s, MSG_SZ-QM_NAME_SZ);
    return msg;
}

Producer::Producer(std::string name, QM *ownerQM) :
    ownerQM(ownerQM), msg(new Msg()) {}
