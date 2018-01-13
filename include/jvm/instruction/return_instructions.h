#ifndef TOYJVM_INSTRUCTION_RETURN_INSTRUCTIONS_H
#define TOYJVM_INSTRUCTION_RETURN_INSTRUCTIONS_H
#include <jvm/instruction/base_instruction.h>
#include <jvm/rtdata/jvm_thread.h>
#include <jvm/utils/types.h>

namespace cyh {
class RETURN_Instruction : NoOperandsInstruction {
public:
    void Execute(JFrame* frame) override
    {
	frame->Thread()->PopFrame();
    }
};

template <typename T>
class BaseReturnInstruction : NoOperandsInstruction {
public:
    void Execute(JFrame* frame) override
    {
	auto jthread = frame->Thread();
	auto current_frame = jthread->PopFrame();
	auto invoker_frame = jthread->TopFrame();

	auto ret = current_frame->OpStack().Pop<T>();
	invoker_frame->OpStack().Push<T>();
    }
};

using IRETURN_Instruction = BaseReturnInstruction<int>;
using DRETURN_Instruction = BaseReturnInstruction<double>;
using FRETURN_Instruction = BaseReturnInstruction<float>;
using LRETURN_Instruction = BaseReturnInstruction<long>;
using ARETURN_Instruction = BaseReturnInstruction<j_ref>;
}

#endif /* end of include guard: TOYJVM_INSTRUCTION_RETURN_INSTRUCTIONS_H */
