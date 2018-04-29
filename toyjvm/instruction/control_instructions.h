//
// Created by cyhone on 18-4-18.
//

#ifndef TOYJVM_CONTROL_INSTRUCTIONS_H
#define TOYJVM_CONTROL_INSTRUCTIONS_H

#include <toyjvm/instruction/control_instructions.h>
#include <toyjvm/instruction/base_instruction.h>

namespace jvm {
    template<typename T>
    class GotoInstruction : public BaseOneOperandInstruction<T> {
    public:
        void execute(JvmFrame &frame) override
        {
            frame.jumpToBranch(this->operand_);
        }
    };

    using GOTO_Instruction = GotoInstruction<u2>;
    using GOTO_W_Instruction = GotoInstruction<u4>;

    class TABLESWITCH_Instruction : public BaseInstruction {
    public:
        void fetchOperands(ByteCodeReader &reader) override;

        void execute(JvmFrame &frame) override;


    private:
        int default_offset_;
        int low_;
        int high_;
        std::vector<int> jump_offsets_;
    };

    class LOOKUPSWITCH_Instruction : public BaseInstruction {
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
