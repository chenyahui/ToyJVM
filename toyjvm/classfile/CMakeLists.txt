set(classfile_SRCS
        classfile.cpp
        const_pool.cpp
        attribute_table.cpp
        attribute_infos.cpp
        const_infos.cpp
        member_info.cpp)

add_library(toyjvm_classfile
        ${classfile_SRCS}
        )
target_link_libraries(toyjvm_classfile
        glog
        toyjvm_utilities)