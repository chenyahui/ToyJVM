add_subdirectory(tests)

set(INST_SRC
        stack_instructions.cpp
        math_instructions.cpp)

add_library(toyjvm_inst ${INST_SRC})