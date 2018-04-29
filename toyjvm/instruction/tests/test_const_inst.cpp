//
// Created by cyhone on 18-4-17.
//

#include <gtest/gtest.h>
#include <toyjvm/instruction/const_instructions.h>
#include "test_inst_context.h"

using namespace jvm;
using namespace jvm_test;

TEST_F(InstTestContext, dconst1)
{
    bytes data = {};
    ByteCodeReader reader(data);

    DCONST_1_Instruction dconst1Instruction;
    dconst1Instruction.run(reader, *frame_);
    EXPECT_EQ(opstack_->pop<jdouble>(), 1.0);
}