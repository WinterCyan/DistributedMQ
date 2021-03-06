cmake_minimum_required(VERSION 3.16)
project(DistributedMQ)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
file(GLOB MQ_SOURCES
        *.hpp
        *.cpp)

file(GLOB ExperimentCPP_SOURCES
        ExperimentCPP/*.hpp
        ExperimentCPP/*.cpp)

file(GLOB TestTemplate_SOURCES
        TestTemplate/*.hpp
        TestTemplate/*.cpp)

add_executable(DistributedMQ main.cpp ${MQ_SOURCES})
add_executable(ExperimentCPP ExperimentCPP/ExpMain.cpp ${ExperimentCPP_SOURCES})
add_executable(TestLocalMQ_Rcv TestLocalMQ/mqrcv.cpp)
add_executable(TestLocalMQ_Snd TestLocalMQ/mqsend.cpp)
add_executable(TestTemplate ${TestTemplate_SOURCES})
add_executable(TestSocketServer TestSocket/socketserver.cpp)
add_executable(TestSocketClient TestSocket/socketclient.cpp)
