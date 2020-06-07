#include <iostream>
#include "Producer.hpp"

int main() {
    auto p = new Producer("producer1", QM("LocalQM"));
    p->run();
}
