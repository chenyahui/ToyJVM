//
// Created by cyhone on 18-4-16.
//

#ifndef TOYJVM_JVM_FRAME_H
#define TOYJVM_JVM_FRAME_H

#include <cstddef>
#include <toyjvm/runtime/local_slots.h>
#include <toyjvm/runtime/operand_stack.h>
#include <toyjvm/runtime/jvm_member.h>

namespace jvm {
    class JvmThread;

    class JvmFrame {
    public:
        JvmFrame(JvmThread &thread, size_t local_slot_size, size_t max_stack_num)
                : local_slots_(local_slot_size),
                  operand_stack_(max_stack_num),
                  thread_(thread)
        {}

        inline LocalSlots &localSlots()
        {
            return local_slots_;
        }

        inline OperandStack &operandStack()
        {
            return operand_stack_;
        }

        inline JvmMethod* method() const
        {
            return method_;
        }

        void jumpToBranch(int offset);

        void setNextPc(size_t next_pc)
        {
            next_pc_ = next_pc;
        }

        size_t nextPc() const
        {
            return next_pc_;
        }

    private:
        LocalSlots local_slots_;
        OperandStack operand_stack_;
        JvmMethod *method_;
        JvmThread &thread_;
        size_t next_pc_ = 0;
    };
}
#endif //TOYJVM_JVM_FRAME_H
