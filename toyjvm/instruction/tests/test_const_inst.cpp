//
// Created by cyhone on 18-4-17.
//

#include <gtest/gtest.h>
#include <toyjvm/instruction/const_instructions.h>

using namespace jvm;

TEST(ConstInstruction, normal)
{
    bytes data = {};
    ByteCodeReader reader(data);
    JvmFrame frame(10, 10);

    DCONST_1_Instruction dconst1Instruction;
    dconst1Instruction.run(reader, frame);

    EXPECT_EQ(frame.operandStack().pop<jdouble>(), 1.0);

}