//
// Created by cyhone on 18-4-16.
//

#include <gtest/gtest.h>
#include <toyjvm/runtime/local_slots.h>

using namespace jvm;

TEST(test_local_slots, normal)
{
    LocalSlots vars(10);

    std::cout << std::hex << 2997924580 << std::endl;

    vars.set<int>(0, 100);
    vars.set<int>(1, -100);
    vars.set<long>(2, 2997924580);
    vars.set<long>(4, -2997924580);
    vars.set<float>(6, 3.1415926f);
    vars.set<double>(7, 2.1234567898713);
    vars.set<int *>(9, nullptr);

    ASSERT_EQ(vars.at<int>(0), 100);
    ASSERT_EQ(vars.at<int>(1), -100);
    ASSERT_EQ(vars.at<long>(2), 2997924580);
    ASSERT_EQ(vars.at<long>(4), -2997924580);
    ASSERT_EQ(vars.at<float>(6), 3.1415926f);
    ASSERT_EQ(vars.at<double>(7), 2.1234567898713);
    ASSERT_EQ(vars.at<int *>(9), nullptr);
}