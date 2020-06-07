cmake_minimum_required(VERSION 3.16)
project(DistributedMQ)

set(CMAKE_CXX_STANDARD 14)
file(GLOB SOURCES
        *.hpp
        *.cpp
        ExperimentCPP/*.hpp
        ExperimentCPP/*.cpp)

add_executable(DistributedMQ main.cpp ${SOURCE_FILES} ${SOURCES} param.hpp)
add_executable(ExperimentCPP ExperimentCPP/ExpMain.cpp ${SOURCES})
