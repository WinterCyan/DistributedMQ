#include <iostream>
#include <future>
#include "Producer.hpp"
#include <unistd.h>

using namespace std;

int main() {
//    auto p = new Producer("Producer1", new QM("LocalQM"));
//    p->run();
    struct Msg msg;
    char s[MSG_SZ-1] = {};
    auto *q = new RemoteQ("Q1");
    cout<<"consuming..."<<endl;
    auto f = async(&SendMCA::run, q->sendMCA);
    sleep(1);
    cout<<"producing..."<<endl;
    for (int i = 0; i<10; i++) {
        for (int i = 0; i < 10; ++i)
            s[i] = CHAR_SET[rand() % (sizeof(CHAR_SET) - 1)];
        msg.msgType = 0;
        memcpy(msg.msgText, DEFAULT_DEST_QM, sizeof(DEFAULT_DEST_QM));
        memcpy(msg.msgText+QM_NAME_SZ, s, MSG_SZ-QM_NAME_SZ);
        q->putMsg(&msg);
    }

//    cout<<"consuming..."<<endl;
//    for (;;) {
//        cout<<"pop ..."<<endl;
//        q->popmsg();
//    }
}
