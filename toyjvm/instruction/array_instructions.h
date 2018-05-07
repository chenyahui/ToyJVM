//
// Created by cyhone on 18-4-27.
//

#ifndef TOYJVM_ARRAY_INSTRUCTIONS_H
#define TOYJVM_ARRAY_INSTRUCTIONS_H

#include <toyjvm/instruction/base_instruction.h>

namespace jvm {
    class NEWARRAY_Instruction : public BaseOneOperandInstruction<u1> {
    public:
        void execute(JvmFrame &frame) override;
    };

    class ANEWARRAY_Instruction : public BaseOneOperandInstruction<u2> {
    public:
        void execute(JvmFrame &frame) override;
    };

    class ARRAYLENGTH_Instruction : public BaseInstruction {
    public:
        void execute(JvmFrame &frame) override;
    };

    class MULTIANEWARRAY_Instruction : public BaseInstruction {
    public:
        void fetchOperands(ByteCodeReader &reader) override;

        void execute(JvmFrame &frame) override;
    private:
        std::vector<int> popAndCheckCounts(OperandStack& opstack);
        JvmBaseArray* newMultiDArray(std::vector<int>& counts, JvmClass* klass);
    private:
        size_t index_;
        u1 dimensions_;
    };
}
#endif //TOYJVM_ARRAY_INSTRUCTIONS_H
