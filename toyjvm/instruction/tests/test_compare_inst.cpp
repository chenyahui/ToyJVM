//
// Created by cyhone on 18-4-28.
//

#include <gtest/gtest.h>
#include <toyjvm/instruction/compare_instructions.h>
#include <toyjvm/runtime/jvm_thread.h>

using namespace jvm;

//TEST(ConstInstruction, IFLT)
//{
//    bytes data = {};
//    ByteCodeReader reader(data);
//    JvmThread t;
//    JvmFrame frame(t, 10, 10);
//
//    IFLT_Instruction iflt_instruction;
//    iflt_instruction.run(reader, frame);
//
//}

TEST(ConstInstruction, DCMPL)
{
    // 上下文参数设置
    bytes data = {};
    ByteCodeReader reader(data);
    JvmThread t;
    JvmFrame frame(t, 10, 10);
    DCMPL_Instruction* dcmpl_instruction = new DCMPL_Instruction();
    auto& opstack = frame.operandStack();

    // 第一组
    opstack.push<jdouble>(1.0);
    opstack.push<jdouble>(1.1);
    dcmpl_instruction->run(reader, frame);
    EXPECT_EQ(opstack.pop<int>(), -1);

    opstack.push<jdouble>(1.0);
    opstack.push<jdouble>(1.0);
    dcmpl_instruction->run(reader, frame);
    EXPECT_EQ(opstack.pop<int>(), 0);

    opstack.push<jdouble>(1.2);
    opstack.push<jdouble>(1.0);
    dcmpl_instruction->run(reader, frame);
    EXPECT_EQ(opstack.pop<int>(), 1);
}
