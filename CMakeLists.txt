cmake_minimum_required(VERSION 3.6)
project(tinyjvm)

if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "DEBUG")
endif()

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/bin)
#set(CMAKE_CXX_FLAGS "-O1")

set(CXX_FLAGS
        -g
        -Wall
        -Werror
        -Woverloaded-virtual
        )


set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
file(GLOB_RECURSE SOURCE_LIST "src/*.cpp")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")


include_directories("${CMAKE_CURRENT_LIST_DIR}/include")
include_directories("/usr/include/c++/6.4.0")
include_directories("/usr/include/x86_64-linux-gnu/c++/6")

set(LIBRARIES "/usr/local/lib")
link_directories(${LIBRARIES})

add_executable(tinyjvm ${SOURCE_LIST})
target_link_libraries(tinyjvm glog)
#add_subdirectory(test)
