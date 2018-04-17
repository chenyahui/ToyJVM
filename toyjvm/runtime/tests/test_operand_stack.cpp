//
// Created by cyhone on 18-4-16.
//

#include <gtest/gtest.h>
#include <toyjvm/runtime/operand_stack.h>

using namespace jvm;

TEST(test_operant_stack, normal)
{
    OperandStack opstack(10);
    opstack.push<int>(100);
    opstack.push<int>(-100);
    opstack.push<long>(2997924580);
    opstack.push<long>(-2997924580);
    opstack.push<float>(3.1415926f);
    opstack.push<double>(2.1234567898713);
    opstack.push<int *>(nullptr);

    ASSERT_EQ(opstack.pop<int *>(), nullptr);
    ASSERT_EQ(opstack.pop<double>(), 2.1234567898713);
    ASSERT_EQ(opstack.pop<float>(), 3.1415926f);
    ASSERT_EQ(opstack.pop<long>(), -2997924580);
    ASSERT_EQ(opstack.pop<long>(), 2997924580);
    ASSERT_EQ(opstack.pop<int>(), -100);
    ASSERT_EQ(opstack.pop<int>(), 100);
}