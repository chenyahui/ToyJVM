set(link_libs toyjvm_runtime
        pthread
        gtest
        gtest_main)

add_executable(test_local_slot test_local_slots.cpp)
target_link_libraries(test_local_slot
        ${link_libs})

add_executable(test_operand_stack test_operand_stack.cpp)
target_link_libraries(test_operand_stack
        ${link_libs})