//
// Created by Winter Cyan on 2020/6/3.
//

#include "Demo.hpp"
#include <iostream>
#include <unistd.h>

[[noreturn]] void Demo::run() {
    auto count = 0;
    while (true) {
        std::cout<<name<<" running,,,"<<std::endl;
        count ++;
        sleep(4);
    }
}

Demo::Demo(std::string demoName) {
    name = demoName;
}
