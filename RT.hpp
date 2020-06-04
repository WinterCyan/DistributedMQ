//
// Created by Winter Cyan on 2020/5/27.
//

#ifndef DISTRIBUTEDMQ_RT_HPP
#define DISTRIBUTEDMQ_RT_HPP

#include "QM.hpp"
#include <map>

struct RT {
    QM* ownerQM;
    // entry: <destQMName, QName>
    std::map<std::string, std::string> entriesMap;
};


#endif //DISTRIBUTEDMQ_RT_HPP
