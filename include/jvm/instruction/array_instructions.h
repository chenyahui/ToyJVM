#ifndef TOYJVM_INSTRUCTION_ARRAY_INSTRUCTIONS_H
#define TOYJVM_INSTRUCTION_ARRAY_INSTRUCTIONS_H
#include <jvm/instruction/base_instruction.h>
#include <jvm/rtdata/runtime_const_pool.h>
#include <jvm/rtdata/symbol_ref.h>

namespace cyh {
class NEW_ARRAY_Instruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader) override;

    void Execute(JFrame* frame) override;

private:
    JClass* GetPrimitiveArrayClass(ClassLoader* loader);

private:
    u1 atype_;
};

class ANEW_ARRAY_Instruction : public Index16Instruction {
public:
    void Execute(JFrame* frame) override;
};

class ARRAY_LENGTH_Instruction : public NoOperandsInstruction {
public:
    void Execute(JFrame* frame) override;
};

template <typename T>
class BaseArrayLoadInst : public NoOperandsInstruction {
public:
    void Execute(JFrame* frame) override
    {
	auto& opstack = frame->OpStack();
	auto index = opstack.Pop<int>();
	auto base_arr = opstack.Pop<JBaseArray*>();

	auto arr_ref = dynamic_cast<JArray<T>*>(base_arr);

	if (arr_ref == NULL) {
	    // TODO
	}

	if (index < 0 && index >= arr_ref->array_length()) {
	    // TODO
	}

	opstack.Push<T>((*arr_ref)[index]);
    }
};

#define ALOAD_GENE(SIGN, TYPE)    \
    using SIGN##ALOAD_Instruction \
	= BaseArrayLoadInst<TYPE>;

ALOAD_GENE(A, j_ref)
ALOAD_GENE(B, j_byte)
ALOAD_GENE(C, j_char)
ALOAD_GENE(D, j_double)
ALOAD_GENE(F, j_float)
ALOAD_GENE(I, j_int)
ALOAD_GENE(L, j_long)
ALOAD_GENE(S, j_short)

template <typename T>
class BaseArrayStoreInst : public NoOperandsInstruction {
public:
    void Execute(JFrame* frame) override
    {
	auto& opstack = frame->OpStack();
	auto val = opstack.Pop<T>();
	auto index = opstack.Pop<int>();
	auto base_arr = opstack.Pop<JBaseArray*>();

	auto arr_ref = dynamic_cast<JArray<T>*>(base_arr);

	if (arr_ref == NULL) {
	    // TODO
	}

	if (index < 0 && index >= arr_ref->array_length()) {
	    // TODO
	}

	(*arr_ref)[index] = val;
    }
};
#define ASTORE_GENE(SIGN, TYPE)    \
    using SIGN##ASTORE_Instruction \
	= BaseArrayStoreInst<TYPE>;

ASTORE_GENE(A, j_ref)
ASTORE_GENE(B, j_byte)
ASTORE_GENE(C, j_char)
ASTORE_GENE(D, j_double)
ASTORE_GENE(F, j_float)
ASTORE_GENE(I, j_int)
ASTORE_GENE(L, j_long)
ASTORE_GENE(S, j_short)

class MULTI_ANEW_ARRAY_Instruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader) override;
    void Execute(JFrame* frame) override;

private:
    JBaseArray* NewMultiDArray(std::vector<int>& counts, JClass* arr_class);
    std::vector<int> PopAndCheckCounts(OperandStack& opstack);
    u2 index_;
    u1 dimensions_;
};
}

#endif /* end of include guard: TOYJVM_INSTRUCTION_ARRAY_INSTRUCTIONS_H */
