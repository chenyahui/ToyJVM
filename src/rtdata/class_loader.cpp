#include <glog/logging.h>
#include <jvm/rtdata/class_loader.h>
#include <jvm/rtdata/jvm_member.h>
#include <jvm/rtdata/runtime_const_pool.h>
#include <jvm/utils/types.h>
using namespace cyh;

static void CalcInstanceFieldSlotIds(JClass* jclass);
static void InitStaticFinalVar(JClass* jclass, JField*);
static void CalcStaticFieldSlotIds(JClass*);
static void AllocAndInitStaticVars(JClass* jclass);

JClass* ClassLoader::LoadClass(std::string class_name)
{
    DLOG(INFO) << "begin to load class:#"<<class_name<<"#";
    DLOG(INFO) << "cache size: " << class_map_.size();
    
    for(auto& kv:class_map_){
        DLOG(INFO) << kv.first << "->"<<kv.second->name();
    }

    if (class_map_.find(class_name) != class_map_.end()) {
    DLOG(INFO) << "load from cache :" << class_name;
	return class_map_[class_name];
    }

    JClass* jclass = NULL;
    if (class_name[0] == '[') {
	jclass = LoadArrayClass(class_name);
    } else {
	jclass = LoadNoArrayClass(class_name);
    }
    
    DLOG(INFO) << "load class :" << class_name;
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
    for (auto field : jclass->fields()) {
	if (field->IsStatic() && field->IsFinal()) {
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
    }
}
