cmake_minimum_required(VERSION 3.9)
project(toyjvm)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 11)

set(CXX_FLAGS
        -g
        -Wall
        -Werror
        -Woverloaded-virtual
        )

if (MSVC)
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
endif (MSVC)


#setup boost
find_package(Boost REQUIRED COMPONENTS
        program_options
        filesystem
        )
message(STATUS "test" ${Boost_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
#setup gtest
find_package(GTest REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/third_party)

add_subdirectory(toyjvm/common)
add_subdirectory(toyjvm/classpath)
add_subdirectory(toyjvm/classfile)
add_subdirectory(toyjvm/runtime)

file(GLOB_RECURSE HEADERS "toyjvm/*.h")

set(SOURCE_FILES
        ${HEADERS}
        toyjvm/main.cpp)

add_executable(toyjvm ${SOURCE_FILES})
target_link_libraries(toyjvm
        toyjvm_common
        toyjvm_classpath
        toyjvm_classfile
        glog
        )