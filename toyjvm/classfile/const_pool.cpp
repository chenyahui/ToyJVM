//
// Created by cyhone on 18-2-8.
//
#include <toyjvm/utilities/exception.h>
#include "toyjvm/classfile/const_pool.h"
#include "toyjvm/classfile/const_infos.h"
#include <glog/logging.h>

using namespace jvm;

void ConstPool::read()
{
    auto count = reader_.read<u2>();
    DLOG(INFO) << "const count : " << count;

    const_infos_.resize(count);

    for (auto i = 1; i < count; i++) {
        auto tag_value = reader_.read<u1>();
        auto tag = static_cast<ConstType>(tag_value);
        auto info = ConstInfoFactory(tag);
        info->read(reader_);
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

std::string ConstPool::stringAt(int index) const
{
    return constInfoAt<ConstUtf8Info>(index)->asString();
}

std::shared_ptr<BaseConstInfo> ConstPool::ConstInfoFactory(jvm::ConstType tag)
{
#define case_info(const_type) \
case ConstType::##const_type##: \
    return std::make_shared<Const##const_type##Info>(*this);


    switch (tag) {
        case_info(Class)
        case_info(FieldRef)
        case_info(MethodRef)
        case_info(InterfaceMethodRef)
        case_info(String)
        case_info(Integer)
        case_info(Float)
        case_info(Double)
        case_info(Long)
        case_info(NameAndType)
        case_info(Utf8)
        case_info(MethodHandle)
        case_info(MethodType)
        case_info(InvokeDynamic)
        default:
            throw JVMError("unsupported constant type");
    }
#undef case_info
}