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
    class BaseInstruction : boost::noncopyable {
    public:
        virtual void fetchOperands(ByteCodeReader &reader)
        {}

        virtual void execute(JvmFrame &frame)
        {}
    };
}
#endif //TOYJVM_BASE_INSTRUCTION_H
