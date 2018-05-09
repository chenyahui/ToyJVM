//
// Created by cyhone on 18-5-9.
//

#include <toyjvm/native/java/lang/Class.h>
#include <toyjvm/runtime/jvm_reference.h>
#include <toyjvm/runtime/string_pool.h>
#include <toyjvm/runtime/class_loader.h>

using namespace jvm::native;

void JavaLangClass::registerMethod(const std::string &method_name, const std::string &method_descriptor,
                                   jvm::native::NativeMethod&& native_method)
{
    NativeMethods::registerMethod("java/lang/Class", method_name, method_descriptor, native_method);
}

bool JavaLangClass::init()
{
    registerMethod("getPrimitiveClass",
                   "(Ljava/lang/String;)Ljava/lang/Class;", BIND_STATIC(JavaLangClass::getPrimitiveClass));

    registerMethod("getName0",
                   "()Ljava/lang/String;", BIND_STATIC(JavaLangClass::getName0));

    registerMethod("desiredAssertionStatus0",
                   "(Ljava/lang/Class;)Z", BIND_STATIC(JavaLangClass::desiredAssertionStatus0));

    return true;
}

void JavaLangClass::getPrimitiveClass(jvm::JvmFrame &frame)
{
    auto name_obj = frame.localSlots().at<jobj>(0);
    auto name = jvm::javaLangStringAsString(name_obj);

    auto meta_ref = Loader::instance()->loadClass(name)->metaClass();

    frame.operandStack().push<jref>(meta_ref);
}

void JavaLangClass::getName0(jvm::JvmFrame &frame)
{
    auto this_obj = frame.localSlots().getThis();
    auto str_obj = StringPool::intern(this_obj->klass()->javaName());
    frame.operandStack().push<jobj>(str_obj);
}

void JavaLangClass::desiredAssertionStatus0(jvm::JvmFrame &frame)
{
    frame.operandStack().push<jbool>(false);
}