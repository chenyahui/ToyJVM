set(classfile_SRCS
        classfile.cpp
        const_pool.cpp
        )

add_library(toyjvm_classfile ${classfile_SRCS})