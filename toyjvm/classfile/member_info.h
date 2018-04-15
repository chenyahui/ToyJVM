//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_MEMBER_INFO_H
#define TOYJVM_MEMBER_INFO_H

#include <toyjvm/common/jvm_types.h>
#include <toyjvm/classfile/attribute_table.h>

namespace jvm {
    class MemberInfo {
    public:
        explicit MemberInfo(const ConstPool &const_pool)
                : const_pool_(const_pool)
        {}

        void read(BaseReader &reader);

        std::string memberName();

    private:
        const ConstPool &const_pool_;

        u2 access_flags_;
        u2 name_index_;
        u2 descriptor_index_;
        AttrTable attr_table_;
    };
}
#endif //TOYJVM_MEMBER_INFO_H
