//
// Created by cyhone on 18-4-15.
//
#include <toyjvm/classfile/member_info.h>

namespace jvm {
    void MemberInfo::read(jvm::BaseReader &reader)
    {
        access_flags_ = reader.read<u2>();
        name_index_ = reader.read<u2>();
        descriptor_index_ = reader.read<u2>();
        attr_table_.read(reader, const_pool_);
    }

    std::string MemberInfo::memberName()
    {
        return const_pool_.stringAt(name_index_);
    }

}