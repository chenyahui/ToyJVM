//
// Created by cyhone on 18-2-8.
//
#include <toyjvm/common/exception.h>
#include "toyjvm/classfile/const_pool.h"
#include "toyjvm/classfile/const_infos.h"

using namespace jvm;

void ConstPool::read()
{
    auto count = reader_.read<u2>();
    const_infos_.resize(count);

    for (auto i = 1; i < count; i++) {
        auto tag = static_cast<ConstType>(reader_.read<u1>());
        auto info = ConstInfoFactory(tag);
        info->read(reader_);
        const_infos_[i] = info;

        if (tag == ConstType::Long || tag == ConstType::Double) {
            i++;
        }
    }
}

std::string ConstPool::string_at(int index)
{

}
BaseConstInfo *ConstPool::ConstInfoFactory(jvm::ConstPool::ConstType tag)
{
    switch (tag) {
        case ConstPool::ConstPool::Class:
            return new ConstClassInfo(this);
        case ConstPool::FieldRef:
            return new ConstFieldRefInfo(this);
        case ConstPool::MethodRef:
            return new ConstMethodRefInfo(this);
        case ConstPool::InterfaceMethodRef:
            return new ConstInterfaceMethodRefInfo(this);
        case ConstPool::String:
            return new ConstStringInfo(this);
        case ConstPool::Integer:
            return new ConstIntegerInfo(this);
        case ConstPool::Float:
            return new ConstFloatInfo(this);
        case ConstPool::Double:
            return new ConstDoubleInfo(this);
        case ConstPool::Long:
            return new ConstLongInfo(this);
        case ConstPool::NameAndType:
            return new ConstNameAndTypeInfo(this);
        case ConstPool::Utf8:
            return new ConstUtf8Info(this);
        case ConstPool::MethodHandle:
            return new ConstMethodHandleInfo(this);
        case ConstPool::MethodType:
            return new ConstMethodTypeInfo(this);
        case ConstPool::InvokeDynamic:
            return new ConstInvokeDynamicInfo(this);
        default:
            throw JVMError("unsupported constant type");
    }
}