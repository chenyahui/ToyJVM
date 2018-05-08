//
// Created by cyhone on 18-2-8.
//
#include <toyjvm/utilities/exception.h>
#include "toyjvm/classfile/const_pool.h"
#include "toyjvm/classfile/const_infos.h"
#include <glog/logging.h>

using namespace jvm;

ConstPool::~ConstPool()
{
    for (auto info : const_infos_) {
        delete info;
    }
}

void ConstPool::read(ByteReader &reader)
{
    auto count = reader.read<u2>();
    DLOG(INFO) << "const count : " << count;

    const_infos_.resize(count);

    for (auto i = 1; i < count; i++) {
        auto tag_value = reader.read<u1>();
        auto tag = static_cast<ConstType>(tag_value);
        auto info = constInfoFactory(tag);
        info->read(reader);
        const_infos_[i] = info;

        if (tag == ConstType::Long || tag == ConstType::Double) {
            i++;
        }
    }
}

std::string ConstPool::classNameOf(jvm::u2 class_index) const
{
    return constInfoAt<ConstClassInfo>(class_index)->className();
}

ModifiedUTF8 &ConstPool::utf8At(int utf8_index) const
{
    return constInfoAt<ConstUtf8Info>(utf8_index)->val();
}

std::string ConstPool::stringAt(int utf8_index) const
{
    return constInfoAt<ConstUtf8Info>(utf8_index)->asString();
}

BaseConstInfo *ConstPool::constInfoFactory(jvm::ConstType tag)
{
    switch (tag) {
        case ConstType::Class: {
            return new ConstClassInfo(tag, *this);
        }
        case ConstType::FieldRef: {
            return new ConstFieldRefInfo(tag, *this);
        }
        case ConstType::MethodRef: {
            return new ConstMethodRefInfo(tag, *this);
        }
        case ConstType::InterfaceMethodRef: {
            return new ConstInterfaceMethodRefInfo(tag, *this);
        }
        case ConstType::String: {
            return new ConstStringInfo(tag, *this);
        }
        case ConstType::Integer: {
            return new ConstIntegerInfo(tag, *this);
        }
        case ConstType::Float: {
            return new ConstFloatInfo(tag, *this);
        }
        case ConstType::Double: {
            return new ConstDoubleInfo(tag, *this);
        }
        case ConstType::Long: {
            return new ConstLongInfo(tag, *this);
        }
        case ConstType::NameAndType: {
            return new ConstNameAndTypeInfo(tag, *this);
        }
        case ConstType::Utf8: {
            return new ConstUtf8Info(tag, *this);
        }
        case ConstType::MethodHandle: {
            return new ConstMethodHandleInfo(tag, *this);
        }
        case ConstType::MethodType: {
            return new ConstMethodTypeInfo(tag, *this);
        }

        case ConstType::InvokeDynamic: {
            return new ConstInvokeDynamicInfo(tag, *this);
        }
        default:
            throw JVMError("unsupported constant type");
    }
#undef case_info
}