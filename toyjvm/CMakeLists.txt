add_subdirectory(utilities)
add_subdirectory(classpath)
add_subdirectory(classfile)
add_subdirectory(runtime)
add_subdirectory(instruction)

file(GLOB_RECURSE HEADERS "./" "*.h")

set(SOURCE_FILES
        ${HEADERS}
        main.cpp interpreter/interpret.h interpreter/interpret.cpp native/native_methods.h native/native_methods.cpp native/java/lang/System.h native/java/lang/Class.h)

add_executable(toyjvm ${SOURCE_FILES})
target_link_libraries(toyjvm
        toyjvm_utilities
        toyjvm_classpath
        toyjvm_classfile
        glog
        )