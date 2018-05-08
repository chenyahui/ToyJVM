//
// Created by cyhone on 18-5-8.
//

#ifndef TOYJVM_NATIVE_METHODS_H
#define TOYJVM_NATIVE_METHODS_H

#include <toyjvm/utilities/all_static.h>
#include <toyjvm/runtime/jvm_frame.h>
#include <unordered_map>
#include <functional>
#include <boost/optional.hpp>

namespace jvm {
    using NativeMethod = std::function<void(JvmFrame &)>;

    class NativeMethods : AllStatic {
    public:
        static void registerMethod(const std::string &class_name,
                                   const std::string &method_name,
                                   const std::string &method_descriptor,
                                   NativeMethod native_method);

        static boost::optional<NativeMethod &> find(const std::string &class_name,
                                           const std::string &method_name,
                                           const std::string &method_descriptor);

    private:
        static std::string methodSignature(const std::string &class_name,
                                           const std::string &method_name,
                                           const std::string &method_descriptor);

        static std::unordered_map<std::string, NativeMethod> native_methods_;
    };

    void initNativeMethods();
}
#endif //TOYJVM_NATIVE_METHODS_H
