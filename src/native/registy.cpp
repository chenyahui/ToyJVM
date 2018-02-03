#include <jvm/native/registy.h>
#include <map>
namespace cyh {
using std::placeholders::_1;
void EmptyNativeMethod(JFrame*)
{
}
static std::map<std::string, NativeMethod&> g_registry;
static NativeMethod g_empty_func = std::bind(EmptyNativeMethod, _1);

std::string MethodSignature(std::string& class_name, std::string& method_name, std::string& method_descriptor)
{
    return class_name + "~" + method_name + "~" + method_descriptor;
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
    return NULL;
}
}
