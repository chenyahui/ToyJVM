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

add_executable(tinyjvm ${SOURCE_LIST} src/classfile/classreader.cpp src/util/byteutils.cpp src/classfile/classfile.cpp src/classfile/memberinfo.cpp include/classfile/constantinfo.h src/classfile/constantinfo.cpp include/classfile/cp_numeric.h include/classfile/cp_utf8.h include/classfile/cp_string.h src/classfile/cp_numeric.cpp src/classfile/cp_utf8.cpp src/classfile/constantPool.cpp src/classfile/cp_string.cpp include/classfile/cp_class.h src/classfile/cp_class.cpp include/classfile/cp_member_ref.h src/classfile/cp_member_ref.cpp include/classfile/cp_name_type.h include/classfile/cp_invoke_dynamic.h src/classfile/cp_name_type.cpp src/classfile/cp_invoke_dynamic.cpp src/classfile/attributeinfo.cpp include/classfile/attr_code.h src/classfile/attr_code.cpp include/classfile/attr_constant_value.h src/classfile/attr_constant_value.cpp include/classfile/attr_markers.h include/classfile/attr_exceptions.h src/classfile/attr_exceptions.cpp include/classfile/attr_line_number_table.h src/classfile/attr_line_number_table.cpp include/classfile/attr_local_variable_table.h src/classfile/attr_local_variable_table.cpp include/classfile/attr_source_file.h src/classfile/attr_source_file.cpp include/classfile/attr_unparsed.h src/classfile/attr_unparsed.cpp)

target_link_libraries(tinyjvm
        boost_system
        boost_filesystem
        zip)