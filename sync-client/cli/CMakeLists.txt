cmake_minimum_required(VERSION 2.8)
project(client-cli)

include_directories(".")
include_directories("../")
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -march=native -Wall -O2")
set(SRC_LIST main.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} -lpthread -L. -lcloudclient)

set(SRC_LIST2 ../configs.cpp ../ext.cpp ../log.cpp ../tcpclient.cpp)
add_library(cloudclient SHARED ${SRC_LIST2})
