cmake_minimum_required(VERSION 2.8)
project(PB1)

set(APP_NAME "app")
file(GLOB_RECURSE SOURCE source/*.c)
#DEV
#set(FLAGS "-Wall -ansi -g -o")
#RELEASE
#set(FLAGS "-Wall -ansi -O3 -o")

set(FLAGS "")


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAGS}")
add_executable(${APP_NAME} ${SOURCE})