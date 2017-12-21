#ifndef MY_JVM_INSTRUCTION_EXTENDED_INSTRUCTIONS_H
#define MY_JVM_INSTRUCTION_EXTENDED_INSTRUCTIONS_H

#include <jvm/instruction/base_instruction.h>
namespace cyh {
class WIDE_Instruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader) override;
    void Execute(JFrame* frame) override;

private:
    Instruction* modified_instruction_;
};

template <bool isnull = true>
class IfnullTmpInstruction : public BranchInstruction<> {
public:
    void Execute(JFrame* frame) override
    {
	auto ref = frame->OpStack().Pop<j_ref>();

	if ((ref == NULL) == isnull) {
	    BranchJump(frame, this->offset);
	}
    }
};

using IFNULL_Instruction = IfnullTmpInstruction<true>;
using IFNONNULL_Instruction = IfnullTmpInstruction<false>;

using GOTO_W_Instruction = BranchInstruction<u4>;
}
#endif
