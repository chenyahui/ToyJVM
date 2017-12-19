#ifndef MY_JVM_INSTRUCTION_MATH_INSTRUCTIONS_H
#define MY_JVM_INSTRUCTION_MATH_INSTRUCTIONS_H

#include <cmath>
#include <functional>
#include <jvm/instruction/base_instruction.h>

namespace cyh {
template <typename T, typename Op>
class MathInstruction : public NoOperandsInstruction {
public:
    void Execute(JFrame& frame) override
    {
	auto op_stack = frame.OpStack();

	auto v2 = op_stack.Pop<T>();
	auto v1 = op_stack.Pop<T>();

	Op op;
	auto result = op(v1, v2);

	op_stack.Push<T>(result);
    }
};
#define GENE_MATHS(prefix, type)                                                   \
    using prefix##REM_Instruction = MathInstruction<type, std::modulus<type> >;    \
    using prefix##ADD_Instruction = MathInstruction<type, std::plus<type> >;       \
    using prefix##DIV_Instruction = MathInstruction<type, std::divides<type> >;    \
    using prefix##MUL_Instruction = MathInstruction<type, std::multiplies<type> >; \
    using prefix##SUB_Instruction = MathInstruction<type, std::minus<type> >;      \
    using prefix##NEG_Instruction = MathInstruction<type, std::negate<type> >;

GENE_MATHS(I, int)
GENE_MATHS(D, double)
GENE_MATHS(L, j_long)
GENE_MATHS(f, float)

#define GENE_BOOLEANS(prefix, type)                                             \
    using prefix##AND_Instruction = MathInstruction<type, std::bit_and<type> >; \
    using prefix##OR_Instruction = MathInstruction<type, std::bit_or<type> >;   \
    using prefix##XOR_Instruction = MathInstruction<type, std::bit_xor<type> >;

GENE_BOOLEANS(I, int)
GENE_BOOLEANS(L, j_long)

// 左移, 逻辑右移、算术右移
template <typename T, bool is_left = true, bool is_logic = false>
class ShiftInstruction : public NoOperandsInstruction {
public:
    void Execute(JFrame& frame) override
    {
	auto op_stack = frame.OpStack();

	auto v2 = op_stack.Pop<int>();
	auto v1 = op_stack.Pop<T>();

	T result;
	if (is_left) {
	    result = v1 << v2;
	} else {
	    result = v1 >> v2;

	    if (is_logic) {
		int mask = 1 << (sizeof(T) - v2);
		mask |= mask - 1;

		result &= mask;
	    }
	}
	op_stack.Push<T>(result);
    }
};

#define GENE_SHIFTS(prefix, type)                                  \
    using prefix##SHL_Instruction = ShiftInstruction<type>;        \
    using prefix##SHR_Instruction = ShiftInstruction<type, false>; \
    using prefix##USHR_Instruction = ShiftInstruction<type, false, true>;

GENE_SHIFTS(I, int)
GENE_SHIFTS(L, j_long)

class IINC_Instruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader) override;
    void Execute(JFrame& frame) override;

private:
    u4 index_;
    j_int const_;
};
}
#endif
