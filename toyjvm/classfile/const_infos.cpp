//
// Created by cyhone on 18-4-14.
//

#include <toyjvm/classfile/const_infos.h>
#include <toyjvm/utilities/modified_utf8.h>

namespace jvm {
    void ConstClassInfo::read(jvm::BaseReader &reader)
    {
        name_index_ = reader.read<u2>();
    }

    const std::string &ConstClassInfo::className()
    {
        if (class_name_.empty()) {
            class_name_ = const_pool_.stringAt(name_index_);
        }
        return class_name_;
    }

    void BaseMemberRefInfo::read(jvm::BaseReader &reader)
    {
        class_index_ = reader.read<u2>();
        name_and_type_index_ = reader.read<u2>();
    }

    std::array<std::string, 2> BaseMemberRefInfo::nameAndDescriptor() const
    {
        return const_pool_.constInfoAt<ConstNameAndTypeInfo>(name_and_type_index_)
                ->nameAndDescriptor();
    }

    std::string BaseMemberRefInfo::className() const
    {
        return const_pool_.classNameOf(class_index_);
    }

    void ConstStringInfo::read(jvm::BaseReader &reader)
    {
        string_index_ = reader.read<u2>();
    }

    std::string ConstStringInfo::val()
    {
        return const_pool_.stringAt(string_index_);
    }

    void ConstNameAndTypeInfo::read(jvm::BaseReader &reader)
    {
        name_index_ = reader.read<u2>();
        descriptor_index_ = reader.read<u2>();
    }

    std::array<std::string, 2> ConstNameAndTypeInfo::nameAndDescriptor() const
    {
        return {const_pool_.stringAt(name_index_), const_pool_.stringAt(descriptor_index_)};
    }

    void ConstUtf8Info::read(jvm::BaseReader &reader)
    {
        data_ = reader.batchRead<u2, u1>();
    }

    std::string ConstUtf8Info::asString()
    {
        return parseMutf8AsString(data_);
    }

    void ConstMethodHandleInfo::read(jvm::BaseReader &reader)
    {
        reference_kind_ = reader.read<u1>();
        reference_index_ = reader.read<u2>();
    }

    void ConstMethodTypeInfo::read(jvm::BaseReader &reader)
    {
        descriptor_index_ = reader.read<u2>();
    }

    void ConstInvokeDynamicInfo::read(jvm::BaseReader &reader)
    {
        boostrap_method_attr_index_ = reader.read<u2>();
        name_and_type_index_ = reader.read<u2>();
    }
}