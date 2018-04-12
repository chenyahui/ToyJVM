set(classpath_SRCS
        class_path.cpp
        path_entry.cpp
        )

add_library(toyjvm_classpath ${classpath_SRCS})
target_link_libraries(toyjvm_classpath
        toyjvm_common
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        zip
        )