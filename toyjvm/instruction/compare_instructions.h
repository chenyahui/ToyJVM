//
// Created by cyhone on 18-4-18.
//

#ifndef TOYJVM_COMPARE_INSTRUCTIONS_H
#define TOYJVM_COMPARE_INSTRUCTIONS_H

#include <math.h>
#include <toyjvm/instruction/base_instruction.h>
#include <functional>

namespace jvm {
    template<typename T, int gflag = 1>
    class CompareInstrution : public BaseInstruction {
    public:
        void execute(JvmFrame &frame) override
        {
            auto &op_stack = frame.operandStack();

            auto v2 = op_stack.pop<T>();
            auto v1 = op_stack.pop<T>();
            int result = 0;

            if (isnan(v2) || isnan(v1)) {
                result = gflag;
            } else if (v1 > v2) {
                result = 1;
            } else if (v1 < v2) {
                result = -1;
            }

            op_stack.push<int>(result);
        }
    };

    using LCMP_Instruction = CompareInstrution<jlong, 1>;
    using FCMPG_Instruction = CompareInstrution<jfloat, 1>;
    using FCMPL_Instruction = CompareInstrution<jfloat, -1>;
    using DCMPG_Instruction = CompareInstrution<jdouble, 1>;
    using DCMPL_Instruction = CompareInstrution<jdouble, -1>;

    template<typename T, typename Comparison, bool icmp>
    class IfCond_Instruction : public BaseOneOperandInstruction<jshort> {
    public:
        void execute(JvmFrame &frame) override
        {
            auto &op_stack = frame.operandStack();
            T v2 = icmp ? 0 : op_stack.pop<T>();
            T v1 = op_stack.pop<T>();
            Comparison comparison;
            if (comparison(v1, v2)) {
                branchJump(frame, this->operand_);
            }
        }
    };

#define GENE_IF(type, op) \
    using IF_ICMP##type_Instruction = IfCond_Instruction<int, std::##op, true>; \
    using IF##type_Instruction =  IfCond_Instruction<int, std::##op, false>;   \

    GENE_IF(EQ, equal_to)
    GENE_IF(NE, not_equal_to)
    GENE_IF(LT, less)
    GENE_IF(LE, less_equal)
    GENE_IF(GT, greater)
    GENE_IF(LE, greater_equal)

    using IF_ACMPEQ_Instruction = IfCond_Instruction<jref, std::equal_to, true>;
    using IF_ACMPNE_Instruction = IfCond_Instruction<jref, std::not_equal_to, true>;
}
#endif //TOYJVM_COMPARE_INSTRUCTIONS_H
