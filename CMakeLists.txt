cmake_minimum_required(VERSION 3.16)
project(sensehat_datacentre)

set(CMAKE_CXX_STANDARD 17)

add_executable(sensehat_datacentre main.cpp include/senseHat.h src/HTS221Driver.cpp include/HTS221Driver.h include/registers.h)
target_link_libraries(${PROJECT_NAME} wiringPi)