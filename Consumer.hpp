//
// Created by Winter Cyan on 2020/5/26.
//

#ifndef DISTRIBUTEDMQ_CONSUMER_HPP
#define DISTRIBUTEDMQ_CONSUMER_HPP


#include "Msg.hpp"
#include "LocalQ.hpp"

class Consumer {
private:
    LocalQ* ownerLocalQ;
    Msg consume();
public:
    void run();

};


#endif //DISTRIBUTEDMQ_CONSUMER_HPP
