#ifndef MY_JVM_INSTRUCTION_STACK_INSTRUCTIONS_H
#define MY_JVM_INSTRUCTION_STACK_INSTRUCTIONS_H

#include <jvm/instruction/base_instruction.h>
namespace cyh {
template <int num = 1>
class PopTmpInstruction : public NoOperandsInstruction {
public:
    void Execute(JFrame* frame)
    {
	auto op_stack = frame->OpStack();
	for (int i = 0; i < num; i++) {
	    op_stack.Pop<LocalSlot>();
	}
    }
};

using POP_Instruction = PopTmpInstruction<1>;
using POP2_Instruction = PopTmpInstruction<2>;

// X代表弹出几个，D代表复制栈顶前几个
template <int D = 1, int X = 0>
class DupTmpInstruction : public NoOperandsInstruction {
public:
    void Execute(JFrame* frame)
    {
	std::vector<LocalSlot> temp;

	auto op_stack = frame->OpStack();

	// 弹出
	for (int i = 0; i < X + D; i++) {
	    temp.push_back(op_stack.Pop<LocalSlot>());
	}

	// 入栈
	for (int i = 0; i < X + D; i++) {
	    op_stack.Push<LocalSlot>(temp[i]);
	}
	// 倒着复制
	for (int i = 0; i < D; i++) {
	    op_stack.Push<LocalSlot>(temp[i]);
	}
    }
};

using DUP_Instruction = DupTmpInstruction<1, 0>;
using DUP_X1_Instruction = DupTmpInstruction<1, 1>;
using DUP_X2_Instruction = DupTmpInstruction<1, 2>;
using DUP2_Instruction = DupTmpInstruction<2, 0>;
using DUP2_X1_Instruction = DupTmpInstruction<2, 1>;
using DUP2_X2_Instruction = DupTmpInstruction<2, 1>;

class SWAP_Instruction : public NoOperandsInstruction {
public:
    void Execute(JFrame* frame) override;
};
}
#endif
