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

    if (field->IsAccessibleTo(d)) {
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
