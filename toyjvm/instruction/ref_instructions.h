//
// Created by cyhone on 18-4-24.
//

#ifndef TOYJVM_REF_INSTRUCTIONS_H
#define TOYJVM_REF_INSTRUCTIONS_H

#include <toyjvm/instruction/base_instruction.h>
#include <toyjvm/runtime/jvm_reference.h>
#include <toyjvm/utilities/exception.h>

namespace jvm {
    class NEW_Instruction : public BaseOneOperandInstruction<u2> {
    public:
        void execute(JvmFrame &frame) override;
    };

    class BaseFieldInstruction : public BaseOneOperandInstruction<u2> {
    public:
        void execute(jvm::JvmFrame &frame) override;

    protected:
        template<typename T>
        virtual void realAction(size_t slot_id,
                                LocalSlots *static_slots,
                                OperandStack &opstack) = 0;
    };

    class PUTSTATIC_Instruction : public BaseFieldInstruction {
    private:
        template<typename T>
        void realAction(size_t slot_id,
                        LocalSlots *static_slots,
                        OperandStack &opstack) override
        {
            static_slots->set<T>(slot_id, opstack.pop<T>());
        }
    };

    class GETSTATIC_Instruction : public BaseFieldInstruction {
    private:
        template<typename T>
        void realAction(size_t slot_id,
                        LocalSlots *static_slots,
                        OperandStack &opstack) override
        {
            opstack.push<T>(static_slots->at<T>(slot_id));
        }
    };

    class PUTFIELD_Instruction : public BaseFieldInstruction {
    private:
    private:
        template<typename T>
        void realAction(size_t slot_id,
                        LocalSlots *,
                        OperandStack &opstack) override
        {
            auto val = opstack.pop<T>();
            auto obj = opstack.pop<jobj>();

            if (obj == nullptr) {
                throw JVMError("null pointer");
            }

            const_cast<LocalSlots &>(obj->instanceFields()).set<T>(slot_id, val);
        }
    };

    class GETFIELD_Instruction : public BaseFieldInstruction {
    private:
    private:
        template<typename T>
        void realAction(size_t slot_id,
                        LocalSlots *,
                        OperandStack &opstack) override
        {
            auto obj = opstack.pop<std::shared_ptr<JvmObject>>();

            if (obj == nullptr) {
                throw JVMError("null pointer");
            }

            opstack.push<T>(obj->instanceFields().at<T>(slot_id));
        }
    };

    class INSTANCEOF_Instruction : public BaseOneOperandInstruction<u2> {
    public:
        void execute(JvmFrame &frame) override;
    };

    class CHECKCAST_Instruction : public BaseOneOperandInstruction<u2> {
    public:
        void execute(JvmFrame &frame) override;
    };
}
#endif //TOYJVM_REF_INSTRUCTIONS_H
