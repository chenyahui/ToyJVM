//
// Created by cyhone on 18-5-6.
//

#ifndef TOYJVM_RETURN_INSTRUCTIONS_H
#define TOYJVM_RETURN_INSTRUCTIONS_H

#include <toyjvm/instruction/base_instruction.h>
#include <toyjvm/runtime/jvm_thread.h>

namespace jvm {
    class RETURN_Instruction : public BaseInstruction {
    public:
        void execute(JvmFrame &frame) override
        {
            frame.thread().pop();
        }
    };

    template<typename T>
    class BaseReturnInstruction : public BaseInstruction {
    public:
        void execute(JvmFrame &frame) override
        {
            auto jthread = frame.thread();
            auto current_frame = jthread.pop();
            auto invoker_frame = jthread.top();

            auto result = current_frame->operandStack().pop<T>();
            invoker_frame->operandStack().push<T>(result);
        }
    };

    using IRETURN_Instruction = BaseReturnInstruction<jint>;
    using DRETURN_Instruction = BaseReturnInstruction<jdouble>;
    using FRETURN_Instruction = BaseReturnInstruction<jfloat>;
    using LRETURN_Instruction = BaseReturnInstruction<jlong>;
    using ARETURN_Instruction = BaseReturnInstruction<jref>;
}
#endif //TOYJVM_RETURN_INSTRUCTIONS_H
