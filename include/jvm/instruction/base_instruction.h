#ifndef MY_JVM_INSTRUCTION_INSTRCUTION_H
#define MY_JVM_INSTRUCTION_INSTRCUTION_H

#include <jvm/instruction/bytecode_reader.h>
#include <jvm/rtdata/jvm_frame.h>

namespace cyh {
class WIDE_Instruction;
class Instruction {
public:
    virtual void FetchOperands(ByteCodeReader&){};
    virtual void Execute(JFrame&){};
};

class NoOperandsInstruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader&) override {}
};

void BranchJump(JFrame& frame, int offset);

template <typename T = u2>
class BranchInstruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader) override
    {
	offset = static_cast<int>(reader.Read<T>());
    }
    virtual void Execute(JFrame& frame) override
    {
	BranchJump(frame, offset);
    }

    friend class WIDE_Instruction;

protected:
    int offset;
};

template <typename T = u1>
class Index8Instruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader) override
    {
	index = static_cast<int>(reader.Read<T>());
    }

    friend class WIDE_Instruction;

protected:
    int index;
};
}
#endif /* ifndef  */
