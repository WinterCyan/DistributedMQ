//
// Created by Winter Cyan on 2020/6/3.
//

#ifndef DISTRIBUTEDMQ_DEMO_HPP
#define DISTRIBUTEDMQ_DEMO_HPP


#include <string>
#include <map>

class Demo {
private:
    std::string name;
    int d;
public:
    [[noreturn]] void run();
    Demo(std::string, int);
};


#endif //DISTRIBUTEDMQ_DEMO_HPP
