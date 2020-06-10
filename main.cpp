#include <iostream>
#include "Producer.hpp"

using namespace std;

int main() {
//    auto p = new Producer("producer1", QM("LocalQM"));
//    p->run();
    struct Msg msg;
    char s[MSG_SZ-1] = {};
    auto *q = new RemoteQ("Q1");
    cout<<"producing..."<<endl;
    for (int i = 0; i<3; i++) {
        for (int i = 0; i < 10; ++i)
            s[i] = CHAR_SET[rand() % (sizeof(CHAR_SET) - 1)];
        cout<<s<<endl;
        msg.msgType = 0;
        memcpy(msg.msgText, DEFAULT_DEST_QM, sizeof(DEFAULT_DEST_QM));
        memcpy(msg.msgText+QM_NAME_SZ, s, MSG_SZ-QM_NAME_SZ);
        q->putMsg(&msg);
    }

    cout<<"consuming..."<<endl;
    for (;;) {
        cout<<"pop ..."<<endl;
        q->popMsg();
    }
}
