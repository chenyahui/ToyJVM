//
// Created by cyhone on 18-5-8.
//

#ifndef TOYJVM_NATIVE_JAVA_LANG_CLASS_H
#define TOYJVM_NATIVE_JAVA_LANG_CLASS_H

#include <toyjvm/utilities/all_static.h>
#include <toyjvm/runtime/jvm_frame.h>
#include <toyjvm/native/native_methods.h>
namespace jvm {
    namespace native {
        class JavaLangClass : AllStatic {
        public:
            static bool init();

            static void getPrimitiveClass(JvmFrame &);

            static void getName0(JvmFrame &);

            static void desiredAssertionStatus0(JvmFrame &);
        private:
            static void registerMethod(const std::string &method_name,
                                       const std::string &method_descriptor,
                                       jvm::native::NativeMethod&& native_method);
        private:
            static bool is_init_ = init();
        };
    }
}
#endif //TOYJVM_CLASS_H
