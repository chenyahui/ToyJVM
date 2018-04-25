//
// Created by cyhone on 18-4-17.
//

#ifndef TOYJVM_STACK_INSTRUCTIONS_H
#define TOYJVM_STACK_INSTRUCTIONS_H

#include <toyjvm/instruction/base_instruction.h>

namespace jvm {
    template<int NUM>
    class PopInstruction : public BaseInstruction {
    public:
        void execute(JvmFrame &frame) override
        {
            auto &op_stack = frame.operandStack();
            for (int i = 0; i < NUM; i++) {
                op_stack.pop();
            }
        }
    };

    using POP_Instruction = PopInstruction<1>;
    using POP2_Instruction = PopInstruction<2>;

    template<int D, int X>
    class DupInstruction : public BaseInstruction {
    public:
        void execute(JvmFrame &frame) override
        {
            std::vector<boost::any> temp;
            auto &op_stack = frame.operandStack();

            // 弹出
            for (int i = 0; i < X + D; i++) {
                temp.push_back(op_stack.pop());
            }

            // 入栈
            for (int i = 0; i < X + D; i++) {
                op_stack.push(temp[i]);
            }
            // 倒着复制
            for (int i = 0; i < D; i++) {
                op_stack.push(temp[i]);
            }
        }
    };

    using DUP_Instruction = DupInstruction<1, 0>;
    using DUP_X1_Instruction = DupInstruction<1, 1>;
    using DUP_X2_Instruction = DupInstruction<1, 2>;
    using DUP2_Instruction = DupInstruction<2, 0>;
    using DUP2_X1_Instruction = DupInstruction<2, 1>;
    using DUP2_X2_Instruction = DupInstruction<2, 1>;

    class SWAP_Instruction : public BaseInstruction {
    public:
        void execute(JvmFrame &frame) override;
    };
};
#endif //TOYJVM_STACK_INSTRUCTIONS_H
