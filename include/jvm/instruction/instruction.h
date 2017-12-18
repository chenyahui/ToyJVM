#ifndef MY_JVM_INSTRUCTION_INSTRCUTION_H
#define MY_JVM_INSTRUCTION_INSTRCUTION_H

#include <jvm/instruction/bytecodereader.h>
#include <jvm/rtdata/jvm_frame.h>

namespace cyh {
class Instruction {
public:
    virtual void FetchOperands(ByteCodeReader&){};
    virtual void Execute(JFrame&){};
};

class NoOperandsInstruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader&) override {}
};

void BranchJump(JFrame& frame, int offset)
{
    auto thread = frame.Thread();
    auto nextpc = thread->Pc() + offset;

    thread->SetNextPc(nextpc);
}

class BranchInstruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader) override
    {
	offset = reader.Read<int>();
    }
    virtual void Execute(JFrame& frame) override
    {
	BranchJump(frame, offset);
    }

protected:
    int offset;
};

class Index8Instruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader) override
    {
	index = reader.Read<u2>();
    }

protected:
    u2 index;
};
}
#endif /* ifndef  */
