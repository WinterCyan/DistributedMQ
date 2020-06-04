//
// Created by Winter Cyan on 2020/5/26.
//

#include <iostream>
#include "QM.hpp"
#include "RT.hpp"

using namespace std;

int QM::handleMsg(Msg msg) {
    Q* nextQ = lookUpRT(msg.destQMName);
    cout<<"msg: ["<<msg.content<<"], handled."<<endl;
    cout<<"Next Q: "<<nextQ->getName()<<endl;
    routeMsg(msg, nextQ);
    return 0;
}

// put msg to next q
int QM::routeMsg(Msg msg, Q *q) {
    q->putMsg(msg);
    return 0;
}

// get next q
Q *QM::lookUpRT(std::string destQMName) {
    if (destQMName == this->name) {
        return (Q*)localQ;
    }
    if (rt->entriesMap.count(destQMName)>0) { // search in RT
        auto nextQName = rt->entriesMap[destQMName];
        return (Q*)remoteQs[nextQName];
    } else{
        // TODO: change qName
        return openQ(destQMName, "newRemoteQ");
    }
}

// open new Q
Q* QM::openQ(std::string destQMName, std::string qName) {
    RemoteQ* pRemoteQ;
    remoteQs.insert(std::make_pair(destQMName, pRemoteQ = new RemoteQ(qName))); // constructor returns pointer?
    rt->entriesMap.insert({destQMName, qName});
    return (Q*)pRemoteQ;
}

// explicitly init "localQ" which has no default constructor, and "rt" that contains a map
QM::QM(std::string qmName):localQ(new LocalQ(LOCAL_Q_NAME)),rt(new RT()) {
    name = qmName;
    rt->entriesMap.insert({{"QM1",LOCAL_Q_NAME},{"QM2","Q2"}});
    remoteQs.insert(std::make_pair("Q2", new RemoteQ("Q2")));
}

