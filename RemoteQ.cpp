//
// Created by Winter Cyan on 2020/5/27.
//

#include "RemoteQ.hpp"

// create remoteQ and meanwhile, create a sendMCA
RemoteQ::RemoteQ(std::string qName):Q(qName) {
    sendMCA = new SendMCA(this);
}

int RemoteQ::putMsg(Msg *msg) {
    Q::putMsg(msg);
    // empty and stopped
    if (getMsgNum() == 0 && sendMCA->status == STOPPED) sendMCA->run();
}
