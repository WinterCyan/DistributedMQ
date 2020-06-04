#include <iostream>
#include "Producer.hpp"

int main() {
    auto p = new Producer("producer1", QM("QM1"));
    p->run();
}
