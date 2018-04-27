//
// Created by cyhone on 18-4-26.
//

#include <toyjvm/instruction/instruction_factory.h>
#include <toyjvm/instruction/const_instructions.h>
#include <toyjvm/instruction/compare_instructions.h>
#include <toyjvm/instruction/control_instructions.h>
#include <toyjvm/instruction/convert_instructions.h>
#include <toyjvm/instruction/extend_instructions.h>
#include <toyjvm/instruction/load_instructions.h>
#include <toyjvm/instruction/math_instructions.h>
#include <toyjvm/instruction/ref_instructions.h>
#include <toyjvm/instruction/stack_instructions.h>
#include <toyjvm/instruction/store_instructions.h>

namespace jvm {
#define MakeInst(INST) \
    case InstructionTag::INST:{ \
        return std::make_shared<INST##_Instruction>(); \
    }

    std::shared_ptr<BaseInstruction> instructionFactory(InstructionTag tag)
    {

        switch (tag){
            MakeInst(ACONST_NULL)
        }
    }

#undef MakeInst
}