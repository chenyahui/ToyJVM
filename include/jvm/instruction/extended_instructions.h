#ifndef MY_JVM_INSTRUCTION_EXTENDED_INSTRUCTIONS_H
#define MY_JVM_INSTRUCTION_EXTENDED_INSTRUCTIONS_H

#include <jvm/instruction/instruction.h>

namespace cyh {
class WIDE_Instruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader) override;
    void Execute(JFrame& frame) override;

private:
    Instruction* modified_instruction_;
};

template <bool isnull = true>
class IFNULL_Instruction : public BranchInstruction<> {
public:
    void Execute(JFrame& frame) override
    {
	auto ref = frame.OpStack().Pop<j_ref>();

	if ((ref == NULL) == isnull) {
	    BranchJump(frame, this->offset);
	}
    }
};

using IFNONULL_Instruction = IFNULL_Instruction<false>;

using GOTO_W_Instruction = BranchInstruction<u4>;
}
#endif
