//
// Created by cyhone on 18-1-30.
//

#ifndef TOYJVM_CLASSFILE_H
#define TOYJVM_CLASSFILE_H

#include <toyjvm/classfile/const_pool.h>
#include <toyjvm/classfile/member_info.h>
#include <toyjvm/classfile/attribute_table.h>
#include <toyjvm/common/jvm_types.h>

#include <boost/noncopyable.hpp>
#include <vector>

namespace jvm {
    class ClassFile : boost::noncopyable {
    public:
        explicit ClassFile(bytes data)
                : reader_(data),
                  const_pool_(reader_)
        {}

        void Parse();

    private:
        void checkMagicAndVersions();

        std::vector<MemberInfo> readMembers();

    private:
        BaseReader reader_;

        ConstPool const_pool_;
        u2 access_flags_;
        u2 this_class_;
        u2 super_class_;
        std::vector<MemberInfo> fields_;
        std::vector<MemberInfo> methods_;
        std::vector<u2> interfaces_;
        AttrTable attr_table_;
    };
}


#endif //NEWJVM_CLASSFILE_H
