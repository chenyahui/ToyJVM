//
// Created by cyhone on 18-5-9.
//

#ifndef TOYJVM_THROWABLE_H
#define TOYJVM_THROWABLE_H

#include <toyjvm/utilities/all_static.h>
#include <toyjvm/runtime/jvm_frame.h>
#include <toyjvm/native/native_methods.h>
#include <toyjvm/runtime/jvm_reference.h>
#include <toyjvm/runtime/exception_table.h>

namespace jvm {
    namespace native {
        class JavaLangThrowable : AllStatic {
        public:
            static bool init();

            static void fillInStackTrace(JvmFrame &);

        private:
            static void registerMethod(const std::string &method_name,
                                       const std::string &method_descriptor,
                                       jvm::native::NativeMethod &&native_method);

            static std::vector<jvm::StackTraceElement> createStackTraceElements(JvmObject *obj, JvmThread &jthread);
            static jvm::StackTraceElement createStackTraceElement(JvmFrame* frame);
            static size_t distanceToObject(JvmClass *jclass);

        private:
            static bool is_init_ = init();
        };
    }
}
#endif //TOYJVM_THROWABLE_H
