//
// Created by cyhone on 18-4-29.
//

#ifndef TOYJVM_INVOKE_INSTRUCTIONS_H
#define TOYJVM_INVOKE_INSTRUCTIONS_H

#include <toyjvm/instruction/base_instruction.h>
#include <toyjvm/runtime/symbol_ref.h>

namespace jvm {
    template<bool skip2Byte>
    class BaseInvokeInstruction : public BaseInstruction {
    public:
        virtual void fetchOperands(ByteCodeReader &reader)
        {
            index_ = static_cast<int>(reader.read<u2>());

            if (skip2Byte) {
                reader.read<u2>();
            }
        }

        void execute(JvmFrame &frame) override;

    protected:
        virtual JvmMethod *findMethodToInvoked(JvmFrame &frame) = 0;

    private:
        void invokeMethod(JvmFrame &invoker, JvmMethod *method);

    protected:
        MethodRef *method_ref_;
        JvmMethod *resolved_method_;
        JvmClass *current_class_;
        JvmClass *resolved_class_;

        int index_;
    };

    class INVOKESTATIC_Instruction : public BaseInvokeInstruction<false> {
    private:
        JvmMethod *findMethodToInvoked(JvmFrame &frame) override;
    };

    class INVOKESPECIAL_Instruction : public BaseInvokeInstruction<false> {
    private:
        JvmMethod *findMethodToInvoked(JvmFrame &frame) override;
    };

    class INVOKEVIRTUAL_Instruction : public BaseInvokeInstruction<false> {
    private:
        JvmMethod *findMethodToInvoked(JvmFrame &frame) override;
    };

    class INVOKEINTERFACE_Instruction : public BaseInvokeInstruction<true> {
    private:
        JvmMethod *findMethodToInvoked(JvmFrame &frame) override;
    };

    class INVOKENATIVE_Instruction : public BaseInstruction {
    public:
        void execute(JvmFrame &frame) override;
    };

}
#endif //TOYJVM_INVOKE_INSTRUCTIONS_H
