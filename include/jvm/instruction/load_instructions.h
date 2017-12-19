#ifndef MY_JVM_INSTRUCTION_LOAD_INSTRUCTIONS_H
#define MY_JVM_INSTRUCTION_LOAD_INSTRUCTIONS_H
#include <jvm/instruction/base_instruction.h>
// 25
namespace cyh {
template <typename T>
void load(JFrame& frame, int index)
{
    auto local_vars = frame.LocalVars();
    T val = local_vars.Get<T>(index);
    frame.OpStack().Push<T>(val);
}

template <typename T>
class LoadInstruction : public Index8Instruction<> {
public:
    void Execute(JFrame& frame) override
    {
	load<T>(frame, index);
    }
};

template <typename T, int index>
class LoadConstInstruction : public NoOperandsInstruction {
public:

    void Execute(JFrame& frame) override
    {
	load<T>(frame, index);
    }
};

#define GENE_LOADS(prefix, type)                                      \
    using prefix##LOAD_Instruction = LoadInstruction<type>;           \
    using prefix##LOAD_0_Instruction = LoadConstInstruction<type, 0>; \
    using prefix##LOAD_1_Instruction = LoadConstInstruction<type, 1>; \
    using prefix##LOAD_2_Instruction = LoadConstInstruction<type, 2>; \
    using prefix##LOAD_3_Instruction = LoadConstInstruction<type, 3>;

GENE_LOADS(I, int)
GENE_LOADS(F, float)
GENE_LOADS(D, double)
GENE_LOADS(L, j_long)
GENE_LOADS(A, j_ref)

}
#endif /* ifndef  */
