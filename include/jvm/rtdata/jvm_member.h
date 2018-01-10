#ifndef MY_JVM_RTDATA_JVM_MEMBER_H
#define MY_JVM_RTDATA_JVM_MEMBER_H

#include <jvm/classfile/attribute_infos.h>
#include <jvm/classfile/constant_infos.h>
#include <jvm/classfile/member_info.h>

#include <jvm/rtdata/jvm_class.h>
#include <string>
#include <vector>
namespace cyh {

class JMember {
public:
    JMember(JClass* jclass, MemberInfo* member_info);
    inline std::string& descriptor()
    {
	return descriptor_;
    }
    inline std::string& name()
    {
	return name_;
    }
    JClass* jclass()
    {
	return jclass_;
    }
    bool IsAccessibleTo(JClass* other);
    bool IsPublic();
    bool IsPrivate();
    bool IsProtected();

protected:
    u2 access_flags_;
    std::string name_;
    std::string descriptor_;
    JClass* jclass_;
};

class JField : public JMember {
public:
    JField(JClass* jclass, MemberInfo* field_info);
    bool IsStatic();
    bool IsLongOrDouble();
    bool IsFinal();

    //getter settter
    inline void set_slot_index(u4 slot_index)
    {
	slot_index_ = slot_index;
    }
    inline u4 slot_index()
    {
	return slot_index_;
    }
    inline u4 const_value_index()
    {
	return const_value_index_;
    }

private:
    u4 slot_index_;
    int const_value_index_ = 0;
};
class JMethod : public JMember {
public:
    JMethod(JClass* jclass, MemberInfo* method_info);
    inline u4 max_stack()
    {
	return max_stack_;
    }

    inline u4 max_locals()
    {
	return max_locals_;
    }

    inline AttributeCodeInfo* CodeAttribute()
    {
	return code_attr_;
    }

private:
    u4 max_stack_;
    u4 max_locals_;
    bytes code_;
    AttributeCodeInfo* code_attr_;
};
}

#endif /* ifndef  */
