//
// Created by cyhone on 18-2-8.
//

#ifndef TOYJVM_MEMBER_INFO_H
#define TOYJVM_MEMBER_INFO_H

#include <toyjvm/common/jvm_types.h>

namespace jvm {
    class MemberInfo {
    private:
        u2 access_flags_;
        u2 name_index_;
        u2 descriptor_index_;
    };
}
#endif //TOYJVM_MEMBER_INFO_H
