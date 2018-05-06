//
// Created by cyhone on 18-4-19.
//

#include <toyjvm/runtime/jvm_member.h>
#include <toyjvm/utilities/method_descriptor.h>

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

        AttrCode *codeAttr = method_info->codeAttr();
        if (codeAttr != nullptr) {
            max_stack_ = codeAttr->maxStack();
            max_locals_ = codeAttr->maxLocals();
            code_ = std::move(codeAttr->moveCode());

            // 计算该方法所需的参数个数
            auto method_descriptor = parseMethodDescriptor(descriptor_);
            for (const auto &param_type : method_descriptor.param_types) {
                args_slot_count_++;
                if (param_type == "J" || param_type == "D") {
                    args_slot_count_++;
                }
            }
            if (!access_flags_.isStatic()) {
                args_slot_count_++;
            }
        }
    }
}