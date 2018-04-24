//
// Created by cyhone on 18-4-17.
//

#include <gtest/gtest.h>
#include <toyjvm/instruction/const_instructions.h>

using namespace jvm;
TEST(ConstInstruction, normal)
{
    DCONST_0_Instruction dconst0Instruction;
    dconst0Instruction.fetchOperands();

}