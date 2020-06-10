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
//    auto sentMsgCount = 0;
    status = RUNNING;
    cout<<"sendMCA running..."<<endl;
    for (;;) {
        owner->popMsg(); // get msg from queue
        deliverMsg(owner->inMsg); // deliver queue
//        sentMsgCount++;
//        if (owner->getMsgNum() <= 0) {
//            status = SUSPENDED;
//            // TODO: set a timer, count down and shut down MCA
//            break;
//        }
    }
}

int SendMCA::deliverMsg(Msg *msg) {
    cout<<"delivering msg "<<msg->msgText+20<<endl;
}

SendMCA::SendMCA(RemoteQ* remoteQ) {
    owner = remoteQ;
}
