#ifndef MY_JVM_INSTRUCTION_EXTENDED_INSTRUCTIONS_H
#define MY_JVM_INSTRUCTION_EXTENDED_INSTRUCTIONS_H

#include <jvm/instruction/instruction.h>

namespace cyh{
class WIDE_Instruction : public Instruction{
	public:
		void FetchOperands(ByteCodeReader& reader) override{
			auto opcode = reader.Read<u1>();

			switch(opcode){
				case 0x15:
					break;
				default:
					break;
			}
		}

		void Execute(JFrame& frame) override{
			modified_instruction_->Execute(frame);
		}
	private:
		Instruction* modified_instruction_;
};

template<bool isnull = true>
class IFNULL_Instruction : public BranchInstruction<j_short>{
	public:
		void Execute(JFrame& frame) override{
			auto ref = frame.OpStack().Pop<j_ref>();

			if((ref == NULL) == isnull){
				BranchJump(frame, this->offset);
			}
		}
};

using IFNONULL_Instruction = IFNULL_Instruction<false>;

using GOTO_W_Instruction = BranchInstruction<j_int>;
}
#endif
