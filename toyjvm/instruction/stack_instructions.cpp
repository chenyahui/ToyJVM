//
// Created by cyhone on 18-4-18.
//

#include <toyjvm/instruction/stack_instructions.h>

namespace jvm {
    void SWAP_Instruction::execute(jvm::JvmFrame &frame)
    {
        auto &op_stack = frame.operandStack();

        auto val1 = op_stack.pop<boost::any>();
        auto val2 = op_stack.pop<boost::any>();

        op_stack.push<boost::any>(val1);
        op_stack.push<boost::any>(val2);
    }

}