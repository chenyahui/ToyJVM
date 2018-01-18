#include <cassert>
#include <cstring>

#include <jvm/classfile/constant_infos.h>
#include <jvm/classfile/constant_pool.h>
#include <jvm/utils/logutils.h>
#include <string>
#include <typeinfo>
#include <glog/logging.h>

namespace cyh {
void ConstantPool::Read(ClassReader& reader)
{
    u2 count = reader.ReadU2();
    cpinfos_.resize(count);

    for (int i = 1; i < count; ++i) {
	auto tag = reader.ReadU1();

	cpinfos_[i] = ReadConstantInfo(tag, reader);
	cpinfos_[i]->set_tag(tag);
	// according the jvms
	if (tag == Long || tag == Double) {
	    ++i;
	}
    }
}

std::string ConstantPool::GetClassName(int index)
{
    assert(index > 0 & index < cpinfos_.size());
    auto class_info = dynamic_cast<ConstantKlassInfo*>(cpinfos_[index]);

    assert(class_info != NULL);
    return class_info->ClassName();
}

// index start from 1
ConstantInfo* ConstantPool::operator[](int index)
{
    return cpinfos_[index];
}

ConstantInfo* ConstantPool::ReadConstantInfo(u1 tag, ClassReader& reader)
{
    //auto tag = reader.ReadU1();

    // 根据tag类型分发
    ConstantInfo* constant_info = NewConstantInfo(tag);

    // 读取该constant_info的内容
    constant_info->ReadInfo(reader);

    return constant_info;
}

std::string ConstantPool::GetUtf8AsString(int index)
{
    assert(index >= 1 && index < cpinfos_.size());

    auto info = dynamic_cast<ConstantUtf8Info*>(cpinfos_[index]);
    if (info == NULL) {
	throw "dynamic_cast failed !!!";
    }
    return info->AsString();
}
ConstantInfo* ConstantPool::NewConstantInfo(u1 tag)
{
    switch (tag) {
    case Klass:
	return new ConstantKlassInfo(this);
    case Fieldref:
	return new ConstantFieldRefInfo(this);
    case Methodref:
	return new ConstantMethodRefInfo(this);
    case InterfaceMethodref:
	return new ConstantInterfaceMethodRefInfo(this);
    case String:
	return new ConstantStringInfo(this);
    case Integer:
	return new ConstantIntegerInfo();
    case Float:
	return new ConstantFloatInfo();
    case Double:
	return new ConstantDoubleInfo();
    case Long:
	return new ConstantLongInfo();
    case NameAndType:
	return new ConstantNameAndTypeInfo(this);
    case Utf8:
	return new ConstantUtf8Info();
    case MethodHandle:
	return new ConstantMethodHandleInfo();
    case MethodType:
	return new ConstantMethodTypeInfo();
    case InvokeDynamic:
	return new ConstantInvokeDynamicInfo();
    default:
	throw std::string("unknown constant info tag!") + std::to_string(tag);
    }
}
}
