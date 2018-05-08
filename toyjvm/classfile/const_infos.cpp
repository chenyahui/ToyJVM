//
// Created by cyhone on 18-4-14.
//

#include <toyjvm/classfile/const_infos.h>

namespace jvm {
    void ConstClassInfo::read(jvm::ByteReader &reader)
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

    void BaseMemberRefInfo::read(jvm::ByteReader &reader)
    {
        class_index_ = reader.read<u2>();
        name_and_type_index_ = reader.read<u2>();
    }

    std::array<std::string, 2> BaseMemberRefInfo::nameAndDescriptor() const
    {
        return const_pool_.constInfoAt<ConstNameAndTypeInfo>(name_and_type_index_)
                ->nameAndDescriptor();
    };

    std::string BaseMemberRefInfo::className() const
    {
        return const_pool_.classNameOf(class_index_);
    }

    void ConstStringInfo::read(jvm::ByteReader &reader)
    {
        string_index_ = reader.read<u2>();
    }

    ModifiedUTF8 &ConstStringInfo::val() const
    {
        return const_pool_.utf8At(string_index_);
    }

    void ConstNameAndTypeInfo::read(jvm::ByteReader &reader)
    {
        name_index_ = reader.read<u2>();
        descriptor_index_ = reader.read<u2>();
    }

    std::array<std::string, 2> ConstNameAndTypeInfo::nameAndDescriptor() const
    {
        return {const_pool_.stringAt(name_index_), const_pool_.stringAt(descriptor_index_)};
    }

    void ConstUtf8Info::read(jvm::ByteReader &reader)
    {
        utf8_ = std::move(reader.batchRead<u2, u1>());
    }

    std::string ConstUtf8Info::asString()
    {
        return utf8_.asString();
    }

    ModifiedUTF8 &ConstUtf8Info::val()
    {
        return utf8_;
    }

    void ConstMethodHandleInfo::read(jvm::ByteReader &reader)
    {
        reference_kind_ = reader.read<u1>();
        reference_index_ = reader.read<u2>();
    }

    void ConstMethodTypeInfo::read(jvm::ByteReader &reader)
    {
        descriptor_index_ = reader.read<u2>();
    }

    void ConstInvokeDynamicInfo::read(jvm::ByteReader &reader)
    {
        boostrap_method_attr_index_ = reader.read<u2>();
        name_and_type_index_ = reader.read<u2>();
    }
}