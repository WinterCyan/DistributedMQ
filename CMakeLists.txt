cmake_minimum_required(VERSION 3.16)
project(DistributedMQ)

set(CMAKE_CXX_STANDARD 14)
file(GLOB MQ_SOURCES
        *.hpp
        *.cpp)

file(GLOB ExperimentCPP_SOURCES
        ExperimentCPP/*.hpp
        ExperimentCPP/*.cpp)

add_executable(DistributedMQ main.cpp ${MQ_SOURCES})
add_executable(ExperimentCPP ExperimentCPP/ExpMain.cpp ${ExperimentCPP_SOURCES})
add_executable(TestLocalMQ_Rcv TestLocalMQ/mqrcv.cpp)
add_executable(TestLocalMQ_Snd TestLocalMQ/mqsend.cpp)
