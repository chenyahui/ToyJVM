set(classpath_SRCS
        class_path.cpp
        path_entry.cpp
        )

add_library(toyjvm_classpath ${classpath_SRCS})
target_link_libraries(toyjvm_classpath boost_filesystem)