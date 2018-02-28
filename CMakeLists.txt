cmake_minimum_required(VERSION 3.7)
project(toyjvm)

set(CMAKE_CXX_STANDARD 11)

#setup boost
find_package(Boost REQUIRED)
#message(STATUS ${Boost_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})

#setup gtest
find_package(GTest REQUIRED)

#setup gflags
find_package(GFlags REQUIRED)
#message(STATUS ${gflags_INCLUDE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/third_party)

add_subdirectory(third_party)
add_subdirectory(src/common)
add_subdirectory(src/classpath)

file(GLOB_RECURSE HEADERS "include/toyjvm/*.h")

set(SOURCE_FILES
        ${HEADERS}
        src/main.cpp)

add_executable(toyjvm ${SOURCE_FILES})
target_link_libraries(toyjvm toyjvm_common)