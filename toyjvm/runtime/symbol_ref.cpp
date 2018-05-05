//
// Created by cyhone on 18-4-22.
//

#include <toyjvm/runtime/symbol_ref.h>
#include <toyjvm/runtime/class_loader.h>
#include <toyjvm/runtime/jvm_member.h>

namespace jvm {
    JvmClass *SymbolRef::resolveClass()
    {
        if (!klass_) {
            klass_ = Loader::instance()->loadNonArrayClass(class_name_);
        }

        return klass_;
    }

    JvmField *FieldRef::resolveField()
    {
        if (!field_) {
            field_ = lookUpField(resolveClass());
        }

        return field_;
    }

    JvmField *FieldRef::lookUpField(JvmClass *klass)
    {
        for (auto field_item : klass->fields()) {
            if (field_item->name() == name_descriptor_[0]
                && field_item->descriptor() == name_descriptor_[1]) {
                return field_item;
            }
        }

        for (auto &interface : klass->interfaces()) {
            auto field_item = lookUpField(interface);
            if (field_item != nullptr) {
                return field_item;
            }
        }

        auto super_class = klass->superClass();
        if (super_class != nullptr) {
            return lookUpField(const_cast<JvmClass *>(super_class));
        }

        return nullptr;
    }
}