//
// Created by cyhone on 18-5-9.
//

#include <toyjvm/native/java/lang/Object.h>
#include <toyjvm/runtime/jvm_reference.h>

using namespace jvm::native;

void JavaLangObject::registerMethod(const std::string &method_name, const std::string &method_descriptor,
                                    jvm::native::NativeMethod native_method)
{
    NativeMethods::registerMethod("java/lang/Object", method_name, method_descriptor, native_method);
}

bool JavaLangObject::init()
{
    registerMethod("getClass",
                   "()Ljava/lang/Class;", BIND_STATIC(JavaLangObject::getClass));
    return true;
}

void JavaLangObject::getClass(jvm::JvmFrame &frame)
{
    auto vars = frame.localSlots();
    auto this_ref = vars.getThis();
    frame.operandStack().push<jref>(this_ref->klass()->metaClass());
}