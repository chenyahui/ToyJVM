set(common_SRCS
        cmdline.cpp
        ioutils.cpp zip_wrapper.h tests/zip_wrapper_test.cpp)

add_library(toyjvm_common ${common_SRCS})
target_link_libraries(toyjvm_common
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        "D:\\vcpkg\\installed\\x64-windows-static\\lib\\zip.lib")