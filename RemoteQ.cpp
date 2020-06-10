//
// Created by Winter Cyan on 2020/5/27.
//

#include "RemoteQ.hpp"
#include <future>
#include <iostream>

using namespace std;

// create remoteQ and meanwhile, create a sendMCA
RemoteQ::RemoteQ(std::string qName):Q(qName) {
    sendMCA = new SendMCA(this);
}

int RemoteQ::putMsg(Msg *msg) {
    Q::putMsg(msg);
    if (sendMCA->status == STOPPED) {
        auto futureRun = std::async(&SendMCA::run, sendMCA);
    }
}
