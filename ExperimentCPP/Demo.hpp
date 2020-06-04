//
// Created by Winter Cyan on 2020/6/3.
//

#ifndef DISTRIBUTEDMQ_DEMO_HPP
#define DISTRIBUTEDMQ_DEMO_HPP


#include <string>
#include <map>
#include "DemoMAP.hpp"

struct DemoMAP;

class Demo {
private:
    std::string name;
    DemoMAP* demoMap;
public:
    void printName();
    Demo(std::string name);
};


#endif //DISTRIBUTEDMQ_DEMO_HPP
