#ifndef MY_JVM_INSTRUCTION_INSTRCUTION_H
#define MY_JVM_INSTRUCTION_INSTRCUTION_H

#include <jvm/instruction/bytecodereader.h>
#include <jvm/rtdata/jvm_thread.h>

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

class BranchInstruction : public Instruction {
public:
    void FetchOperands(ByteCodeReader& reader) override
    {
	offset = reader.Read<int>();
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
