macro(addTester test_name)
    add_executable(${test_name}
            ${test_name}.cpp)

    target_link_libraries(${test_name}
            toyjvm_inst
            pthread
            gtest
            gtest_main)
endmacro()

addTester(test_const_inst)
addTester(test_compare_inst)
addTester(test_control_inst)
addTester(test_convert_inst)