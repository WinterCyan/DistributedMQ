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
public:
    [[noreturn]] void run();
    Demo(std::string demoName);
};


#endif //DISTRIBUTEDMQ_DEMO_HPP
