#include <glog/logging.h>
#include <jvm/rtdata/symbol_ref.h>
using namespace cyh;

JClass* SymbolRef::ResolveClass()
{

    if (jclass_ == NULL) {
	ResolveClassRef();
    }
    return jclass_;
}

void SymbolRef::ResolveClassRef()
{
    auto d = rt_const_pool_->jclass();
    auto c = d->class_loader()->LoadClass(class_name_);
    if (!c->IsAccessibleTo(d)) {
	throw "access error";
    }
    jclass_ = c;
}
MemberRef::MemberRef(RuntimeConstPool* rt_const_pool, ConstantMemberRefInfo* member_ref_info)
    : SymbolRef(rt_const_pool)
{
    this->class_name_ = member_ref_info->ClassName();

    auto name_descriptor = member_ref_info->NameAndDescriptor();
    this->name_ = name_descriptor.first;
    this->descriptor_ = name_descriptor.second;
}

JField* FieldRef::ResolveField()
{
    if (jfield_ == NULL) {
	ResolveFieldRef();
    }
    return jfield_;
}

void FieldRef::ResolveFieldRef()
{
    auto d = rt_const_pool_->jclass();
    auto c = ResolveClass();
    auto field = LookupField(c);

    if (field == NULL) {
	throw "No found field!";
    }

    if (!field->IsAccessibleTo(d)) {
	throw "Access Illegal Field!";
    }

    jfield_ = field;
}

JField* FieldRef::LookupField(JClass* jclass)
{
    for (auto field : jclass->fields()) {
	if (field->name() == name_ && field->descriptor() == descriptor_) {
	    return field;
	}
    }

    for (auto interface : jclass->interfaces()) {
	auto field = LookupField(interface);
	if (field != NULL) {
	    return field;
	}
    }

    auto super_class = jclass->super_class();
    if (super_class != NULL) {
	return LookupField(super_class);
    }
    return NULL;
}

JMethod* MethodRef::ResolveMethod()
{
    if (jmethod_ == NULL) {
	ResolveMethodRef();
    }

    return jmethod_;
}

void MethodRef::ResolveMethodRef()
{
    auto d = rt_const_pool_->jclass();
    auto c = ResolveClass();

    if (c->IsInterface()) {
	throw "不能直接访问interface的方法";
    }

    auto method = LookupMethod(c);
    if (method == NULL) {
	throw "no such method";
    }

    if (!method->IsAccessibleTo(d)) {
	throw "Method illgeal access";
    }

    this->jmethod_ = method;
}

JMethod* MethodRef::LookupMethod(JClass* jclass)
{
    auto method = LookupMethodInClass(jclass, name_, descriptor_);

    if (method == NULL) {
	method = LookupMethodInInterfaces(jclass->interfaces(), name_, descriptor_);
    }

    return method;
}

JMethod* InterfaceMethodRef::ResolveInterfaceMethod()
{
    if (jmethod_ == NULL) {
	ResolveInterfaceMethodRef();
    }

    return jmethod_;
}

void InterfaceMethodRef::ResolveInterfaceMethodRef()
{
    auto d = rt_const_pool_->jclass();
    auto c = ResolveClass();

    if (!c->IsInterface()) {
	throw "不是interface的方法";
    }

    auto method = LookupInterfaceMethod(c);
    if (method == NULL) {
	throw "no such method";
    }

    if (!method->IsAccessibleTo(d)) {
	throw "illgeal access";
    }

    this->jmethod_ = method;
}

JMethod* InterfaceMethodRef::LookupInterfaceMethod(JClass* iface)
{
    for (auto method : iface->methods()) {
	if (method->name() == name_ && method->descriptor() == descriptor_) {
	    return method;
	}
    }

    auto method = LookupMethodInInterfaces(iface->interfaces(), name_, descriptor_);
    return method;
}
namespace cyh {
JMethod* LookupMethodInClass(JClass* jclass, std::string name, std::string descriptor)
{
    for (auto c = jclass; c != NULL; c = c->super_class()) {
	for (auto method : c->methods()) {
	    if (method->name() == name && method->descriptor() == descriptor) {
		return method;
	    }
	}
    }

    return NULL;
}

JMethod* LookupMethodInInterfaces(std::vector<JClass*>& ifaces, std::string name, std::string descriptor)
{
    for (auto iface : ifaces) {
	for (auto method : iface->methods()) {
	    if (method->name() == name && method->descriptor() == descriptor) {
		return method;
	    }
	}

	auto method = LookupMethodInInterfaces(iface->interfaces(), name, descriptor);
	if (method != NULL) {
	    return method;
	}
    }

    return NULL;
}
}
