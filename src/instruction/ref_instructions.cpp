#include <jvm/instruction/ref_instructions.h>
#include <jvm/rtdata/jvm_frame.h>
#include <jvm/rtdata/runtime_const_pool.h>
#include <jvm/rtdata/symbol_ref.h>

using namespace cyh;

void NEW_Instruction::Execute(JFrame* jframe)
{
    auto rt_const_pool = jframe->jmethod()
			     ->jclass()
			     ->rt_const_pool();

    auto class_ref = rt_const_pool->GetRef<ClassRef>(index);
    auto jclass = class_ref->ResolveClass();

    if (jclass->IsInterface() && jclass->IsAbstract()) {
	throw "interface and abstract cannot instance";
    }

    JObject* obj = new JObject(jclass);

    jframe->OpStack().Push<JObject*>(obj);
}
#define STATIC_GET(type)                           \
    opstack.Push<type>(slots->Get<type>(slot_id)); \
    break;

void GETSTATIC_Instruction::Execute(JFrame* jframe)
{
    auto rt_const_pool = jframe->jmethod()->jclass()->rt_const_pool();
    auto field_ref = rt_const_pool->GetRef<FieldRef>(index);
    auto jfield = field_ref->ResolveField();
    auto jclass = jfield->jclass();

    if (!jfield->IsStatic()) {
	throw "put static must apply to static field";
    }
    auto descriptor = jfield->descriptor();
    auto slot_id = jfield->slot_index();
    auto slots = jclass->static_vars();
    auto& opstack = jframe->OpStack();

    switch (descriptor[0]) {
    case 'Z':
    case 'B':
    case 'C':
    case 'S':
    case 'I': {
	STATIC_GET(int)
    }
    case 'F': {
	STATIC_GET(float)
    }
    case 'J': {
	STATIC_GET(long)
    }
    case 'D': {
	STATIC_GET(double)
    }
    case 'L':
    case '[': {
	STATIC_GET(j_ref)
    }
    }
}
void PUTSTATIC_Instruction::Execute(JFrame* jframe)
{
    auto current_method = jframe->jmethod();
    auto current_class = current_method->jclass();
    auto rt_const_pool = current_class->rt_const_pool();
    auto field_ref = rt_const_pool->GetRef<FieldRef>(index);
    auto jfield = field_ref->ResolveField();

    auto jclass = jfield->jclass();

    if (!jfield->IsStatic()) {
	throw "put static must apply to static field";
    }

    if (jfield->IsFinal()) {
	if (current_class != jclass && current_method->name() != "<clinit>") {
	    throw "java illegal access error";
	}
    }

    auto descriptor = jfield->descriptor();
    auto slot_id = jfield->slot_index();
    auto slots = jclass->static_vars();
    auto& opstack = jframe->OpStack();

    switch (descriptor[0]) {
    case 'Z':
    case 'B':
    case 'C':
    case 'S':
    case 'I': {
	slots->Set<int>(slot_id, opstack.Pop<int>());
	break;
    }
    case 'F': {
	slots->Set<float>(slot_id, opstack.Pop<float>());
	break;
    }
    case 'J': {
	slots->Set<long>(slot_id, opstack.Pop<long>());
	break;
    }
    case 'D': {
	slots->Set<double>(slot_id, opstack.Pop<double>());
	break;
    }
    case 'L':
    case '[': {
	slots->Set<j_ref>(slot_id, opstack.Pop<j_ref>());
	break;
    }
    }
}
#define FIELD_PUT(type)                    \
    auto val = opstack.Pop<type>();        \
    auto ref = opstack.Pop<j_ref>();       \
                                           \
    if (ref == NULL) {                     \
	throw "nullpointer";               \
    }                                      \
    ref->fields().Set<type>(slot_id, val); \
    break;

void PUTFIELD_Instruction::Execute(JFrame* frame)
{
    auto current_method = frame->jmethod();
    auto current_class = current_method->jclass();
    auto rt_const_pool = current_class->rt_const_pool();
    auto field_ref = rt_const_pool->GetRef<FieldRef>(index);
    auto jfield = field_ref->ResolveField();

    auto jclass = jfield->jclass();

    if (!jfield->IsStatic()) {
	throw "put static must apply to static field";
    }

    if (jfield->IsFinal()) {
	if (current_class != jclass && current_method->name() != "<init>") {
	    throw "java illegal access error";
	}
    }
    auto descriptor = jfield->descriptor();
    auto slot_id = jfield->slot_index();
    auto& opstack = frame->OpStack();

    switch (descriptor[0]) {
    case 'Z':
    case 'B':
    case 'C':
    case 'S':
    case 'I': {
	FIELD_PUT(int)
    }
    case 'F': {
	FIELD_PUT(float)
    }
    case 'D': {
	FIELD_PUT(double)
    }
    case 'J': {
	FIELD_PUT(long)
    }
    case 'L':
    case '[': {
	FIELD_PUT(j_ref)
    }
    }
}
#define FIELD_GET(type)                    \
    opstack.Push<type>(slots.Get<type>(slot_id)); \
    break;
void GETFIELD_Instruction::Execute(JFrame* jframe)
{
    auto current_method = jframe->jmethod();
    auto current_class = current_method->jclass();
    auto rt_const_pool = current_class->rt_const_pool();
    auto field_ref = rt_const_pool->GetRef<FieldRef>(index);
    auto jfield = field_ref->ResolveField();

    //auto jclass = jfield->jclass();
    auto& opstack = jframe->OpStack();

    if (!jfield->IsStatic()) {
	throw "put static must apply to static field";
    }
    auto ref = opstack.Pop<j_ref>();
    if (ref == NULL) {
	throw "null pointer";
    }
    auto descriptor = jfield->descriptor();
    auto slot_id = jfield->slot_index();
    auto& slots = ref->fields();
    switch (descriptor[0]) {
    case 'Z':
    case 'B':
    case 'C':
    case 'S':
    case 'I': {
	FIELD_GET(int)
    }
    case 'F': {
	FIELD_GET(float)
    }
    case 'D': {
	FIELD_GET(double)
    }
    case 'J': {
	FIELD_GET(long)
    }
    case 'L':
    case '[': {
	FIELD_GET(j_ref)
    }
    }
}

void INSTANCEOF_Instruction::Execute(JFrame* jframe)
{
    auto& opstack = jframe->OpStack();
    auto ref = opstack.Pop<j_ref>();
    if (ref == NULL) {
	opstack.Push<int>(0);
	return;
    }

    auto class_ref = jframe->jmethod()->jclass()->rt_const_pool()->GetRef<ClassRef>(index);
    auto jclass = class_ref->ResolveClass();

    if (ref->IsInstanceOf(jclass)) {
	opstack.Push<int>(1);
    } else {
	opstack.Push<int>(0);
    }
}

void CHECKCAST_Instruction::Execute(JFrame* jframe)
{
    auto& opstack = jframe->OpStack();
    auto ref = opstack.Pop<j_ref>();
    opstack.Push<j_ref>(ref);

    if (ref == NULL) {
	return;
    }
    auto jclass = jframe->jmethod()
		      ->jclass()
		      ->rt_const_pool()
		      ->GetRef<ClassRef>(index)
		      ->ResolveClass();
    if (!ref->IsInstanceOf(jclass)) {
	throw "class cast exception";
    }
}

