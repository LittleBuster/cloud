cmake_minimum_required(VERSION 2.8)
project(cloud)

include_directories(".")
include_directories("..")

set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -march=native -Wall -O2")
set(SRC_LIST ../session.cpp ../filetransfer.cpp ../watcher.cpp ../mastertimer.cpp ../slavetimer.cpp ../configs.cpp ../log.cpp ../tcpclient.cpp ../filehash.cpp ../cloud.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST})

target_link_libraries(cloud -lpthread -lcrypto -lboost_system -lboost_filesystem)

if(WIN32)
	target_link_libraries(${PROJECT_NAME} -lws2_32)
endif(WIN32)