//
// Created by cyhone on 18-4-16.
//

#include <gtest/gtest.h>
#include <toyjvm/utilities/type_cast.h>

using namespace jvm;

TEST(test_type_cast, splitLongTo2Bit32)
{
    auto assert_long = [](long val, int high, int low) {
        auto two = union_cast<long, std::array<int, 2>>(val);
        EXPECT_EQ(two[1], high);
        EXPECT_EQ(two[0], low);
    };

    assert_long(0x100000001, 1, 1);
    assert_long(0x1100000101, 17, 257);
}

TEST(test_type_cast, merge2Bit32ToLong)
{
    auto assert_long = [](int high, int low, long val) {
        auto result = union_cast<std::array<int, 2>, long>({low, high});
        EXPECT_EQ(result, val);
    };

    assert_long(1, 1, 0x100000001);
    assert_long(17, 257, 0x1100000101);
    assert_long(0, -1297042716, 2997924580);

}
