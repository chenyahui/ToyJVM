//
// Created by cyhone on 18-4-18.
//

#ifndef TOYJVM_CONVERT_INSTRUCTIONS_H
#define TOYJVM_CONVERT_INSTRUCTIONS_H

#include <toyjvm/instruction/base_instruction.h>

namespace jvm {
    template<typename T1, typename T2>
    class ConvertInstruction : public BaseInstruction {
    public:
        void execute(JvmFrame &frame) override
        {
            auto &op_stack = frame.operandStack();

            T1 val = op_stack.pop<T1>();
            auto result = static_cast<T2>(val);

            op_stack.push<T2>(result);
        }
    };

    using D2I_Instruction = ConvertInstruction<jdouble, jint>;
    using D2L_Instruction = ConvertInstruction<jdouble, jlong>;
    using D2F_Instruction = ConvertInstruction<jdouble, jfloat>;

    using I2L_Instruction = ConvertInstruction<jint, jlong>;
    using I2F_Instruction = ConvertInstruction<jint, jfloat>;
    using I2D_Instruction = ConvertInstruction<jint, jdouble>;
    using I2S_Instruction = ConvertInstruction<jint, jshort>;
    using I2C_Instruction = ConvertInstruction<jint, jchar>;
    using I2B_Instruction = ConvertInstruction<jint, jbyte>;


    using L2I_Instruction = ConvertInstruction<jlong, jint>;
    using L2D_Instruction = ConvertInstruction<jlong, jdouble>;
    using L2F_Instruction = ConvertInstruction<jlong, jfloat>;

    using F2I_Instruction = ConvertInstruction<jfloat, jint>;
    using F2L_Instruction = ConvertInstruction<jfloat, jlong>;
    using F2D_Instruction = ConvertInstruction<jfloat, jdouble>;
}
#endif //TOYJVM_CONVERT_INSTRUCTIONS_H
