//
// Created by Winter Cyan on 2020/5/27.
//

#include "RemoteQ.hpp"
#include <future>
#include <unistd.h>
#include <iostream>

using namespace std;

// create remoteQ and meanwhile, create a sendMCA
RemoteQ::RemoteQ(std::string qName):Q(qName) {
    sendMCA = new SendMCA(this);
    static auto futureRun = std::async(&SendMCA::run, sendMCA); // run once initialized
}

void RemoteQ::putMsg(Msg *msg) {
    Q::putMsg(msg);
    if (sendMCA->status == STOPPED) {
        static auto futureRun = std::async(&SendMCA::run, sendMCA);
    }
}
