#ifndef MY_JVM_INSTRUCTION_CONTROL_INSTRUCTIONS_H
#define MY_JVM_INSTRUCTION_CONTROL_INSTRUCTIONS_H

#include <jvm/instruction/base_instruction.h>

namespace cyh {
using GOTO_Instruction = BranchInstruction<>;

class TABLE_SWITCH_Instruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader) override;
    void Execute(JFrame* frame) override;

private:
    int default_offset_;
    int low_;
    int high_;
    std::vector<int> jump_offsets_;
};

class LOOKUP_SWITCH_Instruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader) override;
    void Execute(JFrame* frame) override;

private:
    int default_offset_;
    int npairs_;
    std::vector<int> match_offsets_;
};
}
#endif
