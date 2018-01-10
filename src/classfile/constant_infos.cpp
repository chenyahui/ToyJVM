#include <jvm/classfile/constant_infos.h>
#include <jvm/utils/bitutils.h>
#include <jvm/utils/logutils.h>
#include <jvm/utils/utf8utils.h>

namespace cyh {

void ConstantKlassInfo::ReadInfo(ClassReader& reader)
{
    name_index_ = reader.ReadU2();
}

std::string ConstantKlassInfo::ClassName()
{
    return constant_pool_->GetUtf8AsString(name_index_);
}
void ConstantMemberRefInfo::ReadInfo(ClassReader& reader)
{
    class_index_ = reader.ReadU2();
    name_and_type_index_ = reader.ReadU2();
}
std::string ConstantMemberRefInfo::ClassName()
{
    return constant_pool_->GetUtf8AsString(class_index_);
}
std::pair<std::string, std::string> ConstantMemberRefInfo::NameAndDescriptor()
{
    auto name_type_info = constant_pool_->Get<ConstantNameAndTypeInfo*>(name_and_type_index_);

    auto name = constant_pool_->GetUtf8AsString(name_type_info->name_index());
    auto descriptor = constant_pool_->GetUtf8AsString(name_type_info->descriptor_index());

    return std::make_pair(name, descriptor);
}
void ConstantStringInfo::ReadInfo(ClassReader& reader)
{
    string_index_ = reader.ReadU2();
}
void ConstantFloatInfo::ReadInfo(ClassReader& reader)
{
    value = ConvertU4ToFloat(reader.ReadU4());
}

void ConstantIntegerInfo::ReadInfo(ClassReader& reader)
{
    value = reader.ReadU4();
}
void ConstantLongInfo::ReadInfo(ClassReader& reader)
{
    value = ConvertU8ToLong(reader.ReadU8());
}

void ConstantDoubleInfo::ReadInfo(ClassReader& reader)
{
    value = ConvertU8ToDouble(reader.ReadU8());
}
void ConstantNameAndTypeInfo::ReadInfo(ClassReader& reader)
{
    name_index_ = reader.ReadU2();
    descriptor_index_ = reader.ReadU2();
}

void ConstantUtf8Info::ReadInfo(ClassReader& reader)
{
    data_ = reader.ReadU1s();
}

std::string ConstantUtf8Info::AsString()
{
    if (cached_.empty()) {
	cached_ = MUtf8ToString(data_);
    }
    return cached_;
}

void ConstantMethodTypeInfo::ReadInfo(ClassReader& reader)
{
    descriptor_index_ = reader.ReadU2();
}

void ConstantMethodHandleInfo::ReadInfo(ClassReader& reader)
{
    reference_kind_ = reader.ReadU1();
    reference_index_ = reader.ReadU2();
}
void ConstantInvokeDynamicInfo::ReadInfo(ClassReader& reader)
{
    boostrap_method_attr_index_ = reader.ReadU2();
    name_and_type_index_ = reader.ReadU2();
}
}
