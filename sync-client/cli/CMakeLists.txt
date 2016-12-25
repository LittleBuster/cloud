cmake_minimum_required(VERSION 2.8)
project(client-cli)

include_directories(".")
include_directories("../")
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -march=native -Wall -O2")
set(SRC_LIST main.cpp app.cpp ../session.cpp ../filetransfer.cpp ../filewatch.cpp ../configs.cpp ../ext.cpp ../log.cpp ../tcpclient.cpp ../timer.cpp ../filehash.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} -lpthread -lcrypto)