cmake_minimum_required(VERSION 3.22)
project(dining_philosophers)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(dining_philosophers main.cpp philosopher.cpp chopstick.cpp visualization.cpp)

target_link_libraries(dining_philosophers ${CURSES_LIBRARIES})
