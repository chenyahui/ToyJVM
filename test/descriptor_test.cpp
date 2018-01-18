#include <gtest/gtest.h>
#include <jvm/rtdata/method_descriptor.h>

using namespace cyh;

TEST(MethodDescriptorTest, Parser)
{
    MethodDescriptorParser descriptor("(IDLjava/lang/Thread;)Ljava/lang/Object;");
    auto result = descriptor.Parse();

    EXPECT_EQ(result.return_type, "java/lang/Object");
    EXPECT_EQ(result.param_types[0], "I");
    EXPECT_EQ(result.param_types[1], "D");
    EXPECT_EQ(result.param_types[2], "java/lang/Thread");
}

