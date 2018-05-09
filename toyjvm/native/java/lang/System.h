//
// Created by cyhone on 18-5-8.
//

#ifndef TOYJVM_NATIVE_JAVA_LANG_SYSTEM_H
#define TOYJVM_NATIVE_JAVA_LANG_SYSTEM_H

#include <toyjvm/utilities/all_static.h>
#include <toyjvm/runtime/jvm_frame.h>
#include <boost/algorithm/string.hpp>
#include <toyjvm/runtime/jvm_reference.h>
#include <toyjvm/native/native_methods.h>

namespace jvm {
    namespace native {
        class JavaLangSystem : AllStatic {
        public:
            static bool init();

            static void arraycopy(JvmFrame &frame);

        private:
            template<typename T>
            static void realArrayCopy(JvmBaseArray *src, JvmBaseArray *dest, int src_pos, int dest_pos, int length)
            {
                auto src_arr = dynamic_cast<JvmArray<T> *>(src);
                auto dest_arr = dynamic_cast<JvmArray<T> *>(dest);

                std::copy(src_arr->rawData().begin() + src_pos,
                          src_arr->rawData().begin() + length,
                          dest_arr->rawData().begin() + dest_pos);
            }

            static bool checkArrayCopy(JvmBaseArray *src, JvmBaseArray *dest);
            static void registerMethod(const std::string &method_name,
                                       const std::string &method_descriptor,
                                       jvm::native::NativeMethod native_method);

        private:
            static bool is_init_ = init();
        };
    }
}
#endif //TOYJVM_SYSTEM_H
