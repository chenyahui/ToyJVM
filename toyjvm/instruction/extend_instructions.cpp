//
// Created by cyhone on 18-4-18.
//

#include <toyjvm/instruction/extend_instructions.h>
#include <toyjvm/instruction/instruction_tag.h>
#include <toyjvm/instruction/load_instructions.h>
#include <toyjvm/instruction/store_instructions.h>
#include <toyjvm/instruction/math_instructions.h>

namespace jvm {
    void WIDE_Instruction::fetchOperands(jvm::ByteCodeReader &reader)
    {
        auto tag = reader.read<u1>();

#define GENE_CASE(TAG) \
case InstructionTag::##TAG: \
        modified_instruction_ = new TAG##_Instruction(); \
        break;

        switch (static_cast<InstructionTag>(tag)) {
            GENE_CASE(ILOAD)
            GENE_CASE(LLOAD)
            GENE_CASE(FLOAD)
            GENE_CASE(DLOAD)
            GENE_CASE(ALOAD)
            GENE_CASE(ISTORE)
            GENE_CASE(LSTORE)
            GENE_CASE(FSTORE)
            GENE_CASE(DSTORE)
            GENE_CASE(ASTORE)
            GENE_CASE(IINC)
            case InstructionTag::RET:
                throw JVMError("todo ret");
                // TODO ret
        }
        modified_instruction_->fetchOperands(reader);
    }

    void WIDE_Instruction::execute(JvmFrame &frame)
    {
        modified_instruction_->execute(frame);
    }
}