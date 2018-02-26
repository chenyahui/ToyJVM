set(common_SRCS
        cmdline.cpp
        ioutils.cpp system.cpp)

add_library(toyjvm_common ${common_SRCS})
target_link_libraries(toyjvm_common gflags_nothreads)