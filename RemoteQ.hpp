//
// Created by Winter Cyan on 2020/5/27.
//

#ifndef DISTRIBUTEDMQ_REMOTEQ_HPP
#define DISTRIBUTEDMQ_REMOTEQ_HPP


#include "Q.hpp"
#include "SendMCA.hpp"
#include <future>

class RemoteQ: public Q {
private:
    std::future<void> futureRun;
public:
    SendMCA* sendMCA;
    RemoteQ(std::string);
    void putMsg(Msg *msg) override;
};


#endif //DISTRIBUTEDMQ_REMOTEQ_HPP
