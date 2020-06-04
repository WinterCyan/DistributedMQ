//
// Created by Winter Cyan on 2020/5/26.
//

#ifndef DISTRIBUTEDMQ_QM_HPP
#define DISTRIBUTEDMQ_QM_HPP


#include <map>
#include "Msg.hpp"
#include "LocalQ.hpp"
#include "RemoteQ.hpp"

#define LOCAL_Q_NAME "local queue"

struct RT; // prevent ref-cycle

class QM {
private:
    std::string name;
    LocalQ* localQ; // single local Q
    // map: Q's name -> Q*
    std::map<std::string, RemoteQ*> remoteQs = {};
    RT* rt;

    Q* openQ(std::string, std::string); // create new (remote)queue, destQName, qName
    Q* lookUpRT(std::string destName); // return Q's id, or 0
    int routeMsg(Msg msg, Q*);

public:
    QM(std::string);
    int handleMsg(Msg msg);
    void run();

};


#endif //DISTRIBUTEDMQ_QM_HPP
