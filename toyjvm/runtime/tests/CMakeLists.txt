add_executable(test_local_vars test_local_slots.cpp)

target_link_libraries(test_local_vars
        toyjvm_runtime
        pthread
        gtest
        gtest_main)