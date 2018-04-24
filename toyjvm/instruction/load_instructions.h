//
// Created by cyhone on 18-4-17.
//

#ifndef TOYJVM_LOAD_INSTRUCTION_H
#define TOYJVM_LOAD_INSTRUCTION_H

#include <toyjvm/instruction/base_instruction.h>
#include <toyjvm/utilities/jvm_types.h>

namespace jvm {
    template<typename T, int INDEX>
    class LoadInstruction : public BaseLoadStoreInstruction<T, INDEX> {
    public:
        void execute(JvmFrame &frame) override
        {
            const auto &local_vars = frame.localSlots();
            T val = local_vars.at<T>(index_);
            frame.operandStack().push<T>(val);
        }
    };

#define GENE_LOADS(prefix, type)                                      \
    using prefix##LOAD_Instruction = LoadInstruction<type, -1>;           \
    using prefix##LOAD_0_Instruction = LoadInstruction<type, 0>; \
    using prefix##LOAD_1_Instruction = LoadInstruction<type, 1>; \
    using prefix##LOAD_2_Instruction = LoadInstruction<type, 2>; \
    using prefix##LOAD_3_Instruction = LoadInstruction<type, 3>;

    GENE_LOADS(I, jint)
    GENE_LOADS(F, jfloat)
    GENE_LOADS(D, jdouble)
    GENE_LOADS(L, jlong)
    GENE_LOADS(A, jref)

#undef GENE_LOADS
}
#endif //TOYJVM_LOAD_INSTRUCTION_H
