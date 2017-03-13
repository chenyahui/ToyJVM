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

add_executable(tinyjvm ${SOURCE_LIST} src/classfile/classreader.cpp src/util/byteutils.cpp src/classfile/classfile.cpp src/classfile/memberinfo.cpp include/classfile/constantinfo.h src/classfile/constantinfo.cpp include/classfile/cp_numeric.h include/classfile/cp_utf8.h include/classfile/cp_string.h src/classfile/cp_numeric.cpp src/classfile/cp_utf8.cpp src/classfile/constantPool.cpp src/classfile/cp_string.cpp include/classfile/cp_class.h src/classfile/cp_class.cpp include/classfile/cp_member_ref.h src/classfile/cp_member_ref.cpp include/classfile/cp_name_type.h include/classfile/cp_invoke_dynamic.h)

target_link_libraries(tinyjvm
        boost_system
        boost_filesystem
        zip)