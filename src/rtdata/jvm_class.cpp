#include <glog/logging.h>
#include <jvm/rtdata/access_flag.h>
#include <jvm/rtdata/jvm_class.h>
#include <jvm/rtdata/jvm_member.h>
#include <jvm/rtdata/jvm_reference.h>
#include <jvm/rtdata/runtime_const_pool.h>
#include <jvm/utils/types.h>
#include <unordered_map>
using namespace cyh;

const std::unordered_map<std::string, std::string> PrimitiveTypes = {
    { "void", "V" },
    { "boolean", "Z" },
    { "byte", "B" },
    { "short", "S" },
    { "int", "I" },
    { "long", "J" },
    { "char", "C" },
    { "float", "F" },
    { "double", "D" }
};
std::string ToDescriptor(const std::string& class_name)
{
    if (class_name[0] == '[') {
	return class_name;
    }

    auto data = PrimitiveTypes.find(class_name);
    if (data != PrimitiveTypes.end()) {
	return data->second;
    }

    return "L" + class_name + ";";
}
std::string GetArrayClassName(const std::string& class_name)
{
    return "[" + ToDescriptor(class_name);
}
// for array class
JClass::JClass(ClassLoader* class_loader, std::string name)
    : access_flags_(static_cast<u2>(ACC_CLASS::PUBLIC))
    , name_(name)
    , class_loader_(class_loader)
    , instance_slot_count_(0)
    , static_slot_count_(0)
    , init_started_(true)
{
    super_class_ = class_loader_->LoadClass("java/lang/Object");

    interfaces_.push_back(class_loader_->LoadClass("java/lang/Cloneable"));
    interfaces_.push_back(class_loader_->LoadClass("java/io/Serializable"));
}

JClass::JClass(ClassFile* classfile, ClassLoader* class_loader)
    : class_loader_(class_loader)
    , instance_slot_count_(0)
    , static_slot_count_(0)
{
    access_flags_ = classfile->AccessFlags();
    name_ = classfile->ClassName();
    DLOG(INFO) << "class name: " << name_;
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
    DLOG(INFO) << "package name compare : \"" << GetPackageName() << "\"#\""<<other->GetPackageName()<<"\"";
    DLOG(INFO) << "pointer compare: " << this << "#" <<  other ;
    DLOG(INFO) << "class_name compare: " << name_ << "#" <<  other->name_ ;
    return this == other || IsPublic() || (GetPackageName() == other->GetPackageName());
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
bool JClass::IsSuper()
{
    return CheckAccess(access_flags_, ACC_CLASS::SUPER);
}

bool JClass::IsAssignableFrom(JClass* other)
{
    JClass* s = other;
    JClass* t = this;

    if (s == t) {
	return true;
    }

    if (!s->IsArray()) {
	if (!s->IsInterface()) {
	    if (!t->IsInterface()) {
		return s->IsSubClassOf(t);
	    } else {
		return s->IsImplements(t);
	    }
	}
    } else {
	if (!t->IsArray()) {
	    if (!t->IsInterface()) {
		return t->IsJlObject();
	    } else {
		return t->IsJlObject() || t->IsJioSerializable();
	    }

	} else {
	    auto sc = s->ComponentClass();
	    auto tc = t->ComponentClass();

	    return sc == tc || tc->IsAssignableFrom(sc);
	}
    }
    if (!t->IsInterface()) {
	return s->IsSubClassOf(t);
    } else {
	return s->IsImplements(t);
    }
}
bool JClass::IsJlObject()
{
    return name_ == "java/lang/Object";
}
bool JClass::IsJlCloneable()
{
    return name_ == "java/lang/Cloneable";
}

bool JClass::IsJioSerializable()
{
    return name_ == "java/io/Serializable";
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
bool JClass::IsSuperClassOf(JClass* other)
{
    return other->IsSubClassOf(this);
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
bool JClass::IsArray()
{
    return name_[0] == '[';
}

#define NEW_ARRAY(name, type)                 \
    if (name_ == "["#name"") {               \
	return new JArray<type>(count, this); \
    }

JBaseArray* JClass::ArrayFactory(u4 count)
{
    if (!IsArray()) {
	throw "Not Array Class" + name_;
    }

    NEW_ARRAY(Z, bool)
    NEW_ARRAY(B, j_byte)
    NEW_ARRAY(C, j_char)
    NEW_ARRAY(S, j_short)
    NEW_ARRAY(I, j_int)
    NEW_ARRAY(J, j_long)
    NEW_ARRAY(F, j_float)
    NEW_ARRAY(D, j_double)

    return new JArray<JReference*>(count, this);
}
std::string ToClassName(std::string& descriptor)
{
    if (descriptor[0] == '[') {
	return descriptor;
    }
    if (descriptor[0] == 'L') {
    // L at begin, comma at end
	return descriptor.substr(1, descriptor.size() - 2);
    }

    for (auto& kv : PrimitiveTypes) {
	if (kv.second == descriptor) {
	    return kv.first;
	}
    }

    throw "invalid descriptor" + descriptor;
}
JClass* JClass::ComponentClass()
{
    return class_loader_->LoadClass(GetComponentName());
}
std::string JClass::GetComponentName()
{
    if (name_[0] == '[') {
	auto component_type_descriptor = name_.substr(1);
	return ToClassName(component_type_descriptor);
    }
    throw "not a array";
}
JClass* JClass::ArrayClass()
{
    auto array_class_name = GetArrayClassName(this->name_);

    return class_loader_->LoadClass(array_class_name);
}
