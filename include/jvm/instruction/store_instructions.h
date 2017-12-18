#ifndef MY_JVM_INSTRUCTION_STORE_INSTRUCTIONS_H
#define MY_JVM_INSTRUCTION_STORE_INSTRUCTIONS_H

#include <jvm/instruction/instruction.h>
// 25
namespace cyh {
template <typename T>
void store(JFrame& frame, int index)
{
    T val = frame.OpStack().Pop<T>();
    frame.LocalVars().Set<T>(index, val);
}

template <typename T>
class StoreInstruction : public Index8Instruction {
public:
    void Execute(JFrame& frame) override
    {
	store<T>(frame, index);
    }
};

template <typename T, int index>
class StoreConstInstruction : public NoOperandsInstruction {
public:
    void Execute(JFrame& frame) override
    {
	store<T>(frame, index);
    }
};
#define GENE_STORES(prefix, type)                                       \
    using prefix##STORE_Instruction = StoreInstruction<type>;           \
    using prefix##STORE_0_Instruction = StoreConstInstruction<type, 0>; \
    using prefix##STORE_1_Instruction = StoreConstInstruction<type, 1>; \
    using prefix##STORE_2_Instruction = StoreConstInstruction<type, 2>; \
    using prefix##STORE_3_Instruction = StoreConstInstruction<type, 3>;

GENE_STORES(I, int)
GENE_STORES(F, float)
GENE_STORES(D, double)
GENE_STORES(L, j_long)
GENE_STORES(A, j_ref)
}
#endif /* MY_JVM_INSTRUCTION_STORE_STORE_INSTRUCTIONS_H */
