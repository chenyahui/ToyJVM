//
// Created by cyhone on 18-4-18.
//

#ifndef TOYJVM_CONTROL_INSTRUCTIONS_H
#define TOYJVM_CONTROL_INSTRUCTIONS_H

#include <toyjvm/instruction/control_instructions.h>
#include "base_instruction.h"

namespace jvm {
    class GOTO_Instruction : public BaseOneOperandInstruction<jshort> {
    public:
        void execute(JvmFrame &frame) override
        {
            branchJump(frame, operand_);
        }
    };

    class TABLE_SWITCH_Instruction : public BaseInstruction {
    public:
        void fetchOperands(ByteCodeReader &reader) override;

        void execute(JvmFrame &frame) override;


    private:
        int default_offset_;
        int low_;
        int high_;
        std::vector<int> jump_offsets_;
    };

    class LOOKUP_SWITCH_Instruction : public BaseInstruction {
    public:
        void fetchOperands(ByteCodeReader &reader) override;

        void execute(JvmFrame &frame) override;

    private:
        int default_offset_;
        int npairs_;
        std::vector<int> match_offsets_;
    };
}
#endif //TOYJVM_CONTROL_INSTRUCTIONS_H
