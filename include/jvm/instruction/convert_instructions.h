#ifndef MY_JVM_INSTRUCTION_CONVERT_INSTRUCTIONS_H
#define MY_JVM_INSTRUCTION_CONVERT_INSTRUCTIONS_H

#include <jvm/instruction/instruction.h>
#include <jvm/utils/unsafe.h>

namespace cyh {
template <typename T1, typename T2>
class TypeConvertInstruction : public NoOperandsInstruction {
public:
    void Execute(JFrame& frame)
    {
	auto op_stack = frame.OpStack();

	T1 val = op_stack.Pop<T1>();
	T2 result = static_cast<T2>(val);

	op_stack.Push<T2>(result);
    }
};

using D2I_Instruction = TypeConvertInstruction<j_double, j_int>;
using D2L_Instruction = TypeConvertInstruction<j_double, j_long>;
using D2F_Instruction = TypeConvertInstruction<j_double, j_float>;

using I2L_Instruction = TypeConvertInstruction<j_int, j_long>;
using I2F_Instruction = TypeConvertInstruction<j_int, j_float>;
using I2D_Instruction = TypeConvertInstruction<j_int, j_double>;

using L2I_Instruction = TypeConvertInstruction<j_long, j_int>;
using L2D_Instruction = TypeConvertInstruction<j_long, j_double>;
using L2F_Instruction = TypeConvertInstruction<j_long, j_float>;

using F2I_Instruction = TypeConvertInstruction<j_float, j_int>;
using F2L_Instruction = TypeConvertInstruction<j_float, j_long>;
using F2D_Instruction = TypeConvertInstruction<j_float, j_double>;
}

#endif
