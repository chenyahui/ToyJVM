//
// Created by cyhone on 18-5-9.
//

#ifndef TOYJVM_NATIVE_JAVA_LANG_FLOAT_ANT_DOUBLE_H
#define TOYJVM_NATIVE_JAVA_LANG_FLOAT_ANT_DOUBLE_H

#include <toyjvm/runtime/jvm_frame.h>
#include <toyjvm/native/native_methods.h>
#include <functional>

namespace jvm{
    namespace native{
        template<typename From, typename To>
        void convertTypeAtBits(jvm::JvmFrame &frame)
        {
            auto from = frame.localSlots().at<From>(0);
            auto to = jvm::union_cast<From, To>(from);
            frame.operandStack().push<To>(to);
        }

#define bind_convert(From, To) \
        std::bind(convertTypeAtBits<From, To>, std::placeholders::_1)

        static bool init()
        {
            NativeMethods::registerMethod("java/lang/Float", "floatToRawIntBits",
                                          "(F)I", bind_convert(jfloat, jint));
            NativeMethods::registerMethod("java/lang/Double", "doubleToRawLongBits",
                                          "(D)J", bind_convert(jdouble, jlong));
            NativeMethods::registerMethod("java/lang/Double", "longBitsToDouble",
                                          "(J)D", bind_convert(jlong, jdouble));
        }

        static bool g_init = init();
    }
}



#endif //TOYJVM_FLOAT_ANT_DOUBLE_H
