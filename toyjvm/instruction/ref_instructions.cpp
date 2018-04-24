//
// Created by cyhone on 18-4-24.
//

#include <toyjvm/instruction/ref_instructions.h>
#include <toyjvm/runtime/symbol_ref.h>

namespace jvm {
    void NEW_Instruction::execute(jvm::JvmFrame &frame)
    {
        const auto &rt_const_pool = frame.method()->klass()->runtimeConstPool();
        auto &class_ref = rt_const_pool.at<std::shared_ptr<ClassRef>>(operand_);
        auto klass = class_ref->resolveClass();
        auto obj = std::make_shared<JvmObject>(klass);
        frame.operandStack().push(obj);
    }

    void BaseFieldInstruction::execute(jvm::JvmFrame &frame)
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
                realAction<jint>(slot_id, static_slots, opstack);
                break;
            }

            case 'F': {
                realAction<jfloat>(slot_id, static_slots, opstack);
                break;
            }
            case 'J': {
                realAction<jlong>(slot_id, static_slots, opstack);
                break;
            }
            case 'D': {
                realAction<jdouble>(slot_id, static_slots, opstack);
                break;
            }
            case 'L':
            case '[': {
                realAction<jref>(slot_id, static_slots, opstack);
                break;
            }
        }
    }
}