#ifndef MY_JVM_INSTRUCTION_CONTROL_INSTRUCTIONS_H
#define MY_JVM_INSTRUCTION_CONTROL_INSTRUCTIONS_H

#include <jvm/instruction/instruction.h>

namespace cyh {
using GOTO_Instruction = BranchInstruction<j_short>;

class TABLE_SWITCH_Instruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader) override
    {
	reader.SkipPadding();

	default_offset_ = reader.Read<int>();
	low_ = reader.Read<int>();
	high_ = reader.Read<int>();

	int count = high_ - low_ + 1;
	jump_offsets_ = reader.ReadInt32s(count);
    };

    void Execute(JFrame& frame) override
    {
	auto index = frame.OpStack().Pop<int>();

	int offset;

	if (index >= low_ && index <= high_) {
	    offset = index;
	} else {
	    offset = default_offset_;
	}

	BranchJump(frame, offset);
    }

private:
    int default_offset_;
    int low_;
    int high_;
    std::vector<int> jump_offsets_;
};

class LOOKUP_SWITCH_Instruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader)
    {
	reader.SkipPadding();

	default_offset_ = reader.Read<int>();
	npairs_ = reader.Read<int>();

	match_offsets_ = reader.ReadInt32s(npairs_ * 2);
    }

    void Execute(JFrame& frame)
    {
	auto key = frame.OpStack().Pop<int>();

	int offset = default_offset_;

	for (int i = 0; i < npairs_ * 2; i += 2) {
	    if (match_offsets_[i] == key) {
		offset = match_offsets_[i + 1];
		break;
	    }
	}

	BranchJump(frame, offset);
    }

private:
    int default_offset_;
    int npairs_;
    std::vector<int> match_offsets_;
};
}
#endif
