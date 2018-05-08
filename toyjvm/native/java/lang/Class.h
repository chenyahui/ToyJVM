//
// Created by cyhone on 18-5-8.
//

#ifndef TOYJVM_NATIVE_JAVA_LANG_CLASS_H
#define TOYJVM_NATIVE_JAVA_LANG_CLASS_H

#include <toyjvm/utilities/all_static.h>
#include <toyjvm/runtime/jvm_frame.h>

namespace jvm {
    namespace native {
        class JavaLangClass : AllStatic{
        public:
            static bool init();
        };
    }
}
#endif //TOYJVM_CLASS_H
