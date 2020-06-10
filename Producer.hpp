//
// Created by Winter Cyan on 2020/5/26.
//

#ifndef DISTRIBUTEDMQ_PRODUCER_HPP
#define DISTRIBUTEDMQ_PRODUCER_HPP


#include "Msg.hpp"
#include "QM.hpp"

class Producer {
private:
    std::string name;
    Msg *produce();
public:
    QM ownerQM;
    Producer(std::string name, QM ownerQm);
    [[noreturn]] void run();

};


#endif //DISTRIBUTEDMQ_PRODUCER_HPP
