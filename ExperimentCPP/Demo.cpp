//
// Created by Winter Cyan on 2020/6/3.
//

#include "Demo.hpp"
#include <iostream>

Demo::Demo(std::string demoName):demoMap(new DemoMAP()) {
    name = demoName;
    demoMap->localMap.insert({{"k1","v1"},{"k2","v2"}});
}

void Demo::printName() {
    std::cout<<name<<std::endl;
}
