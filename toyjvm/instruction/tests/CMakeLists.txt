add_executable(test_const_inst
        test_const_inst.cpp)

target_link_libraries(test_const_inst
        toyjvm_inst
        pthread
        gtest
        gtest_main)