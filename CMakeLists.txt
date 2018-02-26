cmake_minimum_required(VERSION 3.7)
project(toyjvm)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/third_party)

add_subdirectory(third_party)
add_subdirectory(src/common)
add_subdirectory(src/classpath)

set(SOURCE_FILES
        src/main.cpp)

add_executable(toyjvm ${SOURCE_FILES})
target_link_libraries(toyjvm toyjvm_common)