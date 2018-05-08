//
// Created by cyhone on 18-5-8.
//

#ifndef TOYJVM_NATIVE_JAVA_LANG_SYSTEM_H
#define TOYJVM_NATIVE_JAVA_LANG_SYSTEM_H

#include <toyjvm/utilities/all_static.h>
#include <toyjvm/runtime/jvm_frame.h>

namespace jvm {
    namespace native {
        class JavaLangSystem : AllStatic {
        public:
            void arraycopy(JvmFrame& frame);
        };
    }
}
#endif //TOYJVM_SYSTEM_H
