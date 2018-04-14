set(classfile_SRCS
        classfile.cpp
        const_pool.cpp
        attribute_table.cpp
        attribute_infos.cpp const_infos.cpp)

add_library(toyjvm_classfile ${classfile_SRCS})