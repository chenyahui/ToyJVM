//
// Created by cyhone on 18-5-7.
//
#include <toyjvm/runtime/jvm_reference.h>
#include <toyjvm/runtime/jvm_member.h>

namespace jvm {
    void JvmObject::setRef(const std::string &name,
                           const std::string &descriptor,
                           jvm::jref ref_obj)
    {
        auto objclass = dynamic_cast<JvmClass *>(klass_);
        auto field = objclass->getField(name, descriptor, false);
        instance_fields_.set<jref>(field->slotIndex(), ref_obj);
    }

    jref JvmObject::getRef(const std::string &name, const std::string &descriptor)
    {
        auto objclass = dynamic_cast<JvmClass *>(klass_);
        auto field = objclass->getField(name, descriptor, false);
        return instance_fields_.at(field->slotIndex());
    }
}
