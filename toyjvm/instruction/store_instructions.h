//
// Created by cyhone on 18-4-17.
//

#ifndef TOYJVM_STORE_INSTRUCTION_H
#define TOYJVM_STORE_INSTRUCTION_H

#include <toyjvm/instruction/base_instruction.h>
#include <toyjvm/common/jvm_types.h>

namespace jvm {
    template<typename T, int INDEX>
    class StoreInstruction : public BaseLoadStoreInstruction<T, INDEX> {
    public:
        void execute(JvmFrame &frame) override
        {
            T val = frame.operandStack().pop<T>();
            frame.operandStack().set<T>(index_, val);
        }
    };

#define GENE_STORES(prefix, type)                                       \
    using prefix##STORE_Instruction = StoreInstruction<type,-1>;           \
    using prefix##STORE_0_Instruction = StoreInstruction<type, 0>; \
    using prefix##STORE_1_Instruction = StoreInstruction<type, 1>; \
    using prefix##STORE_2_Instruction = StoreInstruction<type, 2>; \
    using prefix##STORE_3_Instruction = StoreInstruction<type, 3>;

    GENE_STORES(I, jint)
    GENE_STORES(F, jfloat)
    GENE_STORES(D, jdouble)
    GENE_STORES(L, jlong)
    GENE_STORES(A, jref)

#undef GENE_STORES
}
#endif //TOYJVM_STORE_INSTRUCTION_H
