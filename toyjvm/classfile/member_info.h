//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_MEMBER_INFO_H
#define TOYJVM_MEMBER_INFO_H

#include <toyjvm/utilities/jvm_types.h>
#include <toyjvm/classfile/attribute_table.h>

namespace jvm {
    class JvmMember;

    class MemberInfo : boost::noncopyable {
        friend class JvmMember;

    public:
        explicit MemberInfo(const ConstPool &const_pool)
                : const_pool_(const_pool)
        {}

        void read(BaseReader &reader);

        std::string memberName();

        std::string descriptor();

    protected:
        const ConstPool &const_pool_;

        u2 access_flags_;
        u2 name_index_;
        u2 descriptor_index_;
        AttrTable attr_table_;
    };

    class AttrConstantValue;

    class FieldInfo : public MemberInfo {
    public:
        explicit FieldInfo(const ConstPool &const_pool)
                : MemberInfo(const_pool)
        {}

        AttrConstantValue *constantValueAttr() const;

    };

    class AttrCode;

    class MethodInfo : public MemberInfo {
    public:
        explicit MethodInfo(const ConstPool &const_pool)
                : MemberInfo(const_pool)
        {}

        AttrCode *codeAttr() const;
    };
}
#endif //TOYJVM_MEMBER_INFO_H
