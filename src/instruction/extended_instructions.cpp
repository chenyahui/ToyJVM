#include <jvm/instruction/extended_instructions.h>
#include <jvm/instruction/load_instructions.h>
#include <jvm/instruction/store_instructions.h>
#include <jvm/instruction/math_instructions.h>

namespace cyh {
#define GENE_CASE(Code, INS)                                      \
    case Code: {                                                  \
	INS##_Instruction* instruction = new INS##_Instruction(); \
	instruction->index = static_cast<int>(reader.Read<u2>()); \
	modified_instruction_ = instruction;                      \
	break;                                                    \
    }

void WIDE_Instruction::FetchOperands(ByteCodeReader& reader)
{
    auto opcode = reader.Read<u1>();

    switch (opcode) {
    	GENE_CASE(0x15, ILOAD)
	GENE_CASE(0x16, LLOAD)
	GENE_CASE(0x17, FLOAD)
	GENE_CASE(0x18, DLOAD)
	GENE_CASE(0x19, ALOAD)
	GENE_CASE(0x36, ISTORE)
	GENE_CASE(0x37, LSTORE)
	GENE_CASE(0x38, FSTORE)
	GENE_CASE(0x39, DSTORE)
	GENE_CASE(0x3a, ASTORE)
	GENE_CASE(0x84, IINC)
	// TODO ret
    }
}
void WIDE_Instruction::Execute(JFrame* frame)
{
    modified_instruction_->Execute(frame);
}
}
