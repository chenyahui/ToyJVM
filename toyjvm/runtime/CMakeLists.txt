set(runtime_SRCS
        jvm_class.cpp
        runtime_const_pool.h
        jvm_member.h
        class_loader.h
        jvm_member.cpp
        runtime_const_pool.cpp
        symbol_ref.h
        class_loader.cpp
        jvm_reference.h
        symbol_ref.cpp
        jvm_frame.cpp
        jvm_thread.cpp)

add_subdirectory(tests)
add_library(toyjvm_runtime ${runtime_SRCS})
target_link_libraries(toyjvm_runtime
        toyjvm_utilities
        )