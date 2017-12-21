#ifndef MY_JVM_CLASSFILE_ATTRIBUTE_TABLE_H
#define MY_JVM_CLASSFILE_ATTRIBUTE_TABLE_H

#include <jvm/classfile/constant_pool.h>
#include <string>

namespace cyh {
class MemberInfo;

class AttributeInfo {
public:
    AttributeInfo(const char* attr_type)
	: attr_type_(attr_type){};
    virtual void ReadInfo(ClassReader&) = 0;
    virtual ~AttributeInfo() {}

    friend class MemberInfo;
protected:
    std::string attr_type_;
};

class AttributeTable {
public:
    void Read(ClassReader& reader, ConstantPool*);
    friend class MemberInfo;
private:
    AttributeInfo* ReadAttributeInfo(ClassReader&, ConstantPool*);
    AttributeInfo* NewAttributeInfo(std::string attrname, ConstantPool*);
    std::vector<AttributeInfo*> attributes_infos_;
};
}

#endif
