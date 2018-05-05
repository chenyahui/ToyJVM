//
// Created by cyhone on 18-4-19.
//

#include <toyjvm/runtime/jvm_member.h>

namespace jvm {
    JvmField::JvmField(JvmClass *this_class, FieldInfo *field_info)
            : JvmMember(this_class, field_info)
    {
        auto constValueAttr = field_info->constantValueAttr();
        const_value_index_ = constValueAttr != nullptr ? constValueAttr->constValueIndex() : -1;
    }

    JvmMethod::JvmMethod(JvmClass *this_class, MethodInfo *method_info)
            : JvmMember(this_class, method_info)
    {
        AttrCode *codeAttr;
        if ((codeAttr = method_info->codeAttr()) != nullptr) {
            max_stack_ = codeAttr->maxStack();
            max_locals_ = codeAttr->maxLocals();
            code_ = std::move(codeAttr->moveCode());
        }
    }
}