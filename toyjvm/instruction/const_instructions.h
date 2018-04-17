//
// Created by cyhone on 18-4-17.
//

#ifndef TOYJVM_CONST_INSTRUCTIONS_H
#define TOYJVM_CONST_INSTRUCTIONS_H

#include <toyjvm/instruction/base_instruction.h>

namespace jvm {
    template<typename T, T val>
    class BaseConstInstruction : public BaseInstruction {
    public:
        void execute(JvmFrame &frame) override
        {
            frame.operandStack().push<T>(val);
        }
    };

    using NOP_Instruction = BaseInstruction;

    using DCONST_0_Instruction = BaseConstInstruction<double, 0>;
    using DCONST_1_Instruction = BaseConstInstruction<double, 1>;

    using FCONST_0_Instruction = BaseConstInstruction<float, 0>;
    using FCONST_1_Instruction = BaseConstInstruction<float, 1>;
    using FCONST_2_Instruction = BaseConstInstruction<float, 2>;

    using ICONST_M1_Instruction = BaseConstInstruction<int, -1>;
    using ICONST_0_Instruction = BaseConstInstruction<int, 0>;
    using ICONST_1_Instruction = BaseConstInstruction<int, 1>;
    using ICONST_2_Instruction = BaseConstInstruction<int, 2>;
    using ICONST_3_Instruction = BaseConstInstruction<int, 3>;
    using ICONST_4_Instruction = BaseConstInstruction<int, 4>;
    using ICONST_5_Instruction = BaseConstInstruction<int, 5>;

    using LCONST_0_Instruction = BaseConstInstruction<int64_t, 0>;
    using LCONST_1_Instruction = BaseConstInstruction<int64_t, 1>;

    class ACONST_NULL_Instruction : public BaseInstruction {
    public:
        void execute(JvmFrame &frame) override
        {
            frame.operandStack().push<jref>(nullptr);
        }
    };

    template<typename T>
    class BasePushInstruction : public BaseInstruction {
    public:
        void fetchOperands(ByteCodeReader &reader) override
        {
            val = reader.read<T>();
        }

        void execute(JvmFrame &frame) override
        {
            frame.operandStack().push<T>(val);
        }

    public:
        T val;
    };

    using BIPUSH_Instruction = BasePushInstruction<jbyte>;
    using SIPUSH_Instruction = BasePushInstruction<jshort>;
}
#endif //TOYJVM_CONST_INSTRUCTIONS_H
