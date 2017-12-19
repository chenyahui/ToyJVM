#ifndef MY_JVM_INSTRUCTION_CONST_INSTRUCTIONS_H
#define MY_JVM_INSTRUCTION_CONST_INSTRUCTIONS_H

#include <jvm/instruction/base_instruction.h>

namespace cyh {
template <typename T, int num>
class ConstInstruction : public NoOperandsInstruction {
public:
    void Execute(JFrame& frame) override
    {
	frame.OpStack().Push<T>(num);
    }
};

using NOP_Instruction = Instruction;

using ACONST_NULL_Instruction = ConstInstruction<j_ref, NULL>;
using DCONST_0_Instruction = ConstInstruction<double, 0>;
using DCONST_1_Instruction = ConstInstruction<double, 1>;

using FCONST_0_Instruction = ConstInstruction<float, 0>;
using FCONST_1_Instruction = ConstInstruction<float, 1>;
using FCONST_2_Instruction = ConstInstruction<float, 2>;

using ICONST_M1_Instruction = ConstInstruction<int, -1>;
using ICONST_0_Instruction = ConstInstruction<int, 0>;
using ICONST_1_Instruction = ConstInstruction<int, 1>;
using ICONST_2_Instruction = ConstInstruction<int, 2>;
using ICONST_3_Instruction = ConstInstruction<int, 3>;
using ICONST_4_Instruction = ConstInstruction<int, 4>;
using ICONST_5_Instruction = ConstInstruction<int, 5>;

using LCONST_0_Instruction = ConstInstruction<int64_t, 0>;
using LCONST_1_Instruction = ConstInstruction<int64_t, 1>;

template <typename T>
class PushInstruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader) override
    {
	val = reader.Read<T>();
    }

    void Execute(JFrame& frame) override
    {
	frame.OpStack().Push<T>(val);
    }

private:
    T val;
};

using BIPUSH_Instruction = PushInstruction<j_byte>;
using SIPUSH_Instruction = PushInstruction<j_short>;
}
#endif /*  */
