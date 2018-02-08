#include <glog/logging.h>
#include <jvm/rtdata/class_loader.h>
#include <jvm/rtdata/jvm_member.h>
#include <jvm/rtdata/runtime_const_pool.h>
#include <jvm/rtdata/string_pool.h>
#include <jvm/utils/types.h>
using namespace cyh;

static void CalcInstanceFieldSlotIds(JClass* jclass);
static void InitStaticFinalVar(JClass* jclass, JField*);
static void CalcStaticFieldSlotIds(JClass*);
static void AllocAndInitStaticVars(JClass* jclass);

void ClassLoader::LoadBasicClasses()
{
    auto jl_class_class = LoadClass("java/lang/Class");
    for (auto& kv : class_map_) {
	auto jclass = kv.second;
	if (jclass->jl_class() == NULL) {
	    auto jlc_obj = new JObject(jl_class_class);
	    jlc_obj->set_extra((char*)jclass);
	    jclass->set_jl_class(jlc_obj);
	}
    }
}
void ClassLoader::LoadPrimitiveClasses()
{
    for (auto& kv : PrimitiveTypes) {
	LoadPrimitiveClass(const_cast<std::string&>(kv.first));
    }
}

void ClassLoader::LoadPrimitiveClass(std::string& class_name)
{
    auto jclass = new JClass(this, class_name, false);
    auto jlc_obj = new JObject(class_map_["java/lang/Class"]);
    jlc_obj->set_extra((char*)jclass);
    jclass->set_jl_class(jlc_obj);

    class_map_[class_name] = jclass;
}
JClass* ClassLoader::LoadClass(std::string class_name)
{
    if (class_map_.find(class_name) != class_map_.end()) {
	return class_map_[class_name];
    }

    JClass* jclass = NULL;
    if (class_name[0] == '[') {
	jclass = LoadArrayClass(class_name);
    } else {
	jclass = LoadNoArrayClass(class_name);
    }

    if (class_map_.find("java/lang/Class") != class_map_.end()) {
	auto jlc_obj = new JObject(class_map_["java/lang/Class"]);
	jlc_obj->set_extra((char*)jclass);
	jclass->set_jl_class(jlc_obj);
    }

    class_map_[class_name] = jclass;
    return jclass;
}
JClass* ClassLoader::LoadArrayClass(std::string class_name)
{
    return new JClass(this, class_name);
}
JClass* ClassLoader::LoadNoArrayClass(std::string class_name)
{
    auto data = class_path_->ReadClass(class_name);
    auto jclass = defineClass(data);

    Link(jclass);

    return jclass;
}
JClass* ClassLoader::defineClass(const bytes& data)
{
    auto classfile = new ClassFile(data);
    classfile->Parse();

    auto jclass = new JClass(classfile, this);
    jclass->ResolveSuperClass();
    jclass->ResolveInterfaces();

    return jclass;
}

void ClassLoader::Link(JClass* jclass)
{
    Verify(jclass);
    Prepare(jclass);
}
void ClassLoader::Verify(JClass*)
{
    // TODO
}
void ClassLoader::Prepare(JClass* jclass)
{
    CalcInstanceFieldSlotIds(jclass);
    CalcStaticFieldSlotIds(jclass);
    AllocAndInitStaticVars(jclass);
}

void CalcInstanceFieldSlotIds(JClass* jclass)
{
    JClass* super_class = jclass->super_class();
    u4 slot_index = super_class != NULL ? super_class->instance_slot_count() : 0;

    for (auto field : jclass->fields()) {
	if (!field->IsStatic()) {
	    field->set_slot_index(slot_index);
	    slot_index++;

	    if (field->IsLongOrDouble()) {
		slot_index++;
	    }
	}
    }
    DLOG(INFO) << jclass->name() << " instance_slot_count " << slot_index;
    jclass->set_instance_slot_count(slot_index);
}
void CalcStaticFieldSlotIds(JClass* jclass)
{
    u4 slot_index = 0;
    for (auto field : jclass->fields()) {
	if (field->IsStatic()) {
	    field->set_slot_index(slot_index);
	    slot_index++;

	    if (field->IsLongOrDouble()) {
		slot_index++;
	    }
	}
    }

    jclass->set_static_slot_count(slot_index);
}

void AllocAndInitStaticVars(JClass* jclass)
{
    DLOG(INFO) << jclass->name() << " 开始初始化! ";
    for (auto field : jclass->fields()) {
	if (field->IsStatic() && field->IsFinal()) {
	    DLOG(INFO) << "static final " << field->name() << " " << field->descriptor();
	    InitStaticFinalVar(jclass, field);
	}
    }
}

#define CONST_TO_LOCAL(type)                          \
    type val = rt_const_pool->GetVal<type>(cp_index); \
    static_vars->Set<type>(slot_id, val);

void InitStaticFinalVar(JClass* jclass, JField* field)
{
    auto cp_index = field->const_value_index();
    if (cp_index <= 0) {
	DLOG(INFO) << field->name() << " cp index is " << cp_index;
	return;
    }
    auto static_vars = jclass->static_vars();
    auto rt_const_pool = jclass->rt_const_pool();
    auto slot_id = field->slot_index();
    auto& descriptor = field->descriptor();

    if (descriptor == "Z" || descriptor == "B" || descriptor == "C" || descriptor == "S" || descriptor == "I") {
	CONST_TO_LOCAL(int)
    } else if (descriptor == "J") {
	CONST_TO_LOCAL(long)
    } else if (descriptor == "F") {
	CONST_TO_LOCAL(float)
    } else if (descriptor == "D") {
	CONST_TO_LOCAL(double)
    } else if (descriptor == "Ljava/lang/String;") {
	// TODO
	auto& raw_str = rt_const_pool->GetVal<std::string>(cp_index);
	auto str_obj = GetStringFromPool(jclass->class_loader(), raw_str);
	static_vars->Set<JObject*>(slot_id, str_obj);
    } else if (descriptor[0] == 'L') {
	DLOG(INFO) << "尚未初始化" << field->name() << "." << field->descriptor();
    }
}
