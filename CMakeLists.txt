cmake_minimum_required(VERSION 3.24)
project(dining_philosophers)

set(CMAKE_CXX_STANDARD 17)

add_executable(dining_philosophers main.cpp philosopher.cpp chopstick.cpp)
