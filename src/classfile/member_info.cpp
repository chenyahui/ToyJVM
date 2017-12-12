#include <jvm/classfile/member_info.h>

namespace cyh{
	void MemberInfo::Read(ClassReader& reader){
		access_flags_ = reader.ReadU2();
		name_index_  = reader.ReadU2();
		descriptor_index_ = reader.ReadU2();

		attribute_table_.Read(reader,pool_);
	}

	std::string MemberInfo::MemberName(){
		return pool_->GetUtf8AsString(name_index_);
	}
}
