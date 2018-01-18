find_package (Threads)
add_executable(descriptor_test descriptor_test.cpp)
target_link_libraries(descriptor_test
        gtest
        gtest_main
        ${CMAKE_THREAD_LIBS_INIT}
        )
