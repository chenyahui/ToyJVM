//
// Created by cyhone on 18-4-17.
//

#ifndef TOYJVM_STORE_INSTRUCTION_H
#define TOYJVM_STORE_INSTRUCTION_H

#include <toyjvm/instruction/base_instruction.h>
#include <toyjvm/utilities/jvm_types.h>

namespace jvm {
    template<typename T, int INDEX>
    class StoreInstruction : public BaseLoadStoreInstruction<u1, INDEX> {
    public:
        void execute(JvmFrame &frame) override
        {
            T val = frame.operandStack().pop<T>();
            frame.operandStack().set<T>(BaseLoadStoreInstruction<u1, INDEX>::index_, val);
        }
    };

    template<typename T>
    class ArrayStoreInstruction : public BaseInstruction {
    public:
        virtual void execute(JvmFrame &frame)
        {
            auto &opstack = frame.operandStack();
            auto val = opstack.pop<T>();
            auto index = opstack.pop<int>();
            auto base_arr = opstack.pop<JvmBaseArray *>();

            auto arr_ref = dynamic_cast<JvmArray<T> *>(base_arr);
            assert(arr_ref != nullptr);
            assert(index >= 0 && index < arr_ref->arrayLen());

            arr_ref->set(index, val);
        }
    };

#define GENE_STORES(prefix, type)                                       \
    using prefix##STORE_Instruction = StoreInstruction<type,-1>;           \
    using prefix##STORE_0_Instruction = StoreInstruction<type, 0>; \
    using prefix##STORE_1_Instruction = StoreInstruction<type, 1>; \
    using prefix##STORE_2_Instruction = StoreInstruction<type, 2>; \
    using prefix##STORE_3_Instruction = StoreInstruction<type, 3>; \
    using prefix##ASTORE_Instruction = ArrayStoreInstruction<type>;

    GENE_STORES(I, jint)
    GENE_STORES(F, jfloat)
    GENE_STORES(D, jdouble)
    GENE_STORES(L, jlong)
    GENE_STORES(A, jref)

#define GENE_ARRAY_STORES(prefix, type) \
    using prefix##ASTORE_Instruction = ArrayStoreInstruction<type>;

    GENE_ARRAY_STORES(B, jref)
    GENE_ARRAY_STORES(C, jref)
    GENE_ARRAY_STORES(S, jref)

#undef GENE_STORES
}
#endif //TOYJVM_STORE_INSTRUCTION_H
