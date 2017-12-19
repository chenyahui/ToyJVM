#include <jvm/instruction/control_instructions.h>

namespace cyh {
void TABLE_SWITCH_Instruction::FetchOperands(ByteCodeReader& reader)
{
    reader.SkipPadding();

    default_offset_ = reader.Read<int>();
    low_ = reader.Read<int>();
    high_ = reader.Read<int>();

    int count = high_ - low_ + 1;
    jump_offsets_ = reader.ReadInt32s(count);
};

void TABLE_SWITCH_Instruction::Execute(JFrame& frame)
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
void LOOKUP_SWITCH_Instruction::FetchOperands(ByteCodeReader& reader)
{
    reader.SkipPadding();

    default_offset_ = reader.Read<int>();
    npairs_ = reader.Read<int>();

    match_offsets_ = reader.ReadInt32s(npairs_ * 2);
}

void LOOKUP_SWITCH_Instruction::Execute(JFrame& frame)
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
}
