macro(addTester test_name)
    add_executable(${test_name}
            ${test_name}.cpp)

    target_link_libraries(${test_name}
            toyjvm_runtime
            pthread
            gtest
            gtest_main)
endmacro()

addTester(test_local_slots)
addTester(test_operand_stack)
addTester(test_class_loader)