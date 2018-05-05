//
// Created by cyhone on 18-4-19.
//

#ifndef TOYJVM_JVM_MEMBER_H
#define TOYJVM_JVM_MEMBER_H

#include <toyjvm/utilities/access_flags.h>
#include <string>
#include <toyjvm/classfile/member_info.h>
#include <toyjvm/runtime/jvm_class.h>

namespace jvm {
    class JvmMember : boost::noncopyable{
    public:
        explicit JvmMember(JvmClass* this_class, MemberInfo *member_info)
                : access_flags_(member_info->access_flags_),
                  name_(member_info->memberName()),
                  descriptor_(member_info->descriptor()),
                  this_class_(this_class)
        {}

        const AccessFlags &accessFlags() const
        {
            return access_flags_;
        }

        const std::string &descriptor() const
        {
            return descriptor_;
        }

        const std::string &name() const
        {
            return name_;
        }

        JvmClass* klass() const
        {
            return this_class_;
        }

    protected:
        AccessFlags access_flags_;
        std::string name_;
        std::string descriptor_;
        JvmClass* this_class_;
    };

    class JvmField : public JvmMember {
    public:
        explicit JvmField(JvmClass* this_class, FieldInfo *field_info);

        void setSlotIndex(size_t slot_index)
        {
            slot_index_ = slot_index;
        }

        bool isLongOrDouble() const
        {
            return descriptor_ == "J" || descriptor_ == "D";
        }

        int constValueIndex() const
        {
            return const_value_index_;
        }

        size_t slotIndex() const
        {
            return slot_index_;
        }

    private:
        size_t slot_index_;
        int const_value_index_;
    };

    class JvmMethod : public JvmMember {
    public:
        explicit JvmMethod(JvmClass* this_class, MethodInfo *method_info);

    private:
        u4 max_stack_ = 0;
        u4 max_locals_ = 0;
        bytes code_;
    };
}
#endif //TOYJVM_JVM_MEMBER_H
