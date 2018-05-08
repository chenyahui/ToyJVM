set(common_SRCS
        cmdline.cpp
        ioutils.cpp
        modified_utf8.cpp
        access_flags.h descriptor.h singleton.h javautils.h javautils.cpp method_descriptor.h method_descriptor.cpp all_static.h)

add_subdirectory(tests)

add_library(toyjvm_utilities ${common_SRCS})
target_link_libraries(toyjvm_utilities
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        )