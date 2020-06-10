//
// Created by Winter Cyan on 2020/6/3.
//

#include "Demo.hpp"
#include <map>
#include <thread>
#include <future>
#include <unistd.h>
#include "../Msg.hpp"

#define CHAR_SET "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

using namespace std;

int run(string name, int c) {
    for (int i = 0; i < c; ++i) {
        std::cout<<name<<" running,,,"<<i<<std::endl;
    }
    return c;
}

int main() {
    auto demo1 = new Demo("demo1", 1);
    auto demo2 = new Demo("demo2", 2);
    auto f1 = async(&Demo::run, demo1);
    auto f2 = async(&Demo::run, demo2);
    sleep(3);
    cout<<"Main thread printing..."<<endl;
    cout<<"Main thread printing..."<<endl;
    cout<<"Main thread printing..."<<endl;
    cout<<"Main thread printing..."<<endl;

    return 0;
}

//#include <iostream>
//#include <string>
//
//std::string hellofunction(const std::string& s) {
//    return "hello c++11 from " + s + ".";
//}
//
//class hellofunctionobject {
//public:
//    std::string operator()(const std::string& s) const {
//        return "hello c++11 from " + s + ".";
//    }
//};
//
//int main() {
//
//    std::cout << std::endl;
//
//    // 带函数的future
//    auto futurefunction = std::async(hellofunction, "function");
//
//    // 带函数对象的future
//    hellofunctionobject hellofunctionobject;
//    auto futurefunctionobject = std::async(hellofunctionobject, "function object");
//
//    // 带匿名函数的future
//    auto futurelambda = std::async([](const std::string& s) {return "hello c++11 from " + s + "."; }, "lambda function");
//
//    std::cout << futurefunction.get() << "\n"
//              << futurefunctionobject.get() << "\n"
//              << futurelambda.get() << std::endl;
//
//    std::cout << std::endl;
//
//}

//#include <vector>
//#include <thread>
//#include <future>
//#include <numeric>
//#include <iostream>
//#include <chrono>
//
//void accumulate(std::vector<int>::iterator first,
//                std::vector<int>::iterator last,
//                std::promise<int> accumulate_promise)
//{
//    int sum = std::accumulate(first, last, 0);
//    accumulate_promise.set_value(sum);  // notify future
//}
//
//void do_work(std::promise<void> barrier)
//{
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    barrier.set_value();
//}
//
//int main()
//{
//    // demonstrate using promise<int> to transmit a result between threads.
//    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
//    std::promise<int> accumulate_promise;
//    std::future<int> accumulate_future = accumulate_promise.get_future();
//    std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
//                            std::move(accumulate_promise));
//
//    // future::get() will wait until the future has a valid result and retrieves it.
//    // calling wait() before get() is not needed
//    //accumulate_future.wait();  // wait for result
//    std::cout << "result=" << accumulate_future.get() << '\n';
//    work_thread.join();  // wait for thread completion
//
//    // demonstrate using promise<void> to signal state between threads.
//    std::promise<void> barrier;
//    std::future<void> barrier_future = barrier.get_future();
//    std::thread new_work_thread(do_work, std::move(barrier));
//    barrier_future.wait();
//    new_work_thread.join();
//}