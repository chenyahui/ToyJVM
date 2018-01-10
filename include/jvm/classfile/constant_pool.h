#ifndef MY_JVM_CLASSFILE_CONSTANT_POOL_H
#define MY_JVM_CLASSFILE_CONSTANT_POOL_H

#include <jvm/classfile/classreader.h>
#include <jvm/utils/types.h>
#include <string>
namespace cyh {
enum ConstantType {
    Klass = 7,
    Fieldref = 9,
    Methodref = 10,
    InterfaceMethodref = 11,
    String = 8,
    Integer = 3,
    Float = 4,
    Long = 5,
    Double = 6,
    NameAndType = 12,
    Utf8 = 1,
    MethodHandle = 15,
    MethodType = 16,
    InvokeDynamic = 18
};

class ConstantInfo {
public:
    virtual ~ConstantInfo() {}
    virtual void ReadInfo(ClassReader&) {}
    inline void set_tag(u1 tag)
    {
	this->tag_ = tag;
    }
    inline u1 tag()
    {
	return tag_;
    }

private:
    u1 tag_;
};

class ConstantPool {
public:
    void Read(ClassReader&);

    ConstantInfo* operator[](int index);

    template <typename T>
    T Get(int index)
    {
	return dynamic_cast<T>(cpinfos_[index]);
    }
    // entry at the index must be a utf8_info
    std::string GetUtf8AsString(int index);

    // entry at the index must be a class_info
    std::string GetClassName(int index);

    ConstantInfo* ReadConstantInfo(u1 tag, ClassReader&);
    inline std::vector<ConstantInfo*>& cpinfos()
    {
	return cpinfos_;
    }

private:
    ConstantInfo* NewConstantInfo(u1 tag);
    std::vector<ConstantInfo*> cpinfos_;
};
}

#endif /* ifndef  */
