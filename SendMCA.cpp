//
// Created by Winter Cyan on 2020/5/26.
//

#include <iostream>
#include "SendMCA.hpp"
#include "RemoteQ.hpp"

using namespace std;

void SendMCA::run() {
    cout<<"sendMCA::run() invoked."<<endl;
    // TODO: create new async thread
    for(;;) {
        Msg msg = owner->popMsg();
        deliverMsg(msg);
        if (owner->getMsgNum() == 0) break;
    }
}

int SendMCA::deliverMsg(Msg msg) {
    cout<<msg.content<<" delivered by SendMCA..."<<endl;
}

SendMCA::SendMCA(RemoteQ* remoteQ) {
    owner = remoteQ;
}
