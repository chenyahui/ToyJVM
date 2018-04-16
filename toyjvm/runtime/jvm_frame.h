//
// Created by cyhone on 18-4-16.
//

#ifndef TOYJVM_JVM_FRAME_H
#define TOYJVM_JVM_FRAME_H

#include <cstddef>
#include <toyjvm/runtime/local_slots.h>
#include <toyjvm/runtime/operand_stack.h>

namespace jvm {
    class JvmFrame {
    public:
        JvmFrame(size_t local_slot_size, size_t max_stack_num)
                : local_slots_(local_slot_size),
                  operand_stack_(max_stack_num)
        {}

        inline LocalSlots &localSlots()
        {
            return local_slots_;
        }

        inline OperandStack &operandStack()
        {
            return operand_stack_;
        }

    private:
        LocalSlots local_slots_;
        OperandStack operand_stack_;
    };
}
#endif //TOYJVM_JVM_FRAME_H
