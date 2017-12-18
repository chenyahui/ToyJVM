#ifndef MY_JVM_CLASSFILE_CONSTANT_INFOS_H
#define MY_JVM_CLASSFILE_CONSTANT_INFOS_H

#include <jvm/classfile/constant_pool.h>

namespace cyh {
class ConstantKlassInfo : public ConstantInfo {
public:
    ConstantKlassInfo(ConstantPool* constant_pool)
	: constant_pool_(constant_pool)
    {
    }
    void ReadInfo(ClassReader&) override;
    std::string ClassName();

private:
    ConstantPool* constant_pool_;
    u2 name_index_; // is a index of constant pool,and the entry at the index is  Utf8 type
};

class ConstantMemberInfo : public ConstantInfo {
public:
    ConstantMemberInfo(ConstantPool* constant_pool)
	: constant_pool_(constant_pool)
    {
    }
    void ReadInfo(ClassReader&) override;

private:
    ConstantPool* constant_pool_;
    u2 class_index_;
    u2 name_and_type_index_;
};

using ConstantFieldRefInfo = ConstantMemberInfo;
using ConstantMethodRefInfo = ConstantMemberInfo;
using ConstantInterfaceMethodRefInfo = ConstantMemberInfo;

class ConstantStringInfo : public ConstantInfo {
public:
    ConstantStringInfo(ConstantPool* constant_pool)
	: constant_pool_(constant_pool)
    {
    }
    void ReadInfo(ClassReader&) override;

private:
    ConstantPool* constant_pool_;
    u2 string_index_; // index of utf8 type
};

class ConstantFloatInfo : public ConstantInfo {
public:
    void ReadInfo(ClassReader&) override;

private:
    float value;
};

class ConstantIntegerInfo : public ConstantInfo {
public:
    void ReadInfo(ClassReader&) override;

private:
    int value;
};
class ConstantDoubleInfo : public ConstantInfo {
public:
    void ReadInfo(ClassReader&) override;

private:
    double value;
};

class ConstantLongInfo : public ConstantInfo {
public:
    void ReadInfo(ClassReader&) override;

private:
    long value;
};
class ConstantNameAndTypeInfo : public ConstantInfo {
public:
    ConstantNameAndTypeInfo(ConstantPool* pool)
	: pool_(pool)
    {
    }
    void ReadInfo(ClassReader&) override;

private:
    ConstantPool* pool_;
    u2 name_index_;       // index of utf8 type
    u2 descriptor_index_; // index of utf8 type
};
class ConstantUtf8Info : public ConstantInfo {
public:
    ConstantUtf8Info()
	: cached_()
	, data_()
    {
    }
    void ReadInfo(ClassReader&) override;
    std::string AsString();

private:
    bytes data_;
    std::string cached_ = "";
};
class ConstantMethodHandleInfo : public ConstantInfo {
public:
    void ReadInfo(ClassReader&) override;

private:
    u1 reference_kind_;
    u2 reference_index_;
};
class ConstantMethodTypeInfo : public ConstantInfo {
public:
    void ReadInfo(ClassReader&) override;

private:
    u2 descriptor_index_;
};

class ConstantInvokeDynamicInfo : public ConstantInfo {
public:
    void ReadInfo(ClassReader&) override;

private:
    u2 boostrap_method_attr_index_;
    u2 name_and_type_index_;
};
}

#endif
