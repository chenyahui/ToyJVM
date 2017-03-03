cmake_minimum_required(VERSION 3.6)
project(tinyjvm)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/bin)

# boost
set(Boost_INCLUDE_DIRS "/usr/local/include/boost")
set(Boost_LIBRARIES "/usr/local/lib")

file(GLOB_RECURSE SOURCE_LIST "src/*.cpp")

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)
link_directories(${Boost_LIBRARIES})

add_executable(tinyjvm ${SOURCE_LIST} src/classfile/classreader.cpp src/util/byteutils.cpp src/classfile/classfile.cpp src/classfile/memberinfo.cpp include/classfile/constantinfo.h)

target_link_libraries(tinyjvm
        boost_system
        boost_filesystem
        zip)