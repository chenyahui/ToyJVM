//
// Created by cyhone on 18-4-24.
//

#ifndef TOYJVM_REF_INSTRUCTIONS_H
#define TOYJVM_REF_INSTRUCTIONS_H

#include <toyjvm/instruction/base_instruction.h>
#include <toyjvm/runtime/jvm_reference.h>
#include <toyjvm/utilities/exception.h>
#include <toyjvm/utilities/jvm_types.h>
#include <toyjvm/runtime/symbol_ref.h>

namespace jvm {
    class NEW_Instruction : public BaseOneOperandInstruction<u2> {
    public:
        void execute(JvmFrame &frame) override;
    };

    class BaseFieldInstruction : public BaseOneOperandInstruction<u2> {
    protected:
        template<typename RealActor>
        void realAction(jvm::JvmFrame &frame)
        {
            const auto &rt_const_pool = frame.method()->klass()->runtimeConstPool();
            // 找到要赋值的字段
            auto &field_ref = rt_const_pool.at<std::shared_ptr<FieldRef>>(operand_);
            auto field = field_ref->resolveField();

            auto klass = field->klass();
            auto static_slots = klass->staticFields();
            auto slot_id = field->slotIndex();

            auto descriptor = field->descriptor();
            auto &opstack = frame.operandStack();
            switch (descriptor[0]) {
                case 'Z':
                case 'B':
                case 'C':
                case 'S':
                case 'I': {
                    RealActor::template handle<jint>(slot_id, static_slots, opstack);
                    break;
                }

                case 'F': {
                    RealActor::template handle<jfloat>(slot_id, static_slots, opstack);
                    break;
                }
                case 'J': {
                    RealActor::template handle<jlong>(slot_id, static_slots, opstack);
                    break;
                }
                case 'D': {
                    RealActor::template handle<jdouble>(slot_id, static_slots, opstack);
                    break;
                }
                case 'L':
                case '[': {
                    RealActor::template handle<jref>(slot_id, static_slots, opstack);
                    break;
                }
            }
        }

    };

    class PUTSTATIC_Instruction : public BaseFieldInstruction {
    private:
        class RealAction {
        public:
            template<typename T>
            static void handle(size_t slot_id,
                           LocalSlots *static_slots,
                           OperandStack &opstack)
            {
                static_slots->set<T>(slot_id, opstack.pop<T>());
            }
        };

    public:
        void execute(JvmFrame &frame) override
        {
            realAction<PUTSTATIC_Instruction::RealAction>(frame);
        }
    };

    class GETSTATIC_Instruction : public BaseFieldInstruction {
    private:
        class RealAction {
        public:
            template<typename T>
            static void handle(size_t slot_id,
                           LocalSlots *static_slots,
                           OperandStack &opstack)
            {
                opstack.push<T>(static_slots->at<T>(slot_id));
            }
        };

    public:
        void execute(JvmFrame &frame) override
        {
            realAction<GETSTATIC_Instruction::RealAction>(frame);
        }
    };

    class PUTFIELD_Instruction : public BaseFieldInstruction {
    private:
        class RealAction {
        public:
            template<typename T>
            static void handle(size_t slot_id,
                           LocalSlots *static_slots,
                           OperandStack &opstack)
            {
                auto val = opstack.pop<T>();
                auto obj = opstack.pop<jobj>();

                if (obj == nullptr) {
                    throw JVMError("null pointer");
                }

                const_cast<LocalSlots &>(obj->instanceFields()).set<T>(slot_id, val);
            }
        };
    public:
        void execute(JvmFrame &frame) override
        {
            realAction<PUTFIELD_Instruction::RealAction>(frame);
        }
    };

    class GETFIELD_Instruction : public BaseFieldInstruction {
    public:
        void execute(JvmFrame &frame) override
        {
            realAction<GETFIELD_Instruction::RealAction>(frame);
        }
    private:
        class RealAction {
        public:
            template<typename T>
            static void handle(size_t slot_id,
                           LocalSlots *static_slots,
                           OperandStack &opstack)
            {
                auto obj = opstack.pop<std::shared_ptr<JvmObject>>();

                if (obj == nullptr) {
                    throw JVMError("null pointer");
                }

                opstack.push<T>(obj->instanceFields().at<T>(slot_id));
            }
        };
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
