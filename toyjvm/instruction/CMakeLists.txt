add_subdirectory(tests)

set(INST_SRC
        stack_instructions.cpp
        math_instructions.cpp
        convert_instructions.h
        compare_instructions.h
        bytecode_reader.cpp
        control_instructions.h
        control_instructions.cpp
        extend_instructions.h
        extend_instructions.cpp
        ref_instructions.h
        ref_instructions.cpp
        instruction_factory.h instruction_factory.cpp array_instructions.h array_instructions.cpp)

add_library(toyjvm_inst
        ${INST_SRC}
        )

target_link_libraries(toyjvm_inst toyjvm_runtime)