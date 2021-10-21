cmake_minimum_required(VERSION 3.16)
project(sensehat_datacentre)

set(CMAKE_CXX_STANDARD 17)

add_executable(sensehat_datacentre main.cpp src/I2CClient.cpp include/I2CClient.h src/I2CClient.cpp include/I2CClient.h)
