//
// Created by cyhone on 18-4-22.
//

#include <toyjvm/runtime/symbol_ref.h>
#include <toyjvm/runtime/class_loader.h>
#include <toyjvm/utilities/exception.h>
#include <toyjvm/runtime/jvm_member.h>

namespace jvm {
    std::shared_ptr<JvmClass> SymbolRef::resolveClass()
    {
        if (!klass_) {
            klass_ = Loader::instance()->loadClass(class_name_);
        }

        return klass_;
    }

    std::shared_ptr<JvmField> FieldRef::resolveField()
    {
        if (!field_) {
            field_ = lookUpField(resolveClass().get());
        }

        return field_;
    }

    std::shared_ptr<JvmField> FieldRef::lookUpField(JvmClass *klass)
    {
        for (auto &field_item : klass->fields()) {
            if (field_item->name() == name_descriptor_[0]
                && field_item->descriptor() == name_descriptor_[1]) {
                return field_item;
            }
        }

        for (auto &interface : klass->interfaces()) {
            auto field_item = lookUpField(interface.get());
            if (field_item != nullptr) {
                return field_item;
            }
        }

        auto super_class = klass->superClass();
        if (super_class != nullptr) {
            return lookUpField(super_class.get());
        }

        return nullptr;
    }
}