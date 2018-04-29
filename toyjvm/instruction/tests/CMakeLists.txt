macro(Tester test_name)
    add_executable(${test_name}
            ${test_name}.cpp)

    target_link_libraries(${test_name}
            toyjvm_inst
            pthread
            gtest
            gtest_main)
endmacro()

Tester(test_const_inst)
Tester(test_compare_inst)
