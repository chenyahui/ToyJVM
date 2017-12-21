cmake_minimum_required(VERSION 3.6)
project(tinyjvm)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/bin)
#set(CMAKE_CXX_FLAGS "-O1")

file(GLOB_RECURSE SOURCE_LIST "src/*.cpp")

include_directories("${CMAKE_CURRENT_LIST_DIR}/include")
include_directories("/usr/include/c++/6.4.0")
include_directories("/usr/include/x86_64-linux-gnu/c++/6")

set(LIBRARIES "/usr/local/lib")
link_directories(${LIBRARIES})

add_executable(tinyjvm ${SOURCE_LIST})
