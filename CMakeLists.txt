cmake_minimum_required(VERSION 3.9)
project(toyjvm)

set(CMAKE_CXX_STANDARD 11)

if (MSVC)
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
endif (MSVC)

#setup boost
find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
message(STATUS ${Boost_INCLUDE_DIRS})
#setup gtest
find_package(GTest REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/third_party)

#add_subdirectory(third_party)
add_subdirectory(src/common)
#add_subdirectory(src/classpath)

file(GLOB_RECURSE HEADERS "include/toyjvm/*.h")

set(SOURCE_FILES
        ${HEADERS}
        src/main.cpp)

add_executable(toyjvm ${SOURCE_FILES})
target_link_libraries(toyjvm toyjvm_common)