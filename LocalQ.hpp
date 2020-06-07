//
// Created by Winter Cyan on 2020/5/27.
//

#ifndef DISTRIBUTEDMQ_LOCALQ_HPP
#define DISTRIBUTEDMQ_LOCALQ_HPP


#include "Q.hpp"

class LocalQ: public Q {
private:
//    Consumer* consumer;
public:
    LocalQ(std::string);

};


#endif //DISTRIBUTEDMQ_LOCALQ_HPP
