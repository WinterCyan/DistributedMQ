//
// Created by Winter Cyan on 2020/5/26.
//

#include <iostream>
#include <string>
#include "QM.hpp"
#include "RT.hpp"

using namespace std;

// data flow of Messages?: produce()->handleMsg()->putMsg(), pass with pointer, and when msg is destroyed?
int QM::handleMsg(Msg *msg) {
    char destQM[QM_NAME_SZ];
    memcpy(destQM, msg->msgText, QM_NAME_SZ);
    Q* nextQ = lookUpRT(destQM);
    nextQ->putMsg(msg);
//    routeMsg(msg, nextQ);
    return 0;
}

// put msg to next q
//int QM::routeMsg(Msg msg, Q *q) {
//    q->putMsg(msg);
//    return 0;
//}

// get next q
Q *QM::lookUpRT(std::string destQMName) {
    if (destQMName == this->name) { // local deliver
        return (Q*)localQ;
    }
    if (rt->entriesMap.count(destQMName)>0) { // search in RT
        auto nextQName = rt->entriesMap[destQMName];
        return (Q*)remoteQs[nextQName];
    } else{
        auto qCount = remoteQs.size();
        return openQ(destQMName, "Q"+to_string(qCount+1));
    }
}

// open new Q
Q* QM::openQ(std::string destQMName, std::string qName) {
    RemoteQ* pRemoteQ;
    remoteQs.insert(std::make_pair(qName, pRemoteQ = new RemoteQ(qName))); // constructor returns pointer?
    rt->entriesMap.insert({destQMName, qName});
    return (Q*)pRemoteQ;
}

// explicitly init "localQ" which has no default constructor, and "rt" that contains a map
QM::QM(std::string qmName):localQ(new LocalQ(LOCAL_Q_NAME)),rt(new RT()) {
    name = qmName;
    rt->entriesMap.insert({"LocalQM",LOCAL_Q_NAME});
}

