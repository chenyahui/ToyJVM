//
// Created by cyhone on 18-4-17.
//

#ifndef TOYJVM_LOAD_INSTRUCTION_H
#define TOYJVM_LOAD_INSTRUCTION_H

#include <toyjvm/instruction/base_instruction.h>
#include <toyjvm/utilities/jvm_types.h>
#include <toyjvm/runtime/jvm_reference.h>

namespace jvm {
    template<typename T, int INDEX>
    class LoadInstruction : public BaseLoadStoreInstruction<u1, INDEX> {
    public:
        void execute(JvmFrame &frame) override
        {
            const auto &local_vars = frame.localSlots();
            T val = local_vars.at<T>(BaseLoadStoreInstruction<u1, INDEX>::index_);
            frame.operandStack().push<T>(val);
        }
    };

    template<typename T>
    class ArrayLoadInstruction : public BaseInstruction {
    public:
        virtual void execute(JvmFrame &frame)
        {
            auto &opstack = frame.operandStack();
            auto index = opstack.pop<int>();
            auto base_arr = opstack.pop<jarr>();

            auto arr_ref = dynamic_cast<JvmArray<T> *>(base_arr);

            assert(arr_ref != nullptr);
            assert(index >= 0 && index < arr_ref->arrayLen());

            opstack.push<T>(arr_ref->at(index));
        }
    };

#define GENE_LOADS(prefix, type)                                      \
    using prefix##LOAD_Instruction = LoadInstruction<type, -1>;           \
    using prefix##LOAD_0_Instruction = LoadInstruction<type, 0>; \
    using prefix##LOAD_1_Instruction = LoadInstruction<type, 1>; \
    using prefix##LOAD_2_Instruction = LoadInstruction<type, 2>; \
    using prefix##LOAD_3_Instruction = LoadInstruction<type, 3>; \
    using prefix##ALOAD_Instruction = ArrayLoadInstruction<type>;

    GENE_LOADS(I, jint)
    GENE_LOADS(F, jfloat)
    GENE_LOADS(D, jdouble)
    GENE_LOADS(L, jlong)
    GENE_LOADS(A, jref)

#define GENE_ARRAY_LOADS(prefix, type)              \
    using prefix##ALOAD_Instruction = ArrayLoadInstruction<type>;

    GENE_ARRAY_LOADS(B, jref)
    GENE_ARRAY_LOADS(C, jref)
    GENE_ARRAY_LOADS(S, jref)

#undef GENE_LOADS
}
#endif //TOYJVM_LOAD_INSTRUCTION_H
