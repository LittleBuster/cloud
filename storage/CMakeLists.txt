cmake_minimum_required(VERSION 2.8)
project(storage)

include_directories(".")
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -march=native -Wall -O2")
set(SRC_LIST main.cpp app.cpp session.cpp base.cpp filetransfer.cpp configs.cpp ext.cpp log.cpp tcpclient.cpp tcpserver.cpp cloudstorage.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} -lpthread -lsqlite3)
