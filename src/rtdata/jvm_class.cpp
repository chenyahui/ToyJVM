#include <jvm/rtdata/access_flag.h>
#include <jvm/rtdata/jvm_class.h>
#include <jvm/rtdata/jvm_member.h>
#include <jvm/rtdata/runtime_const_pool.h>

using namespace cyh;

JClass::JClass(ClassFile* classfile, ClassLoader* class_loader)
    : class_loader_(class_loader)
{
    access_flags_ = classfile->AccessFlags();
    name_ = classfile->ClassName();
    if (name_ != "java/lang/Object") {
	super_class_name_ = classfile->SuperClassName();
	interface_names_ = classfile->InterfaceNames();
    }
    rt_const_pool_ = new RuntimeConstPool(this, &classfile->constant_pool);

    for (auto field_info : classfile->fields) {
	fields_.push_back(new JField(this, field_info));
    }

    for (auto method_info : classfile->methods) {
	methods_.push_back(new JMethod(this, method_info));
    }
}
void JClass::ResolveSuperClass()
{
    if (name_ != "java/lang/Object") {
	super_class_ = class_loader_->LoadClass(super_class_name_);
    }
}

void JClass::ResolveInterfaces()
{
    for (auto interface_name : interface_names_) {
	interfaces_.push_back(class_loader_->LoadClass(interface_name));
    }
}
bool JClass::IsAccessibleTo(JClass* other)
{
    return IsPublic() || (GetPackageName() == other->GetPackageName());
}
bool JClass::IsPublic()
{
    return CheckIsPublic(access_flags_);
}
bool JClass::IsInterface()
{
    return CheckAccess(access_flags_, ACC_CLASS::INTERFACE);
}
bool JClass::IsAbstract()
{
    return CheckAccess(access_flags_, ACC_CLASS::ABSTRACT);
}

bool JClass::IsAssignableFrom(JClass* other)
{
    JClass* s = other;
    JClass* t = this;

    if (s == t) {
	return true;
    }

    if (!t->IsInterface()) {
	return s->IsSubClassOf(t);
    } else {
	return s->IsImplements(t);
    }
}
bool JClass::IsSubClassOf(JClass* other)
{
    for (auto c = super_class_; c != NULL; c = c->super_class_) {
	if (c == other) {
	    return true;
	}
    }
    return false;
}
bool JClass::IsSubInterfaceOf(JClass* iface)
{
    for (auto super_iface : interfaces_) {
	if (super_iface == iface || super_iface->IsSubInterfaceOf(iface)) {
	    return true;
	}
    }

    return false;
}
bool JClass::IsImplements(JClass* iface)
{
    for (auto c = this; c != NULL; c = c->super_class_) {
	for (auto i : interfaces_) {
	    if (i == iface || i->IsSubInterfaceOf(iface)) {
		return true;
	    }
	}
    }
    return false;
}
std::string JClass::GetPackageName()
{
    size_t last_found = name_.find_last_of("/");
    if (last_found == std::string::npos) {
	return "";
    }
    return name_.substr(0, last_found);
}

bool JObject::IsInstanceOf(JClass* jclass)
{
    return jclass->IsAssignableFrom(this->jclass_);
}
