//
// Created by Winter Cyan on 2020/6/3.
//

#include "Demo.hpp"
#include <iostream>
#include <unistd.h>

[[noreturn]] void Demo::run() {
    auto count = 0;
    while (true) {
        sleep(d);
        std::cout<<name<<" running,,,"<<std::endl;
        count ++;
    }
}

Demo::Demo(std::string demoName, int delay ) {
    name = demoName;
    d = delay;
}
