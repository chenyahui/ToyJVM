add_subdirectory(common)
add_subdirectory(classpath)
add_subdirectory(classfile)
add_subdirectory(runtime)
add_subdirectory(instruction)

file(GLOB_RECURSE HEADERS "./" "*.h")

set(SOURCE_FILES
        ${HEADERS}
        main.cpp)

add_executable(toyjvm ${SOURCE_FILES})
target_link_libraries(toyjvm
        toyjvm_common
        toyjvm_classpath
        toyjvm_classfile
        glog
        )