#ifndef MY_JVM_CLASSFILE_CONSTANT_INFOS_H
#define MY_JVM_CLASSFILE_CONSTANT_INFOS_H

#include <jvm/classfile/constant_pool.h>
#include <utility>
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

class ConstantMemberRefInfo : public ConstantInfo {
public:
    ConstantMemberRefInfo(ConstantPool* constant_pool)
	: constant_pool_(constant_pool)
    {
    }
    void ReadInfo(ClassReader&) override;
    std::string ClassName();
    std::pair<std::string, std::string> NameAndDescriptor();

private:
    ConstantPool* constant_pool_;
    u2 class_index_;
    u2 name_and_type_index_;
};

using ConstantFieldRefInfo = ConstantMemberRefInfo;
using ConstantMethodRefInfo = ConstantMemberRefInfo;
using ConstantInterfaceMethodRefInfo = ConstantMemberRefInfo;

class ConstantStringInfo : public ConstantInfo {
public:
    ConstantStringInfo(ConstantPool* constant_pool)
	: constant_pool_(constant_pool)
    {
    }
    void ReadInfo(ClassReader&) override;

    inline std::string val()
    {
	return constant_pool_->GetUtf8AsString(string_index_);
    }

private:
    ConstantPool* constant_pool_;
    u2 string_index_; // index of utf8 type
};

class ConstantFloatInfo : public ConstantInfo {
public:
    void ReadInfo(ClassReader&) override;
    inline float val()
    {
	return value;
    }

private:
    float value;
};

class ConstantIntegerInfo : public ConstantInfo {
public:
    void ReadInfo(ClassReader&) override;
    inline int val()
    {
	return value;
    }

private:
    int value;
};
class ConstantDoubleInfo : public ConstantInfo {
public:
    void ReadInfo(ClassReader&) override;
    inline double val()
    {
	return value;
    }

private:
    double value;
};

class ConstantLongInfo : public ConstantInfo {
public:
    void ReadInfo(ClassReader&) override;
    inline long val()
    {
	return value;
    }

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

    inline u2 name_index()
    {
	return name_index_;
    }
    inline u2 descriptor_index()
    {
	return descriptor_index_;
    }

private:
    ConstantPool* pool_;
    u2 name_index_;       // index of utf8 type
    u2 descriptor_index_; // index of utf8 type
};
class ConstantUtf8Info : public ConstantInfo {
public:
    ConstantUtf8Info()
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
