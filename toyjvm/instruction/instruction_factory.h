//
// Created by cyhone on 18-4-26.
//

#ifndef TOYJVM_INSTRUCTION_FACTORY_H
#define TOYJVM_INSTRUCTION_FACTORY_H

#include <toyjvm/instruction/base_instruction.h>
#include <toyjvm/instruction/instruction_tag.h>
#include <memory>
namespace jvm {
    std::shared_ptr<BaseInstruction> instructionFactory(InstructionTag tag);
}
#endif //TOYJVM_INSTRUCTION_FACTORY_H
