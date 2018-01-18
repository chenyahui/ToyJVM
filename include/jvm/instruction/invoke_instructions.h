#ifndef TOYJVM_INSTRUCTION_INVOKE_INSTRUCTIONS_H
#define TOYJVM_INSTRUCTION_INVOKE_INSTRUCTIONS_H

#include <jvm/instruction/base_instruction.h>
#include <jvm/rtdata/jvm_thread.h>
#include <jvm/rtdata/symbol_ref.h>

namespace cyh {
class INVOKE_STATIC_Instruction : public Index16Instruction {
public:
    void Execute(JFrame* frame) override;
};
class INVOKE_SPECIAL_Instruction : public Index16Instruction {
public:
    void Execute(JFrame* frame) override;
};

class INVOKE_VIRTUAL_Instruction : public Index16Instruction {
public:
    void Execute(JFrame* frame) override;
};

class INVOKE_INTERFACE_Instruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader) override;
    void Execute(JFrame* frame) override;

private:
    int index_;
};
}

#endif /* end of include guard: TOYJVM_INSTRUCTION_INVOKE_INSTRUCTIONS_H */
