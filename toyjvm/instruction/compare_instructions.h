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
            }else{
                result = 0;
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
            T v2 = icmp ? op_stack.pop<T>() : 0;
            T v1 = op_stack.pop<T>();
            Comparison comparison;
            if (comparison(v1, v2)) {
                frame.jumpToBranch(this->operand_);
            }
        }
    };

    using IF_ICMPEQ_Instruction =  IfCond_Instruction<int, std::equal_to<int>, true>;
    using IFEQ_Instruction =  IfCond_Instruction<int, std::equal_to<int>, false>;

    using IF_ICMPNE_Instruction =  IfCond_Instruction<int, std::not_equal_to<int>, true>;
    using IFNE_Instruction =  IfCond_Instruction<int, std::not_equal_to<int>, false>;

    using IF_ICMPLT_Instruction =  IfCond_Instruction<int, std::less<int>, true>;
    using IFLT_Instruction =  IfCond_Instruction<int, std::less<int>, false>;

    using IF_ICMPLE_Instruction =  IfCond_Instruction<int, std::less_equal<int>, true>;
    using IFLE_Instruction =  IfCond_Instruction<int, std::less_equal<int>, false>;

    using IF_ICMPGT_Instruction =  IfCond_Instruction<int, std::greater<int>, true>;
    using IFGT_Instruction =  IfCond_Instruction<int, std::greater<int>, false>;

    using IF_ICMPGE_Instruction =  IfCond_Instruction<int, std::greater_equal<int>, true>;
    using IFGE_Instruction =  IfCond_Instruction<int, std::greater_equal<int>, false>;

    using IF_ACMPEQ_Instruction = IfCond_Instruction<jref, std::equal_to<jref>, true>;
    using IF_ACMPNE_Instruction = IfCond_Instruction<jref, std::not_equal_to<jref>, true>;

    using IFNULL_Instruction = IfCond_Instruction<jref, std::equal_to<jref>, false>;
    using IFNONNULL_Instruction = IfCond_Instruction<jref, std::not_equal_to<jref>, false>;
}
#endif //TOYJVM_COMPARE_INSTRUCTIONS_H
