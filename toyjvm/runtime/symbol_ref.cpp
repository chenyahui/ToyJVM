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

    JvmMethod *MethodRef::resolveMethod()
    {
        if (!method_) {
            auto klass = resolveClass();

            auto method = lookUpMethodInClass(klass, name_descriptor_[0], name_descriptor_[1]);
            if (method == nullptr) {
                method = lookUpMethodInInterfaces(klass->interfaces(), name_descriptor_[0], name_descriptor_[1]);
            }

            return method;
        }

        return method_;
    }

    JvmMethod *InterfaceMethodRef::resolveInterfaceMethod()
    {
        if (!method_) {
            auto iface = resolveClass();
            for (auto method : iface->methods()) {
                if (method->name() == name_descriptor_[0] && method->descriptor() == name_descriptor_[1]) {
                    method_ = method;
                    goto RET;
                }
            }
            method_ = lookUpMethodInInterfaces(iface->interfaces(), name_descriptor_[0], name_descriptor_[1]);
        }

        RET:
        return method_;
    }

    JvmMethod *lookUpMethodInClass(JvmClass *klass,
                                   const std::string &name,
                                   const std::string &descriptor)
    {
        for (auto c = klass; c != nullptr; c = c->superClass()) {
            for (auto method : c->methods()) {
                if (method->name() == name && method->descriptor() == descriptor) {
                    return method;
                }
            }
        }

        return nullptr;
    }

    JvmMethod *lookUpMethodInInterfaces(const std::vector<JvmClass *> &ifaces,
                                        const std::string &name,
                                        const std::string &descriptor)
    {
        for (auto iface : ifaces) {
            for (auto method : iface->methods()) {
                if (method->name() == name && method->descriptor() == descriptor) {
                    return method;
                }
            }

            auto method = lookUpMethodInInterfaces(iface->interfaces(), name, descriptor);
            if (method != nullptr) {
                return method;
            }
        }

        return nullptr;
    }
}