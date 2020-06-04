//
// Created by Winter Cyan on 2020/5/26.
//

#ifndef DISTRIBUTEDMQ_RCVMCA_HPP
#define DISTRIBUTEDMQ_RCVMCA_HPP

#include "QM.hpp"

class RcvMCA {
private:
    QM* ownerQM;
    Msg retrieveMsg();
    int handOverMsg();

public:
    RcvMCA();

};


#endif //DISTRIBUTEDMQ_RCVMCA_HPP
