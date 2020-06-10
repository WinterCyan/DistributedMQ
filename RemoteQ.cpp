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
    // empty and stopped
//    if (sendMCA->status == STOPPED or sendMCA->status == SUSPENDED) {
//    if (sendMCA->status == STOPPED) {
//        cout<<"status when async call: "<<sendMCA->status<<endl;
//        auto futureRun = std::async(&SendMCA::run, sendMCA);
//    }
}
