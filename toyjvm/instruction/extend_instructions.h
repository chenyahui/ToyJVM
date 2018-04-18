//
// Created by cyhone on 18-4-18.
//

#ifndef TOYJVM_EXTEND_INSTRUCTIONS_H
#define TOYJVM_EXTEND_INSTRUCTIONS_H

#include <toyjvm/instruction/base_instruction.h>

namespace jvm {
    class WIDE_Instruction : public BaseInstruction {
    public:
        void fetchOperands(ByteCodeReader &reader) override;

        void execute(JvmFrame &frame) override;

        ~WIDE_Instruction()
        {
            delete modified_instruction_;
        }

    private:
        BaseInstruction *modified_instruction_;
    };
}
#endif //TOYJVM_EXTEND_INSTRUCTIONS_H
