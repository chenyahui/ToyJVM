//
// Created by cyhone on 18-4-18.
//

#include <toyjvm/instruction/math_instructions.h>

namespace jvm {
    void IINC_Instruction::execute(jvm::JvmFrame &frame)
    {
        auto &local_vars = frame.localSlots();
        auto val = local_vars.at<jint>(index_);
        local_vars.set<jint>(index_, val + const_);
    }

    void IINC_Instruction::fetchOperands(jvm::ByteCodeReader &reader)
    {
        index_ = static_cast<int>(reader.read<u1>());
        const_ = static_cast<int>(reader.read<u1>());
    }
}