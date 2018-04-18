//
// Created by cyhone on 18-4-17.
//

#ifndef TOYJVM_MATH_INSTRUCTIONS_H
#define TOYJVM_MATH_INSTRUCTIONS_H

#include <toyjvm/instruction/base_instruction.h>
#include <toyjvm/common/exception.h>
#include <cmath>
#include <toyjvm/instruction/instruction_code.h>

namespace jvm {
    // 单操作数的数学指令
    template<typename T, typename Solver>
    class P1MathInstruction : public BaseInstruction {
    public:
        void execute(JvmFrame &frame) override
        {
            auto &op_stack = frame.operandStack();
            auto v2 = op_stack.pop<T>();
            Solver solver;
            T result = solver(v2);
            op_stack.push<T>(result);
        }
    };

    template<typename T, typename Solver, bool zeroCheck = false>
    class P2MathInstruction : public BaseInstruction {
    public :
        void execute(JvmFrame &frame) override
        {
            auto &op_stack = frame.operandStack();
            Solver solver;

            auto v2 = op_stack.pop<T>();
            auto v1 = op_stack.pop<T>();
            if (v2 == 0 && zeroCheck) {
                throw JVMError("zero error");
            }
            T result = solver(v1, v2);

            op_stack.push<T>(result);
        }
    };

    template<typename T>
    class Fmod {
    public:
        constexpr T operator()(const T &lhs, const T &rhs) const
        {
            return std::fmod(lhs, rhs);
        }
    };

#define GENE_MATHS(prefix, type)                                                   \
    using prefix##REM_Instruction = P2MathInstruction<type, Fmod<type> >;            \
    using prefix##ADD_Instruction = P2MathInstruction<type, std::plus<type> >;       \
    using prefix##DIV_Instruction = P2MathInstruction<type, std::divides<type> >;    \
    using prefix##MUL_Instruction = P2MathInstruction<type, std::multiplies<type> >; \
    using prefix##SUB_Instruction = P2MathInstruction<type, std::minus<type> >;      \
    using prefix##NEG_Instruction = P1MathInstruction<type, std::negate<type> >;

    GENE_MATHS(I, jint)
    GENE_MATHS(D, jdouble)
    GENE_MATHS(L, jlong)
    GENE_MATHS(F, jfloat)
#undef GENE_MATHS

#define GENE_BOOLEANS(prefix, type)                                             \
    using prefix##AND_Instruction = P2MathInstruction<type, std::bit_and<type> >; \
    using prefix##OR_Instruction = P2MathInstruction<type, std::bit_or<type> >;   \
    using prefix##XOR_Instruction = P2MathInstruction<type, std::bit_xor<type> >;

    GENE_BOOLEANS(I, jint)
    GENE_BOOLEANS(L, jlong)
#undef GENE_BOOLEANS

    enum class ShiftType {
        SHL,
        SHR,
        USHR
    };

    template<typename T, ShiftType tag>
    class ShiftInstruction : public BaseInstruction {
    public:
        void execute(JvmFrame &frame) override
        {
            auto &op_stack = frame.operandStack();

            auto shift = (op_stack.pop<u4>()) & 0x1f;
            auto value = op_stack.pop<T>();

            jint mask = ~(~0 << (32 - shift));

            T result;
            switch (tag) {
                case ShiftType::SHL: {
                    result = value << shift;
                    break;
                }
                case ShiftType::SHR: {
                    result = value >> shift;
                    break;
                }
                case ShiftType::USHR: {
                    result = (value >> shift) & mask;
                    break;
                }
            }

            op_stack.push<T>(result);
        }
    };

#define GENE_SHIFTS(prefix, type)                                  \
    using prefix##SHL_Instruction = ShiftInstruction<type, ShiftType::SHL>;        \
    using prefix##SHR_Instruction = ShiftInstruction<type, ShiftType::SHR>; \
    using prefix##USHR_Instruction = ShiftInstruction<type, ShiftType::USHR>;

    GENE_SHIFTS(I, jint)
    GENE_SHIFTS(L, jlong)
#undef GENE_SHIFTS

    class IINC_Instruction : public BaseInstruction {
    public:
        void fetchOperands(ByteCodeReader &reader) override;

        void execute(JvmFrame &frame) override;

    private:
        int index_;
        int const_;
    };
}
#endif //TOYJVM_MATH_INSTRUCTIONS_H
