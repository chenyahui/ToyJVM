//
// Created by cyhone on 18-4-17.
//

#ifndef TOYJVM_BASE_INSTRUCTION_H
#define TOYJVM_BASE_INSTRUCTION_H

#include <boost/core/noncopyable.hpp>
#include <toyjvm/instruction/bytecode_reader.h>
#include <toyjvm/runtime/jvm_frame.h>
#include <tuple>
#include <set>

namespace jvm {
    void branchJump(JvmFrame &frame, int offset);

    class BaseInstruction : boost::noncopyable {
    public:
        virtual void fetchOperands(ByteCodeReader &reader)
        {}

        virtual void execute(JvmFrame &frame)
        {}
    };

    template<typename T>
    class BaseOneOperandInstruction : public BaseInstruction {
    public:
        virtual void fetchOperands(ByteCodeReader &reader)
        {
            operand_ = static_cast<int>(reader.read<T>());
        }

    protected:
        int operand_;
    };

    template<typename T, int INDEX>
    class BaseLoadStoreInstruction : public BaseInstruction {
    public:
        virtual void fetchOperands(ByteCodeReader &reader) override
        {
            if (INDEX < 0) {
                index_ = static_cast<int>(reader.read<T>());
            }
        }

        virtual void execute(JvmFrame &frame) override = 0;

    protected:
        int index_ = INDEX;
    };
}
#endif //TOYJVM_BASE_INSTRUCTION_H
