//
// Created by cyhone on 18-4-18.
//

#include <toyjvm/instruction/control_instructions.h>

namespace jvm {
    void TABLESWITCH_Instruction::fetchOperands(ByteCodeReader &reader)
    {
        reader.skipPadding();

        default_offset_ = reader.read<int>();
        low_ = reader.read<int>();
        high_ = reader.read<int>();

        int count = high_ - low_ + 1;
        jump_offsets_ = reader.batchRead<int>(count);
    };

    void TABLESWITCH_Instruction::execute(jvm::JvmFrame &frame)
    {
        auto index = frame.operandStack().pop<int>();

        int offset;
        if (index >= low_ && index <= high_) {
            offset = index;
        } else {
            offset = default_offset_;
        }

        frame.jumpToBranch(offset);
    }

    void LOOKUPSWITCH_Instruction::fetchOperands(ByteCodeReader &reader)
    {
        reader.skipPadding();

        default_offset_ = reader.read<int>();
        npairs_ = reader.read<int>();

        match_offsets_ = reader.batchRead<int>(npairs_ * 2);
    }

    void LOOKUPSWITCH_Instruction::execute(jvm::JvmFrame &frame)
    {
        auto key = frame.operandStack().pop<int>();

        int offset = default_offset_;

        for (int i = 0; i < npairs_ * 2; i += 2) {
            if (match_offsets_[i] == key) {
                offset = match_offsets_[i + 1];
                break;
            }
        }
        frame.jumpToBranch(offset);
    }
}