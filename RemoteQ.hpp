//
// Created by Winter Cyan on 2020/5/27.
//

#ifndef DISTRIBUTEDMQ_REMOTEQ_HPP
#define DISTRIBUTEDMQ_REMOTEQ_HPP


#include "Q.hpp"
#include "SendMCA.hpp"

class RemoteQ: public Q {
private:
    SendMCA* sendMCA;
public:
    RemoteQ(std::string);
    int putMsg(Msg *msg) override;
};


#endif //DISTRIBUTEDMQ_REMOTEQ_HPP
