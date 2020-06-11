//
// Created by Winter Cyan on 2020/5/26.
//

#include <iostream>
#include <unistd.h>
#include <thread>
#include "SendMCA.hpp"
#include "RemoteQ.hpp"

using namespace std;

// should MCA run as a new thread?
void SendMCA::run(void) {
    cout<<"run invoked."<<endl;
    status = RUNNING;
    for (;;) {
        owner->popMsg(); // get msg from queue
        deliverMsg(owner->msg); // deliver queue
    }
}

int SendMCA::deliverMsg(Msg *msg) {
}

SendMCA::SendMCA(RemoteQ* remoteQ) {
    owner = remoteQ;
}
