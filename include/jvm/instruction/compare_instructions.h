#ifndef MY_JVM_INSTRUCTION_COMPARE_INSTRUCTIONS_H
#define MY_JVM_INSTRUCTION_COMPARE_INSTRUCTIONS_H

#include <jvm/instruction/base_instruction.h>
#include <math.h>

namespace cyh {

template <typename T, int gflag = 1>
class CompareInstrution : public NoOperandsInstruction {
public:
    void Execute(JFrame& jframe)
    {
	auto op_stack = jframe.OpStack();

	auto v2 = op_stack.Pop<T>();
	auto v1 = op_stack.Pop<T>();

	int result = 0;

	if (isnan(v2) || isnan(v1)) {
	    result = gflag;
	} else if (v1 > v2) {
	    result = 1;
	} else if (v1 < v2) {
	    result = -1;
	}

	op_stack.Push<int>(result);
    }
};

using LCMP_Instruction = CompareInstrution<j_long>;
using FCMPG_Instruction = CompareInstrution<j_float, 1>;
using FCMPL_Instruction = CompareInstrution<j_float, -1>;
using DCMPG_Instruction = CompareInstrution<j_double, 1>;
using DCMPL_Instruction = CompareInstrution<j_double, -1>;

enum class CondType {
    EQ,
    NE,
    LT,
    LE,
    GT,
    GE
};
template <typename T, CondType cond, bool icmp = false>
class IfCond_Instruction : public BranchInstruction<> {
public:
    void Execute(JFrame& frame) override
    {
	auto op_stack = frame.OpStack();

	auto v2 = op_stack.Pop<T>();
	int v1 = 0;

	if (icmp) {
	    v1 = op_stack.Pop<T>();
	}

	bool jump = false;
	switch (cond) {
	case CondType::EQ:
	    jump = v2 == v1;
	    break;
	case CondType::NE:
	    jump = v2 != v1;
	    break;
	case CondType::LT:
	    jump = v2 > v1;
	    break;
	case CondType::LE:
	    jump = v2 >= v1;
	    break;
	case CondType::GT:
	    jump = v2 > v1;
	    break;
	case CondType::GE:
	    jump = v2 >= v1;
	    break;
	}

	if (jump) {
	    BranchJump(frame, this->offset);
	}
    };
};

#define GENE_COND(Type)                                         \
    using IF##Type##_Instruction = IfCond_Instruction<int, CondType::Type, false>; \
    using IF_ICMP##Type##_Instruction = IfCond_Instruction<int, CondType::Type, true>;

GENE_COND(EQ)
GENE_COND(NE)
GENE_COND(LT)
GENE_COND(LE)
GENE_COND(GT)
GENE_COND(GE)

using IF_ACMPEQ_Instruction = IfCond_Instruction<j_ref, CondType::EQ, true>;
using IF_ACMPNE_Instruction = IfCond_Instruction<j_ref, CondType::NE, true>;

}
#endif
