#ifndef MY_JVM_CLASSFILE_MEMBER_INFO_H
#define MY_JVM_CLASSFILE_MEMBER_INFO_H

#include <jvm/classfile/attribute_table.h>
#include <jvm/classfile/classreader.h>
#include <jvm/classfile/attribute_infos.h>

namespace cyh {

class MemberInfo {
public:
    MemberInfo(ConstantPool* pool)
	: pool_(pool)
    {
    }
    void Read(ClassReader& reader);
    std::string MemberName();
    AttributeCodeInfo* CodeAttribute();
private:
    u2 access_flags_;
    u2 name_index_;
    u2 descriptor_index_;
    AttributeTable attribute_table_;
    ConstantPool* pool_;
};
}
#endif
