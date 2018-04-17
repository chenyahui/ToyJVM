set(runtime_SRCS
        jvm_class.cpp)

add_subdirectory(tests)
add_library(toyjvm_runtime ${runtime_SRCS})
target_link_libraries(toyjvm_runtime
        toyjvm_common
        )