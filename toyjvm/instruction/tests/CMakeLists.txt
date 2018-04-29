add_executable(test_const_inst
        test_const_inst.cpp)

target_link_libraries(test_const_inst
        toyjvm_inst
        pthread
        gtest
        gtest_main)


add_executable(test_compare_inst
        test_compare_inst.cpp)

target_link_libraries(test_compare_inst
        toyjvm_inst
        pthread
        gtest
        gtest_main)