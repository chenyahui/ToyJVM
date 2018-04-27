//
// Created by cyhone on 18-4-26.
//

#include <toyjvm/instruction/instruction_factory.h>
#include <toyjvm/instruction/const_instructions.h>
#include <toyjvm/instruction/compare_instructions.h>
#include <toyjvm/instruction/load_instructions.h>

namespace jvm {
#define MakeInst(INST) \
    case InstructionTag::INST:{ \
        return std::make_shared<INST##_Instruction>(); \
    }

    std::shared_ptr<BaseInstruction> instructionFactory(InstructionTag tag)
    {

        switch (tag) {
            MakeInst(ACONST_NULL)
            MakeInst(ALOAD)
            MakeInst(ALOAD_0)
            MakeInst(ALOAD_1)
            MakeInst(ALOAD_2)
            MakeInst(ALOAD_3)

        }
    }

#undef MakeInst
}