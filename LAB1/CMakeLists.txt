cmake_minimum_required(VERSION 2.8)
project(PB1)

set(APP_NAME "app")
file(GLOB_RECURSE SOURCE source/*.c)
message(STATUS "files : " ${SOURCE})
#DEV
#set(FLAGS "-Wall -ansi -g")
#RELEASE
set(FLAGS "-Wall -ansi -O3")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAGS}")
add_executable(${APP_NAME} ${SOURCE})
