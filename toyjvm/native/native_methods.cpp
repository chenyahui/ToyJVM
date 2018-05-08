//
// Created by cyhone on 18-5-8.
//

#include <toyjvm/native/native_methods.h>
#include <boost/optional.hpp>

namespace jvm {
    const std::function<void(JvmFrame &)> emptyNativeMethod = [](JvmFrame &) {};

    void NativeMethods::registerMethod(const std::string &class_name, const std::string &method_name,
                                       const std::string &method_descriptor, jvm::NativeMethod native_method)
    {
        auto signature = methodSignature(class_name, method_name, method_descriptor);
        native_methods_[signature] = native_method;
    }

    std::string NativeMethods::methodSignature(const std::string &class_name, const std::string &method_name,
                                               const std::string &method_descriptor)
    {
        return class_name + "~" + method_name + "~" + method_descriptor;
    }

    boost::optional<NativeMethod &> NativeMethods::find(const std::string &class_name, const std::string &method_name,
                                                       const std::string &method_descriptor)
    {
        auto signature = methodSignature(class_name, method_name, method_descriptor);
        if (native_methods_.find(signature) != native_methods_.end()) {
            return native_methods_[signature];
        }

        if (method_descriptor == "()V" && method_name == "registerNatives") {
            return emptyNativeMethod;
        }

        return boost::optional<NativeMethod &>();
    }
}