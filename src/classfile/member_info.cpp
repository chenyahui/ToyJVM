#include <glog/logging.h>
#include <jvm/classfile/member_info.h>

namespace cyh {
void MemberInfo::Read(ClassReader& reader)
{
    access_flags_ = reader.ReadU2();
    name_index_ = reader.ReadU2();
    descriptor_index_ = reader.ReadU2();

    attribute_table_.Read(reader, pool_);
}

std::string MemberInfo::MemberName()
{
    return pool_->GetUtf8AsString(name_index_);
}

AttributeCodeInfo* MemberInfo::CodeAttribute()
{
    for (AttributeInfo* attr_info : attribute_table_.attributes_infos_) {
	if (attr_info->attr_type_ == "Code")
	    return dynamic_cast<AttributeCodeInfo*>(attr_info);
    }

    // throw "can not find Code attribute";
    return NULL;
}

AttributeConstantValueInfo* MemberInfo::ConstantValueAttribute()
{
    for (AttributeInfo* attr_info : attribute_table_.attributes_infos_) {
	if (attr_info->attr_type_ == "ConstantValue")
	    return dynamic_cast<AttributeConstantValueInfo*>(attr_info);
    }

    DLOG(INFO) << "找不到 constant value attr";
    return NULL;
}
}
