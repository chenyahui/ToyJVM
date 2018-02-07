#include <glog/logging.h>
#include <jvm/native/array_copy.h>
#include <jvm/native/get_primitive_class.h>
#include <jvm/native/registy.h>
#include <jvm/native/throwable.h>
#include <map>

namespace cyh {
using std::placeholders::_1;
void EmptyNativeMethod(JFrame*)
{
}
static std::map<std::string, NativeMethod> g_registry;
static NativeMethod g_empty_func = std::bind(EmptyNativeMethod, _1);

std::string MethodSignature(std::string& class_name, std::string& method_name, std::string& method_descriptor)
{
    return class_name + "~" + method_name + "~" + method_descriptor;
}
void Register(const char* class_name, const char* method_name, const char* method_descriptor, NativeMethod method)
{
    std::string class_str = class_name;
    std::string method_str = method_name;
    std::string method_descriptor_str = method_descriptor;

    Register(class_str, method_str, method_descriptor_str, method);
}
void Register(std::string& class_name, std::string& method_name, std::string& method_descriptor, NativeMethod method)
{
    auto key = MethodSignature(class_name, method_name, method_descriptor);
    g_registry[key] = method;
}
NativeMethod* FindNativeMethod(std::string& class_name, std::string& method_name, std::string& method_descriptor)
{
    auto key = MethodSignature(class_name, method_name, method_descriptor);
    if (g_registry.find(key) != g_registry.end()) {
	return &(g_registry[key]);
    }

    if (method_descriptor == "()V" && method_name == "registerNatives") {
	return &g_empty_func;
    }
    DLOG(INFO) << "not found native method :" << key;
    return NULL;
}
void InitNativeMethods()
{
    Register("java/lang/System", "arraycopy", "(Ljava/lang/Object;ILjava/lang/Object;II)V", std::bind(arraycopy, _1));
    Register("java/lang/Throwable", "fillInStackTrace", "(I)Ljava/lang/Throwable;", std::bind(fillInStackTrace, _1));
    Register("java/lang/Class", "getPrimitiveClass", "(Ljava/lang/String;)Ljava/lang/Class;", std::bind(getPrimitiveClass, _1));
}
}
