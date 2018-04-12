set(common_SRCS
        cmdline.cpp
        ioutils.cpp)

add_library(toyjvm_common ${common_SRCS})
target_link_libraries(toyjvm_common
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        )