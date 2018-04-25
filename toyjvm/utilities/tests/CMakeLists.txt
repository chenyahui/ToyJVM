add_executable(test_type_cast test_type_cast.cpp)

target_link_libraries(test_type_cast
        toyjvm_utilities
        pthread
        gtest
        gtest_main)