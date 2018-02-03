#include <glog/logging.h>
#include <jvm/instruction/invoke_instructions.h>
#include <jvm/native/registy.h>
#include <jvm/rtdata/jvm_reference.h>

using namespace cyh;

static void InvokeMethod(JFrame* invoker, JMethod* method);

void INVOKE_STATIC_Instruction::Execute(JFrame* frame)
{
    auto const_pool = frame->jmethod()->jclass()->rt_const_pool();

    auto method_ref = const_pool->GetRef<MethodRef>(index);

    auto method = method_ref->ResolveMethod();
    if (!method->IsStatic()) {
	throw "不是static";
    }

    InvokeMethod(frame, method);
}

void INVOKE_SPECIAL_Instruction::Execute(JFrame* frame)
{
    auto current_class = frame->jmethod()->jclass();
    auto const_pool = current_class->rt_const_pool();

    auto method_ref = const_pool->GetRef<MethodRef>(index);

    auto resolved_class = method_ref->ResolveClass();
    auto method = method_ref->ResolveMethod();

    if (method->name() == "<init>" && method->jclass() != resolved_class) {
	throw "构造方法的所属类必须和调用类同名";
    }

    if (method->IsStatic()) {
	throw "不应该是static";
    }

    DLOG(INFO) << "method: " << method->name()
	       << " args count: " << method->args_slot_count();
    auto obj = frame->OpStack().GetRefFromTop(method->args_slot_count() - 1);

    if (method->IsProtected()
	&& method->jclass()->IsSuperClassOf(resolved_class)
	&& method->jclass()->GetPackageName() != resolved_class->GetPackageName()
	&& obj->jclass() != current_class
	&& !obj->jclass()->IsSubClassOf(current_class)) {
	throw "不合法的访问";
    }

    auto methodToInvoked = method;
    if (current_class->IsSuper()
	&& resolved_class->IsSuperClassOf(current_class)
	&& method->name() != "<init>") {
	methodToInvoked = LookupMethodInClass(current_class->super_class(), method_ref->name(), method_ref->descriptor());
    }

    if (methodToInvoked != NULL && methodToInvoked->IsAbstract()) {
	throw "abstract method cannot be invoked";
    }

    InvokeMethod(frame, methodToInvoked);
}
static void _println(OperandStack& opstack, std::string& descriptor)
{
    if (descriptor == "(J)V") {
	std::cout << opstack.Pop<long>() << std::endl;
    } else if (descriptor == "(I)V") {
	std::cout << opstack.Pop<int>() << std::endl;
    } else if (descriptor == "(Ljava/lang/String;)V") {
	auto str_obj = opstack.Pop<JObject*>();

	std::string name = "value", descriptor = "[C";
	auto char_array_obj = dynamic_cast<JArray<char>*>(str_obj->GetRefVar(name, descriptor));
	auto& char_vec = char_array_obj->raw_data();

	std::string str(char_vec.begin(), char_vec.end());
	std::cout << str << std::endl;
    }
    opstack.Pop<j_ref>();
}
void INVOKE_VIRTUAL_Instruction::Execute(JFrame* frame)
{
    auto current_class = frame->jmethod()->jclass();
    auto const_pool = current_class->rt_const_pool();

    auto method_ref = const_pool->GetRef<MethodRef>(index);

    //    auto resolved_class = method_ref->ResolveClass();
    auto method = method_ref->ResolveMethod();

    if (method->IsStatic()) {
	throw "不应该是static";
    }
    DLOG(INFO) << "method: " << method->name()
	       << " args count: " << method->args_slot_count();
    auto obj = frame->OpStack().GetRefFromTop(method->args_slot_count() - 1);
    if (obj == NULL) {
	// hack!
	if (method->name() == "println") {
	    _println(frame->OpStack(), method_ref->descriptor());
	    return;
	}
	throw "null pointer exception";
    }
    if (method->IsProtected()
	&& method->jclass()->IsSuperClassOf(current_class)
	&& method->jclass()->GetPackageName() != current_class->GetPackageName()
	&& obj->jclass() != current_class
	&& !obj->jclass()->IsSubClassOf(current_class)) {
	throw "不合法的访问";
    }

    auto methodToInvoked = LookupMethodInClass(obj->jclass(),
	method_ref->name(),
	method_ref->descriptor());

    if (methodToInvoked != NULL && methodToInvoked->IsAbstract()) {
	throw "abstract method cannot be invoked";
    }

    InvokeMethod(frame, methodToInvoked);
}
void INVOKE_INTERFACE_Instruction::FetchOperands(ByteCodeReader& reader)
{
    index_ = static_cast<int>(reader.Read<u2>());
    reader.Read<u1>();
    reader.Read<u1>();
}

void INVOKE_INTERFACE_Instruction::Execute(JFrame* frame)
{
    auto const_pool = frame->jmethod()->jclass()->rt_const_pool();

    auto method_ref = const_pool->GetRef<InterfaceMethodRef>(index_);

    auto resolved_method = method_ref->ResolveInterfaceMethod();

    if (resolved_method->IsStatic() || resolved_method->IsPrivate()) {
	throw "不合法的访问";
    }

    auto obj = frame->OpStack().GetRefFromTop(resolved_method->args_slot_count() - 1);

    if (obj == NULL) {
	throw "空指针错误";
    }

    if (!obj->jclass()->IsImplements(method_ref->ResolveClass())) {
	throw "该类没有实现该接口";
    }
    auto methodToInvoked = LookupMethodInClass(obj->jclass(),
	method_ref->name(),
	method_ref->descriptor());

    if (methodToInvoked != NULL && methodToInvoked->IsAbstract()) {
	throw "abstract method cannot be invoked";
    }

    if (!methodToInvoked->IsPublic()) {
	throw "不合法的访问";
    }

    InvokeMethod(frame, methodToInvoked);
}

void INVOKE_NATIVE_Instruction::Execute(JFrame* frame)
{
    auto method = frame->jmethod();
    auto class_name = method->jclass()->name();
    auto method_name = method->name();
    auto method_descriptor = method->descriptor();

    auto native_method = FindNativeMethod(class_name, method_name, method_descriptor);
    if (native_method == NULL) {
	auto method_info = class_name + "." + method_name + method_descriptor;
    }
    (*native_method)(frame);
}
void InvokeMethod(JFrame* invoker, JMethod* method)
{
    assert(method != NULL);
    auto jthread = invoker->Thread();
    auto new_frame = new JFrame(jthread, method);

    jthread->PushFrame(new_frame);
    auto slot_num = method->args_slot_count();

    auto& opstack = invoker->OpStack();
    auto& local_vars = new_frame->LocalVars();

    for (auto i = slot_num - 1; i >= 0; i--) {
	auto slot = opstack.Pop<LocalSlot>();
	local_vars.Set<LocalSlot>(i, slot);
    }
}
