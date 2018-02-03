#ifndef TOYJVM_NATIVE_REGISTY_H
#define TOYJVM_NATIVE_REGISTY_H
#include <functional>
namespace cyh {
class JFrame;
using NativeMethod = std::function<void(JFrame*)>;

void Register(std::string& class_name, std::string& method_name, std::string& method_descriptor, NativeMethod method);
NativeMethod* FindNativeMethod(std::string& class_name, std::string& method_name, std::string& method_descriptor);
}

#endif /* end of include guard: TOYJVM_NATIVE_REGISTY_H */
