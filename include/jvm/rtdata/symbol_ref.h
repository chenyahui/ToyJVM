#ifndef TOYJVM_RTDATA_SYMBOL_REF_H
#define TOYJVM_RTDATA_SYMBOL_REF_H

#include <jvm/rtdata/class_loader.h>
#include <jvm/rtdata/jvm_member.h>
#include <jvm/rtdata/runtime_const_pool.h>

namespace cyh {
class SymbolRef {
public:
    SymbolRef(RuntimeConstPool* rt_const_pool)
	: rt_const_pool_(rt_const_pool)
    {
    }
    JClass* ResolveClass();

protected:
    void ResolveClassRef();

    RuntimeConstPool* rt_const_pool_;
    JClass* jclass_;
    std::string class_name_;
};

class ClassRef : public SymbolRef {
public:
    ClassRef(RuntimeConstPool* rt_const_pool, ConstantKlassInfo* class_info)
	: SymbolRef(rt_const_pool)
    {
	this->class_name_ = class_info->ClassName();
    }
};

class MemberRef : public SymbolRef {
public:
    MemberRef(RuntimeConstPool*, ConstantMemberRefInfo*);

protected:
    std::string name_;
    std::string descriptor_;
};
class FieldRef : public MemberRef {
public:
    FieldRef(RuntimeConstPool* rt_const_pool, ConstantFieldRefInfo* field_ref_info)
	: MemberRef(rt_const_pool, field_ref_info)
    {
    }
    JField* ResolveField();

private:
    void ResolveFieldRef();
    JField* LookupField(JClass*);

    JField* jfield_;
};
class MethodRef : public MemberRef {
public:
    MethodRef(RuntimeConstPool* rt_const_pool, ConstantMethodRefInfo* method_ref_info)
	: MemberRef(rt_const_pool, method_ref_info)
    {
    }
    JMethod* ResolveMethod() {
    	return NULL;
    }

private:
    void ResolveMethodRef() {}

    JMethod* jmethod_;
};
class InterfaceMethodRef : public MemberRef {
public:
    InterfaceMethodRef(RuntimeConstPool* rt_const_pool, ConstantInterfaceMethodRefInfo* interface_method_ref_info)
	: MemberRef(rt_const_pool, interface_method_ref_info)
    {
    }

private:
    JMethod* jmethod_;
};
}
#endif /* end of include guard: TOYJVM_RTDATA_SYMBOL_REF_H */
