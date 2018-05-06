//
// Created by cyhone on 18-4-29.
//

#ifndef TOYJVM_INVOKE_INSTRUCTIONS_H
#define TOYJVM_INVOKE_INSTRUCTIONS_H

#include <toyjvm/instruction/base_instruction.h>
#include <toyjvm/runtime/symbol_ref.h>

namespace jvm {
    class BaseInvokeInstruction : public BaseOneOperandInstruction<u2> {
    protected:
        void invokeMethod(JvmFrame& invoker, JvmMethod* method);
    };

    class INVOKESTATIC_Instruction : public BaseInvokeInstruction {
    public:
        void execute(JvmFrame &frame) override
        {
            auto &const_pool = frame.method()->klass()->runtimeConstPool();
            auto method_ref = const_pool.at<MethodRef *>(operand_);

        }
    };

}
#endif //TOYJVM_INVOKE_INSTRUCTIONS_H
