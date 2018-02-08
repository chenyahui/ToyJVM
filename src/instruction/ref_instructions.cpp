#include <glog/logging.h>
#include <jvm/instruction/ref_instructions.h>
#include <jvm/native/throwable.h>
#include <jvm/rtdata/jvm_frame.h>
#include <jvm/rtdata/runtime_const_pool.h>
#include <jvm/rtdata/string_pool.h>
#include <jvm/rtdata/symbol_ref.h>

#include <iostream>

using namespace cyh;

void NEW_Instruction::Execute(JFrame* jframe)
{
    auto rt_const_pool = jframe->jmethod()
			     ->jclass()
			     ->rt_const_pool();

    auto class_ref = rt_const_pool->GetRef<ClassRef>(index);
    auto jclass = class_ref->ResolveClass();

    if (!jclass->init_started()) {
	jframe->RevertNextPc();
	jclass->InitClass(jframe->Thread());
	return;
    }
    if (jclass->IsInterface() && jclass->IsAbstract()) {
	throw "interface and abstract cannot instance";
    }
    auto obj = new JObject(jclass);

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
    assert(jfield != NULL);
    DLOG(INFO) << "index: " << index
	       << "; jfield->" << jfield->name()
	       << ";" << jfield->descriptor();
    auto jclass = jfield->jclass();

    if (!jfield->IsStatic()) {
	throw "put static must apply to static field";
    }

    if (!jclass->init_started()) {
	jframe->RevertNextPc();
	jclass->InitClass(jframe->Thread());
	return;
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

    if (!jclass->init_started()) {
	jframe->RevertNextPc();
	jclass->InitClass(jframe->Thread());
	return;
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
#define FIELD_PUT(type)                     \
    auto val = opstack.Pop<type>();         \
    auto ref = opstack.Pop<JObject*>();     \
                                            \
    if (ref == NULL) {                      \
	throw "nullpointer";                \
    }                                       \
    ref->fields()->Set<type>(slot_id, val); \
    break;

void PUTFIELD_Instruction::Execute(JFrame* frame)
{
    auto current_method = frame->jmethod();
    auto current_class = current_method->jclass();
    auto rt_const_pool = current_class->rt_const_pool();
    auto field_ref = rt_const_pool->GetRef<FieldRef>(index);
    auto jfield = field_ref->ResolveField();

    auto jclass = jfield->jclass();

    if (jfield->IsStatic()) {
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
#define FIELD_GET(type)                            \
    opstack.Push<type>(slots->Get<type>(slot_id)); \
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

    if (jfield->IsStatic()) {
	throw "put static must apply to static field";
    }
    auto ref = opstack.Pop<JObject*>();
    if (ref == NULL) {
	throw "null pointer";
    }
    auto descriptor = jfield->descriptor();
    DLOG(INFO) << "Get field: " << jfield->name() << "#" << descriptor;
    auto slot_id = jfield->slot_index();
    auto slots = ref->fields();
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
    auto ref = opstack.Pop<JReference*>();
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
    auto ref = opstack.Pop<JReference*>();
    opstack.Push<JReference*>(ref);

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

void ATHROW_Instruction::Execute(JFrame* frame)
{
    auto ex_obj = frame->OpStack().Pop<JObject*>();

    if (ex_obj == NULL) {
	throw "null pointer";
    }

    auto jthread = frame->Thread();
    if (!FindAndGotoExceptionHandler(jthread, ex_obj)) {
	HandleUncaughtException(jthread, ex_obj);
    }
}

bool ATHROW_Instruction::FindAndGotoExceptionHandler(JThread* jthread, JObject* obj)
{
    while (true) {
	auto frame = jthread->TopFrame();
	auto pc = frame->NextPc() - 1;

	auto handler_pc = frame->jmethod()->FindExceptionHandler(obj->jclass(), pc);
	if (handler_pc > 0) {
	    auto& opstack = frame->OpStack();
	    opstack.Clear();
	    opstack.Push<JObject*>(obj);
	    frame->SetNextPc(handler_pc);
	    return true;
	}
	jthread->PopFrame();
	if (jthread->IsStackEmpty()) {
	    break;
	}
    }

    return false;
}

void ATHROW_Instruction::HandleUncaughtException(JThread* jthread, JObject* exobj)
{
    jthread->ClearStack();
    std::string name = "detailMessage", descriptor = "Ljava/lang/String;";
    auto msg_obj = dynamic_cast<JObject*>(exobj->GetRefVar(name, descriptor));
    std::string msg = TransJString(msg_obj);
    std::cout << "Exception in thread \"main\" " << exobj->jclass()->JavaName() << ":" << msg << std::endl;
    if (exobj->has_extra()) {
	auto stack_traces = exobj->ExtraTo<std::vector<StackTraceElement>*>();

	for (auto& trace_item : *stack_traces) {
	    std::cout << "\t at " << trace_item.ToString() << std::endl;
	}
    }
}
